/* stepper-brick
 * Copyright (C) 2010-2011 Olaf Lüke <olaf@tinkerforge.com>
 *
 * stepper.h: Implementation of Stepper-Brick specific functions
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

#ifndef STEPPER_H
#define STEPPER_H

#include <stdint.h>
#include "config.h"
#include "bricklib/utility/util_definitions.h"

#define STEPPER_VELOCITY_DEFAULT           500
#define STEPPER_ACCELERATION_DEFAULT       1000
#define STEPPER_ACCELERATION_SQRT_DEFAULT  31 // sqrt(1000)
#define STEPPER_DECELERATION_DEFAUL        1000
#define STEPPER_MINIMUM_VOLTAGE_DEFAULT    8000
#define STEPPER_VOLTAGE_EPSILON            200

#define VELOCITY_TO_DELAY(vel) (1000000/(vel))
#define DELAY_TO_VELOCITY(del) (1000000/(del))

#define MAX_TIMER_VALUE 0xFFFF

#define STEPPER_PWM_MAX_DUTY_CYCLE 128

#define STEPPER_TC_CHANNEL_NUM 0
#define STEPPER_TC_CHANNEL (TC0->TC_CHANNEL[STEPPER_TC_CHANNEL_NUM])
#define STEPPER_COUNTER STEPPER_TC_CHANNEL.TC_RC

#define SINGLE_SHOT_TC_CHANNEL_NUM 1
#define SINGLE_SHOT_TC_CHANNEL (TC0->TC_CHANNEL[SINGLE_SHOT_TC_CHANNEL_NUM])
#define SINGLE_SHOT_COUNTER SINGLE_SHOT_TC_CHANNEL.TC_RC

#define STEP_MODE_FULL       1
#define STEP_MODE_HALF       2
#define STEP_MODE_QUARTER    4
#define STEP_MODE_EIGTH      8

// (0.2*3300)
#define DECAY_MIN_VALUE      SCALE(660, VOLTAGE_MIN_DAC, VOLTAGE_MAX_DAC, \
                                        VOLTAGE_MIN_VALUE, VOLTAGE_MAX_VALUE)
// (0.61*3300)
#define DECAY_MAX_VALUE      SCALE(2013, VOLTAGE_MIN_DAC, VOLTAGE_MAX_DAC, \
                                         VOLTAGE_MIN_VALUE, VOLTAGE_MAX_VALUE)

#define DECAY_DEFAULT_VALUE  10000

#define STEPPER_STATE_OFF    1
#define STEPPER_STATE_STOP   2
#define STEPPER_STATE_DRIVE  3
#define STEPPER_STATE_STEPS  4
#define STEPPER_STATE_TARGET 5

// Define forward and backward same as for direction,
// this allows for easy comparisons
#define STEPPER_SPEEDRAMP_STATE_FORWARD        1
#define STEPPER_SPEEDRAMP_STATE_BACKWARD      -1
#define STEPPER_SPEEDRAMP_STATE_STOP           2
#define STEPPER_SPEEDRAMP_STATE_ACCELERATION   3
#define STEPPER_SPEEDRAMP_STATE_RUN            4
#define STEPPER_SPEEDRAMP_STATE_DECELERATION   5

#define STEPPER_DIRECTION_FORWARD   1
#define STEPPER_DIRECTION_BACKWARD -1

void new_connection(void);
void stepper_init(void);
void stepper_set_output_current(const uint16_t current);
void stepper_set_step_mode(const uint8_t mode);
uint8_t stepper_get_step_mode(void);
void stepper_set_decay(const uint16_t decay);
void stepper_enable(void);
void stepper_disable(void);
void stepper_update_tc_frequency(void);
uint16_t stepper_get_external_voltage(void);
uint16_t stepper_get_stack_voltage(void);
void tick_task(void);
void stepper_set_direction(int8_t direction);
void TC1_IrqHandler(void);
void stepper_position_reached_signal(void);
bool stepper_is_currently_running(void);
void stepper_set_next_timer(uint32_t velocity);
void stepper_make_step(void);
void stepper_make_step_speedramp(int32_t steps);
void stepper_step_speedramp(void);
void stepper_make_drive_speedramp(uint8_t state);
void stepper_drive_speedramp(void);
void stepper_full_brake(void);
void stepper_check_error_signals(void);
uint16_t stepper_get_current(void);

void TC0_IrqHandler(void);
#endif
