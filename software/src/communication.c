/* stepper-brick
 * Copyright (C) 2010-2011 Olaf Lüke <olaf@tinkerforge.com>
 *
 * communication.c: Implementation of Stepper-Brick specific messages
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

#include "communication.h"

#include "stepper.h"

#include "bricklib/logging/logging.h"
#include "bricklib/com/com_common.h"
#include "bricklib/drivers/pwmc/pwmc.h"
#include "bricklib/drivers/adc/adc.h"

#include "bricklib/utility/util_definitions.h"
#include "bricklib/utility/sqrt.h"

#include <stdint.h>
#include <stdio.h>

extern uint8_t stepper_step_type;
extern uint32_t stepper_velocity_goal;
extern uint32_t stepper_velocity;
extern uint16_t stepper_acceleration;
extern uint16_t stepper_acceleration_sqrt;
extern uint16_t stepper_deceleration;
extern uint16_t stepper_minimum_voltage;
extern uint16_t stepper_decay;

extern int32_t stepper_position;
extern int32_t stepper_target_position;
extern int32_t stepper_steps;
extern uint8_t stepper_drive;
extern uint16_t stepper_output_current;

extern int8_t stepper_state;
extern int8_t stepper_speedramp_state;
extern int32_t stepper_step_counter;

void set_max_velocity(uint8_t com, const SetMaxVelocity *data) {
	stepper_velocity_goal = data->velocity;
}

void get_max_velocity(uint8_t com, const GetMaxVelocity *data) {
	GetMaxVelocityReturn gmvr;

	gmvr.stack_address = data->stack_address;
	gmvr.type          = data->type;
	gmvr.length        = sizeof(GetMaxVelocityReturn);
	gmvr.velocity      = stepper_velocity_goal;

	send_blocking_with_timeout(&gmvr, sizeof(GetMaxVelocityReturn), com);
}

void get_current_velocity(uint8_t com, const GetCurrentVelocity *data) {
	GetCurrentVelocityReturn gcvr;

	gcvr.stack_address = data->stack_address;
	gcvr.type          = data->type;
	gcvr.length        = sizeof(GetCurrentVelocityReturn);
	gcvr.velocity      = stepper_velocity;

	send_blocking_with_timeout(&gcvr, sizeof(GetCurrentVelocityReturn), com);
}

void set_speed_ramping(uint8_t com, const SetSpeedRamping *data) {
	stepper_acceleration_sqrt = sqrt_integer_precise(data->acceleration);
	stepper_acceleration      = data->acceleration;
	stepper_deceleration      = data->deceleration;
}

void get_speed_ramping(uint8_t com, const GetSpeedRamping *data) {
	GetSpeedRampingReturn gsrr;

	gsrr.stack_address = data->stack_address;
	gsrr.type          = data->type;
	gsrr.length        = sizeof(GetSpeedRampingReturn);
	gsrr.acceleration  = stepper_acceleration;
	gsrr.deceleration  = stepper_deceleration;

	send_blocking_with_timeout(&gsrr, sizeof(GetSpeedRampingReturn), com);
}

void full_brake(uint8_t com, const FullBrake *data) {
	stepper_full_brake();
}

void set_current_position(uint8_t com, const SetCurrentPosition *data) {
	stepper_position = data->position;
}

void get_current_position(uint8_t com, const GetCurrentPosition *data) {
	GetCurrentPositionReturn gcpr;

	gcpr.stack_address = data->stack_address;
	gcpr.type          = data->type;
	gcpr.length        = sizeof(GetCurrentPositionReturn);
	gcpr.position      = stepper_position;

	send_blocking_with_timeout(&gcpr, sizeof(GetCurrentPositionReturn), com);
}

void set_target_position(uint8_t com, const SetTargetPosition *data) {
	if(stepper_is_currently_running() || stepper_state == STEPPER_STATE_OFF) {
		return;
	}

	stepper_state = STEPPER_STATE_TARGET;
	stepper_target_position = data->position;
	stepper_make_step_speedramp(stepper_target_position - stepper_position);
}

void get_target_position(uint8_t com, const GetTargetPosition *data) {
	GetTargetPositionReturn gtpr;

	gtpr.stack_address = data->stack_address;
	gtpr.type          = data->type;
	gtpr.length        = sizeof(GetTargetPositionReturn);
	gtpr.position      = stepper_target_position;

	send_blocking_with_timeout(&gtpr, sizeof(GetTargetPositionReturn), com);
}

void set_steps(uint8_t com, const SetSteps *data) {
	if(stepper_is_currently_running() || stepper_state == STEPPER_STATE_OFF) {
		return;
	}

	stepper_state = STEPPER_STATE_STEPS;
	stepper_steps = data->steps;
	stepper_make_step_speedramp(data->steps);
}

void get_steps(uint8_t com, const GetSteps *data) {
	GetStepsReturn gsr;

	gsr.stack_address = data->stack_address;
	gsr.type          = data->type;
	gsr.length        = sizeof(GetStepsReturn);
	gsr.steps         = stepper_steps;

	send_blocking_with_timeout(&gsr, sizeof(GetStepsReturn), com);
}

void get_remaining_steps(uint8_t com, const GetRemainingSteps *data) {
	GetRemainingStepsReturn grsr;

	grsr.stack_address = data->stack_address;
	grsr.type          = data->type;
	grsr.length        = sizeof(GetRemainingStepsReturn);
	if(stepper_state == STEPPER_STATE_STEPS) {
		if(stepper_steps > 0) {
			grsr.steps = stepper_steps - stepper_step_counter;
		} else {
			grsr.steps = stepper_steps + stepper_step_counter;
		}
	} else if(stepper_state == STEPPER_STATE_TARGET) {
		grsr.steps     = stepper_target_position - stepper_position;
	} else {
		grsr.steps     = 0;
	}

	send_blocking_with_timeout(&grsr, sizeof(GetRemainingStepsReturn), com);
}

void set_step_mode(uint8_t com, const SetStepMode *data) {
	stepper_set_step_mode(data->mode);
}

void get_step_mode(uint8_t com, const GetStepMode *data) {
	GetStepModeReturn gsmr;

	gsmr.stack_address = data->stack_address;
	gsmr.type          = data->type;
	gsmr.length        = sizeof(GetStepModeReturn);
	gsmr.mode          = stepper_get_step_mode();

	send_blocking_with_timeout(&gsmr, sizeof(GetStepModeReturn), com);
}

void drive_forward(uint8_t com, const DriveForward *data) {
	if(stepper_state == STEPPER_STATE_STEPS ||
	   stepper_state == STEPPER_STATE_TARGET ||
	   stepper_state == STEPPER_STATE_OFF) {
		return;
	}

	stepper_make_drive_speedramp(STEPPER_SPEEDRAMP_STATE_FORWARD);
}

void drive_backward(uint8_t com, const DriveBackward *data) {
	if(stepper_state == STEPPER_STATE_STEPS ||
	   stepper_state == STEPPER_STATE_TARGET ||
	   stepper_state == STEPPER_STATE_OFF) {
		return;
	}

	stepper_make_drive_speedramp(STEPPER_SPEEDRAMP_STATE_BACKWARD);
}

void stop(uint8_t com, const Stop *data) {
	if(stepper_state == STEPPER_STATE_OFF) {
		return;
	}

	stepper_make_drive_speedramp(STEPPER_SPEEDRAMP_STATE_STOP);
}

void get_stack_input_voltage(uint8_t com, const GetStackInputVoltage *data) {
	GetStackInputVoltageReturn gsivr;

	gsivr.stack_address = data->stack_address;
	gsivr.type          = data->type;
	gsivr.length        = sizeof(GetStackInputVoltageReturn);
    gsivr.voltage       = stepper_get_stack_voltage();

	send_blocking_with_timeout(&gsivr, sizeof(GetStackInputVoltageReturn), com);
}

void get_external_input_voltage(uint8_t com, const GetExternalInputVoltage *data) {
	GetExternalInputVoltageReturn geivr;

	geivr.stack_address = data->stack_address;
	geivr.type          = data->type;
	geivr.length        = sizeof(GetExternalInputVoltageReturn);
	geivr.voltage       = stepper_get_external_voltage();

	send_blocking_with_timeout(&geivr, sizeof(GetExternalInputVoltageReturn), com);
}

void get_current_consumption(uint8_t com, const GetCurrentConsumption *data) {
	GetCurrentConsumptionReturn gccr;

	gccr.stack_address = data->stack_address;
	gccr.type          = data->type;
	gccr.length        = sizeof(GetCurrentConsumptionReturn);
	gccr.current       = stepper_get_current();

	send_blocking_with_timeout(&gccr, sizeof(GetCurrentConsumptionReturn), com);
}

void set_motor_current(uint8_t com, const SetMotorCurrent *data) {
	stepper_set_output_current(data->current);
}

void get_motor_current(uint8_t com, const GetMotorCurrent *data) {
	GetMotorCurrentReturn gmcr;

	gmcr.stack_address = data->stack_address;
	gmcr.type          = data->type;
	gmcr.length        = sizeof(GetMotorCurrentReturn);
	gmcr.current       = stepper_output_current;

	send_blocking_with_timeout(&gmcr, sizeof(GetMotorCurrentReturn), com);
}

void enable(uint8_t com, const Enable *data) {
	stepper_enable();
}

void disable(uint8_t com, const Disable *data) {
	stepper_disable();
}

void is_enabled(uint8_t com, const IsEnabled *data) {
	IsEnabledReturn ier;

	ier.stack_address = data->stack_address;
	ier.type          = data->type;
	ier.length        = sizeof(IsEnabledReturn);
	ier.enabled       = stepper_state != STEPPER_STATE_OFF;

	send_blocking_with_timeout(&ier, sizeof(IsEnabledReturn), com);
}

void set_decay(uint8_t com, const SetDecay *data) {
	stepper_set_decay(data->decay);
}

void get_decay(uint8_t com, const GetDecay *data) {
	GetDecayReturn gdr;

	gdr.stack_address = data->stack_address;
	gdr.type          = data->type;
	gdr.length        = sizeof(GetDecayReturn);
	gdr.decay         = stepper_decay;

	send_blocking_with_timeout(&gdr, sizeof(GetDecayReturn), com);
}

void set_minimum_voltage(uint8_t com, const SetMinimumVoltage *data) {
	stepper_minimum_voltage = data->voltage;
}

void get_minimum_voltage(uint8_t com, const GetMinimumVoltage *data) {
	GetMinimumVoltageReturn gmvr;

	gmvr.stack_address = data->stack_address;
	gmvr.type          = data->type;
	gmvr.length        = sizeof(GetMinimumVoltageReturn);
	gmvr.voltage       = stepper_minimum_voltage;

	send_blocking_with_timeout(&gmvr, sizeof(GetMinimumVoltageReturn), com);
}
