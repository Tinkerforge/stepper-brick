/* stepper-brick
 * Copyright (C) 2010-2011 Olaf Lüke <olaf@tinkerforge.com>
 *
 * stepper.c: Implementation of Stepper-Brick specific functions
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "stepper.h"

#include "config.h"
#include "communication.h"

#include "bricklib/com/com.h"
#include "bricklib/com/com_common.h"
#include "bricklib/logging/logging.h"
#include "bricklib/bricklet/bricklet_init.h"
#include "bricklib/drivers/dacc/dacc.h"
#include "bricklib/drivers/adc/adc.h"
#include "bricklib/drivers/tc/tc.h"
#include "bricklib/drivers/pio/pio.h"
#include "bricklib/drivers/usart/usart.h"
#include "bricklib/drivers/pwmc/pwmc.h"
#include "bricklib/utility/util_definitions.h"
#include "bricklib/utility/led.h"
#include <stdio.h>

Pin pin_enable =  PIN_ENABLE;
Pin pin_sleep = PIN_SLEEP;
Pin pin_step = PIN_STEP;
Pin pin_direction = PIN_DIRECTION;
Pin pin_usm[2] = {PIN_USM0, PIN_USM1};
Pin pin_reset = PIN_RESET;
Pin pin_sync_rect = PIN_SYNC_RECT;
Pin pin_home = PIN_HOME;
Pin pin_vref = PIN_VREF;
Pin pin_decay = PIN_DECAY;
Pin pin_voltage_switch = VOLTAGE_STACK_SWITCH_PIN;

uint32_t stepper_velocity_goal = STEPPER_VELOCITY_DEFAULT;
uint32_t stepper_velocity = 0;
uint16_t stepper_acceleration = STEPPER_ACCELERATION_DEFAULT;
uint16_t stepper_acceleration_sqrt = STEPPER_ACCELERATION_SQRT_DEFAULT;
uint16_t stepper_deceleration = STEPPER_DECELERATION_DEFAUL;
uint16_t stepper_minimum_voltage = STEPPER_MINIMUM_VOLTAGE_DEFAULT;
uint16_t stepper_decay = 0;

int32_t stepper_position = 0;
int32_t stepper_target_position = 0;
int32_t stepper_steps = 0;
uint16_t stepper_output_current = 0;
int8_t stepper_state = STEPPER_STATE_OFF;
int8_t stepper_speedramp_state = STEPPER_SPEEDRAMP_STATE_STOP;
int8_t stepper_direction = STEPPER_DIRECTION_FORWARD;

int32_t stepper_step_counter = 0;
int32_t stepper_acceleration_counter = 0;
int32_t stepper_acceleration_steps = 0;
int32_t stepper_deceleration_steps = 0;
int32_t stepper_delay = 0;
int32_t stepper_last_delay = 0;
int32_t stepper_delay_rest = 0;
int32_t stepper_deceleration_start = 0;
uint32_t stepper_tick_counter = 0;

bool stepper_running = false;
bool stepper_position_reached = false;

const uint32_t stepper_timer_frequency[] = {BOARD_MCK/2,
                                            BOARD_MCK/8,
                                            BOARD_MCK/32,
                                            BOARD_MCK/128,
                                            32768};
const uint32_t stepper_timer_velocity[]  = {BOARD_MCK/2   / MAX_TIMER_VALUE,
                                            BOARD_MCK/8   / MAX_TIMER_VALUE,
                                            BOARD_MCK/32  / MAX_TIMER_VALUE,
                                            BOARD_MCK/128 / MAX_TIMER_VALUE,
                                            32768         / MAX_TIMER_VALUE};

extern ComType com_current;
extern uint8_t com_stack_id;

void stepper_position_reached_signal(void) {
	PositionReachedSignal prs = {
		com_stack_id,
		TYPE_POSITION_REACHED,
		sizeof(PositionReachedSignal),
		stepper_position
	};

	send_blocking_with_timeout(&prs,
	                           sizeof(PositionReachedSignal),
	                           com_current);
}

void stepper_check_error_signals(void) {
	if(stepper_tick_counter % 1000 != 0 || stepper_state == STEPPER_STATE_OFF) {
		return;
	}

	const uint16_t external_voltage = stepper_get_external_voltage();
	const uint16_t stack_voltage    = stepper_get_stack_voltage();

	// Under Voltage if external voltage is below minimum voltage (regardless
	// of stack voltage), or if external voltage is zero and stack velotage is
	// below minimum voltage

	if((external_voltage > STEPPER_VOLTAGE_EPSILON &&
	    external_voltage < stepper_minimum_voltage) ||
	   (external_voltage < STEPPER_VOLTAGE_EPSILON &&
	    stack_voltage > STEPPER_VOLTAGE_EPSILON &&
	    stack_voltage < stepper_minimum_voltage)) {
		UnderVoltageSignal uvs = {
				com_stack_id,
				TYPE_UNDER_VOLTAGE,
				sizeof(UnderVoltageSignal),
				external_voltage == 0 ? stack_voltage : external_voltage
		};

		send_blocking_with_timeout(&uvs,
		                           sizeof(UnderVoltageSignal),
		                           com_current);
	}
}

void stepper_make_drive_speedramp(uint8_t state) {
	stepper_state = STEPPER_STATE_DRIVE;
	stepper_speedramp_state = state;

	if(!stepper_is_currently_running()) {
		// call drive speedramp one time, to get it going
		// (i.e. make velocity != 0)
		stepper_drive_speedramp();
		TC0_IrqHandler();
	}
}

void stepper_make_step_speedramp(int32_t steps) {
	if(steps == 0) {
		stepper_position_reached = true;
		stepper_state = STEPPER_STATE_STOP;
		return;
	}
	if(steps < 0) {
		stepper_set_direction(STEPPER_DIRECTION_BACKWARD);
		steps = -steps;
	} else {
		stepper_set_direction(STEPPER_DIRECTION_FORWARD);
	}

	if(steps == 1) {
		// Just make the single step, no need for TC IRQ
		stepper_make_step();
		stepper_position_reached = true;
		return;
	}

	uint16_t acceleration;
	uint16_t acceleration_sqrt;
	uint16_t deceleration;

	if(stepper_acceleration == 0) {
		acceleration = 0xFFFF;
		acceleration_sqrt = 256; // sqrt(0xFFFF)
	} else {
		acceleration = stepper_acceleration;
		acceleration_sqrt = stepper_acceleration_sqrt;
	}

	if(stepper_deceleration == 0) {
		deceleration = 0xFFFF;
	} else {
		deceleration = stepper_deceleration;
	}

	stepper_acceleration_steps = (stepper_velocity_goal*stepper_velocity_goal)/
	                             (2*acceleration);
	if(stepper_acceleration_steps == 0) {
		stepper_acceleration_steps = 1;
	}

	int32_t acceleration_limit = (steps*deceleration)/
	                             (acceleration + deceleration);
	if(acceleration_limit == 0) {
		acceleration_limit = 1;
	}

	if(acceleration_limit <= stepper_acceleration_steps) {
		stepper_deceleration_steps = acceleration_limit - steps;
	} else {
		stepper_deceleration_steps = -stepper_acceleration_steps *
									  acceleration /
		                              deceleration;
	}
	if(stepper_deceleration_steps == 0) {
		stepper_deceleration_steps = -1;
	}

	stepper_velocity = acceleration_sqrt;
	stepper_delay = VELOCITY_TO_DELAY(acceleration_sqrt);

	stepper_deceleration_start = steps + stepper_deceleration_steps;
	stepper_step_counter = 0;
	stepper_acceleration_counter = 0;
	stepper_speedramp_state = STEPPER_SPEEDRAMP_STATE_ACCELERATION;

	TC0_IrqHandler();
}

void tick_task(void) {
	stepper_tick_counter++;

	// Switch Output Voltage between extern and stack
	if(adc_channel_get_data(VOLTAGE_EXTERN_CHANNEL) < MIN_EXTERN_VALUE) {
		PIO_Set(&pin_voltage_switch);
	} else {
		PIO_Clear(&pin_voltage_switch);
	}

	if(stepper_position_reached) {
		stepper_position_reached = false;
		stepper_position_reached_signal();
	}

	stepper_check_error_signals();
}

void stepper_init(void) {
	Pin pins_stepper[] = {PINS_STEPPER};
	PIO_Configure(pins_stepper, PIO_LISTSIZE(pins_stepper));

	Pin stepper_power_management_pins[] = {VOLTAGE_STACK_PIN,
	                                       VOLTAGE_EXTERN_PIN,
	                                       VOLTAGE_STACK_SWITCH_PIN,
	                                       STEPPER_CURRENT_PIN};
	PIO_Configure(stepper_power_management_pins,
	              PIO_LISTSIZE(stepper_power_management_pins));

	// Initialize and enable DACC to set VREF and DECAY pins
    DACC_Initialize(DACC,
                    ID_DACC,
                    0, // Hardware triggers are disabled
                    0, // External trigger
                    0, // Half-Word Transfer
                    0, // Normal Mode (not sleep mode)
                    BOARD_MCK,
                    1, // refresh period
                    0, // Channel 0 selection
                    1, // Tag Selection Mode enabled
                    16); //  value of the start up time
    DACC_EnableChannel(DACC, VREF_CHANNEL);
    DACC_EnableChannel(DACC, DECAY_CHANNEL);


    // Enable peripheral clock for TC
    PMC->PMC_PCER0 = 1 << ID_TC0;

    // Configure and enable TC interrupts
	NVIC_DisableIRQ(TC0_IRQn);
	NVIC_ClearPendingIRQ(TC0_IRQn);
	NVIC_SetPriority(TC0_IRQn, PRIORITY_STEPPER_TC0);
	NVIC_EnableIRQ(TC0_IRQn);

	tc_channel_init(&STEPPER_TC_CHANNEL,
	                TC_CMR_TCCLKS_TIMER_CLOCK5 | TC_CMR_CPCTRG);

    // Interrupt in compare
    tc_channel_interrupt_set(&STEPPER_TC_CHANNEL, TC_IER_CPCS);

    PMC->PMC_PCER0 = 1 << ID_TC1;
	tc_channel_init(&SINGLE_SHOT_TC_CHANNEL,
	                TC_CMR_WAVE |
	                TC_CMR_TCCLKS_TIMER_CLOCK4 |
	                TC_CMR_EEVT_XC0 |
	                TC_CMR_ASWTRG_SET |
	                TC_CMR_ACPC_CLEAR |
	                TC_CMR_WAVSEL_UP |
	                TC_CMR_CPCDIS |
	                TC_CMR_CPCSTOP);

	SINGLE_SHOT_COUNTER = 1;
	tc_channel_start(&SINGLE_SHOT_TC_CHANNEL);

    stepper_set_output_current(VREF_DEFAULT_CURRENT);
    stepper_set_step_mode(STEP_MODE_FULL);
    stepper_set_decay(DECAY_DEFAULT_VALUE);

	adc_channel_enable(VOLTAGE_EXTERN_CHANNEL);
	adc_channel_enable(VOLTAGE_STACK_CHANNEL);
	adc_channel_enable(STEPPER_CURRENT_CHANNEL);
}

void stepper_set_next_timer(uint32_t velocity) {
	if(velocity == 0) {
		if(stepper_state == STEPPER_STATE_DRIVE) {
			// In drive mode we have a transition from backward to forward here.
			// Wait 10ms in that case
			velocity = 100;
		} else {
			// In step mode this should not happen, stop tc
			stepper_running = false;
			tc_channel_stop(&STEPPER_TC_CHANNEL);
			return;
		}
	}

	int8_t i;
	for(i = 4; i > 0; i--) {
		if(velocity <= stepper_timer_velocity[i-1]) {
			break;
		}
	}

	STEPPER_TC_CHANNEL.TC_CMR = i | TC_CMR_CPCTRG;
	STEPPER_COUNTER = stepper_timer_frequency[i] / velocity;
	if(!stepper_is_currently_running()) {
		stepper_running = true;
		tc_channel_start(&STEPPER_TC_CHANNEL);
	}
}

bool stepper_is_currently_running(void) {
	return stepper_running;
}

void stepper_make_step(void) {
	tc_channel_start(&SINGLE_SHOT_TC_CHANNEL);
	stepper_position += stepper_direction;
}

void stepper_step_speedramp(void) {
	int32_t new_delay = 0;

	switch(stepper_speedramp_state) {
		case STEPPER_SPEEDRAMP_STATE_STOP: {
			stepper_velocity = 0;
			stepper_step_counter = 0;
			stepper_acceleration_counter = 0;
			stepper_delay_rest = 0;

			stepper_running = false;
			tc_channel_stop(&STEPPER_TC_CHANNEL);
			return;
		}

		case STEPPER_SPEEDRAMP_STATE_ACCELERATION: {
			stepper_step_counter++;
			stepper_acceleration_counter++;

			int32_t a = (2*stepper_delay + stepper_delay_rest);
			int32_t b = (4*stepper_acceleration_counter + 1);
			new_delay = stepper_delay - a/b;
			stepper_delay_rest = a % b;

			if(stepper_step_counter >= stepper_deceleration_start) {
				stepper_acceleration_counter = stepper_deceleration_steps;
				stepper_speedramp_state = STEPPER_SPEEDRAMP_STATE_DECELERATION;
			} else if(new_delay <= VELOCITY_TO_DELAY(stepper_velocity_goal)) {
				stepper_last_delay = new_delay;
				new_delay = VELOCITY_TO_DELAY(stepper_velocity_goal);
				stepper_speedramp_state = STEPPER_SPEEDRAMP_STATE_RUN;
			}
			break;
		}

		case STEPPER_SPEEDRAMP_STATE_RUN: {
			stepper_step_counter++;
			if(stepper_step_counter >= stepper_deceleration_start) {
				stepper_acceleration_counter = stepper_deceleration_steps;
				new_delay = stepper_last_delay;
				stepper_speedramp_state = STEPPER_SPEEDRAMP_STATE_DECELERATION;
			} else {
				new_delay = VELOCITY_TO_DELAY(stepper_velocity_goal);
			}
			break;
		}

		case STEPPER_SPEEDRAMP_STATE_DECELERATION: {
			stepper_step_counter++;
			stepper_acceleration_counter++;

			int32_t a = (2*stepper_delay + stepper_delay_rest);
			int32_t b = (4*stepper_acceleration_counter + 1);
			new_delay = stepper_delay - a/b;
			stepper_delay_rest = a % b;

			if(stepper_acceleration_counter >= 0) {
				stepper_speedramp_state = STEPPER_SPEEDRAMP_STATE_STOP;
				stepper_state = STEPPER_STATE_STOP;
				stepper_position_reached = true;
				stepper_running = false;
				tc_channel_stop(&STEPPER_TC_CHANNEL);
				stepper_velocity = 0;
				return;
			}
			break;
		}
	}

	stepper_delay = new_delay;
	stepper_velocity = DELAY_TO_VELOCITY(stepper_delay);
}

void stepper_full_brake(void) {
	stepper_running = false;
	tc_channel_stop(&STEPPER_TC_CHANNEL);
	stepper_state = STEPPER_STATE_STOP;
	stepper_speedramp_state = STEPPER_SPEEDRAMP_STATE_STOP;
	stepper_velocity = 0;
}

void stepper_drive_speedramp(void) {
	static uint32_t rest = 0;
	uint16_t goal = stepper_velocity_goal;

	if((stepper_speedramp_state == STEPPER_SPEEDRAMP_STATE_STOP) ||
	   (stepper_speedramp_state != stepper_direction)) {
		goal = 0;
	}

	if(goal == stepper_velocity) {
		if(stepper_speedramp_state == STEPPER_SPEEDRAMP_STATE_STOP) {
			stepper_running = false;
			tc_channel_stop(&STEPPER_TC_CHANNEL);
			stepper_state = STEPPER_STATE_STOP;
			rest = 0;
			return;
		} else if(stepper_speedramp_state != stepper_direction) {
			goal = stepper_velocity_goal;
			rest = 0;
		} else {
			// If i am at stepper velocity goal and the direction is correct
			// -> We have nothing to do
			return;
		}
	}

	uint16_t acceleration;
	uint16_t acceleration_sqrt;
	uint16_t deceleration;
	int32_t delta;

	if(stepper_acceleration == 0) {
		acceleration = 0xFFFF;
		acceleration_sqrt = 256; // sqrt(0xFFFF)
	} else {
		acceleration = stepper_acceleration;
		acceleration_sqrt = stepper_acceleration_sqrt;
	}
	if(stepper_deceleration == 0) {
		deceleration = 0xFFFF;
	} else {
		deceleration = stepper_deceleration;
	}

	if(stepper_velocity == 0) {
		delta = acceleration_sqrt;
		rest = 0;
		if(stepper_speedramp_state == STEPPER_SPEEDRAMP_STATE_FORWARD) {
			stepper_set_direction(STEPPER_DIRECTION_FORWARD);
		} else if(stepper_speedramp_state == STEPPER_SPEEDRAMP_STATE_BACKWARD) {
			stepper_set_direction(STEPPER_DIRECTION_BACKWARD);
		}
	} else {
		if(stepper_velocity < goal) {
			delta = (acceleration + rest) / stepper_velocity;
			rest = (acceleration + rest) % stepper_velocity;
		} else {
			delta = (deceleration + rest) / stepper_velocity;
			rest = (deceleration + rest) % stepper_velocity;
		}
	}

	if(stepper_velocity < goal) {
		stepper_velocity = MIN(stepper_velocity + delta,
							   goal);
	} else {
		stepper_velocity = MAX(((int32_t)stepper_velocity) - delta,
							   goal);
	}
}

void TC0_IrqHandler(void) {
	// acknowledge interrupt
	tc_channel_interrupt_ack(&STEPPER_TC_CHANNEL);

	if(stepper_state != STEPPER_STATE_STOP) {
		stepper_set_next_timer(stepper_velocity);
		stepper_make_step();
	}

	if(stepper_state == STEPPER_STATE_STEPS ||
	   stepper_state == STEPPER_STATE_TARGET) {
		stepper_step_speedramp();
	} else if(stepper_state == STEPPER_STATE_DRIVE) {
		stepper_drive_speedramp();
	}
}

void stepper_set_direction(int8_t direction) {
	if(direction == stepper_direction) {
		return;
	}

	stepper_direction = direction;
	if(direction == STEPPER_DIRECTION_FORWARD) {
		PIO_Clear(&pin_direction);
	} else {
		PIO_Set(&pin_direction);
	}
}

void stepper_enable(void) {
	PIO_Set(&pin_reset);
	PIO_Clear(&pin_enable);
	PIO_Set(&pin_sleep);
	stepper_state = STEPPER_STATE_STOP;
	stepper_speedramp_state = STEPPER_SPEEDRAMP_STATE_STOP;
}

void stepper_disable(void) {
	stepper_state = STEPPER_STATE_OFF;
	stepper_speedramp_state = STEPPER_SPEEDRAMP_STATE_STOP;
	PIO_Set(&pin_enable);
	PIO_Clear(&pin_sleep);
}

void stepper_set_output_current(const uint16_t current) {
	const uint16_t new_current = BETWEEN(VREF_MIN_CURRENT,
	                                     current,
	                                     VREF_MAX_CURRENT);

	DACC_SetConversionData(DACC, SCALE(new_current,
	                                   VREF_MIN_CURRENT,
	                                   VREF_MAX_CURRENT,
	                                   VOLTAGE_MIN_VALUE,
	                                   VOLTAGE_MAX_VALUE));

	stepper_output_current = new_current;
}

void stepper_set_step_mode(const uint8_t mode) {
	switch(mode) {
		case STEP_MODE_FULL:
			PIO_Clear(&pin_usm[0]);
			PIO_Clear(&pin_usm[1]);
			break;
		case STEP_MODE_HALF:
			PIO_Set(&pin_usm[0]);
			PIO_Clear(&pin_usm[1]);
			break;
		case STEP_MODE_QUARTER:
			PIO_Clear(&pin_usm[0]);
			PIO_Set(&pin_usm[1]);
			break;
		case STEP_MODE_EIGTH:
			PIO_Set(&pin_usm[0]);
			PIO_Set(&pin_usm[1]);
			break;
		default:
			break;
			// TODO: error?
	}
}

uint8_t stepper_get_step_mode(void) {
	bool usm[2] = {PIO_Get(&pin_usm[0]), PIO_Get(&pin_usm[1])};
	if(!usm[0] && !usm[1]) {
		return STEP_MODE_FULL;
	} else if(usm[0] && !usm[1]) {
		return STEP_MODE_HALF;
	} else if(!usm[0] && usm[1]) {
		return STEP_MODE_QUARTER;
	} else {
		return STEP_MODE_EIGTH;
	}
}

void stepper_set_decay(const uint16_t decay) {
	stepper_decay = decay;
	DACC_SetConversionData(DACC, SCALE(decay,
	                                   0,
	                                   0xFFFF,
	                                   DECAY_MIN_VALUE,
	                                   DECAY_MAX_VALUE) |
	                             (1 << 12));
}

uint16_t stepper_get_external_voltage(void) {
    return adc_channel_get_data(VOLTAGE_EXTERN_CHANNEL) *
           VOLTAGE_EXTERN_REFERENCE *
           VOLTAGE_EXTERN_MULTIPLIER /
           VOLTAGE_MAX_VALUE;
}

uint16_t stepper_get_stack_voltage(void) {
    return adc_channel_get_data(VOLTAGE_STACK_CHANNEL) *
           VOLTAGE_STACK_REFERENCE *
           VOLTAGE_STACK_MULTIPLIER /
           VOLTAGE_MAX_VALUE;
}

uint16_t stepper_get_current(void) {
	return adc_channel_get_data(STEPPER_CURRENT_CHANNEL) *
	                            STEPPER_CURRENT_REFERENCE *
	                            STEPPER_CURRENT_MULTIPLIER /
	                            VOLTAGE_MAX_VALUE;
}
