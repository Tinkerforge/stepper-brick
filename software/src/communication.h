/* stepper-brick
 * Copyright (C) 2010-2011 Olaf Lüke <olaf@tinkerforge.com>
 *
 * communication.h: Implementation of Stepper-Brick specific messages
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


#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdint.h>
#include <stdbool.h>

#define TYPE_SET_MAX_VELOCITY 1
#define TYPE_GET_MAX_VELOCITY 2
#define TYPE_GET_CURRENT_VELOCITY 3
#define TYPE_SET_SPEED_RAMPING 4
#define TYPE_GET_SPEED_RAMPING 5
#define TYPE_FULL_BRAKE 6
#define TYPE_SET_CURRENT_POSITION 7
#define TYPE_GET_CURRENT_POSITION 8
#define TYPE_SET_TARGET_POSITION 9
#define TYPE_GET_TARGET_POSITION 10
#define TYPE_SET_STEPS 11
#define TYPE_GET_STEPS 12
#define TYPE_GET_REMAINING_STEPS 13
#define TYPE_SET_STEP_MODE 14
#define TYPE_GET_STEP_MODE 15
#define TYPE_DRIVE_FORWARD 16
#define TYPE_DRIVE_BACKWARD 17
#define TYPE_STOP 18
#define TYPE_GET_STACK_INPUT_VOLTAGE 19
#define TYPE_GET_EXTERNAL_INPUT_VOLTAGE 20
#define TYPE_GET_CURRENT_CONSUMPTION 21
#define TYPE_SET_MOTOR_CURRENT 22
#define TYPE_GET_MOTOR_CURRENT 23
#define TYPE_ENABLE 24
#define TYPE_DISABLE 25
#define TYPE_IS_ENABLED 26
#define TYPE_SET_DECAY 27
#define TYPE_GET_DECAY 28
#define TYPE_SET_MINIMUM_VOLTAGE 29
#define TYPE_GET_MINIMUM_VOLTAGE 30
#define TYPE_UNDER_VOLTAGE 31
#define TYPE_POSITION_REACHED 32
#define TYPE_SET_SYNC_RECT 33
#define TYPE_IS_SYNC_RECT 34

#define COM_MESSAGES_USER \
	{TYPE_SET_MAX_VELOCITY, (message_handler_func_t)set_max_velocity}, \
	{TYPE_GET_MAX_VELOCITY, (message_handler_func_t)get_max_velocity}, \
	{TYPE_GET_CURRENT_VELOCITY, (message_handler_func_t)get_current_velocity}, \
	{TYPE_SET_SPEED_RAMPING, (message_handler_func_t)set_speed_ramping}, \
	{TYPE_GET_SPEED_RAMPING, (message_handler_func_t)get_speed_ramping}, \
	{TYPE_FULL_BRAKE, (message_handler_func_t)full_brake}, \
	{TYPE_SET_CURRENT_POSITION, (message_handler_func_t)set_current_position}, \
	{TYPE_GET_CURRENT_POSITION, (message_handler_func_t)get_current_position}, \
	{TYPE_SET_TARGET_POSITION, (message_handler_func_t)set_target_position}, \
	{TYPE_GET_TARGET_POSITION, (message_handler_func_t)get_target_position}, \
	{TYPE_SET_STEPS, (message_handler_func_t)set_steps}, \
	{TYPE_GET_STEPS, (message_handler_func_t)get_steps}, \
	{TYPE_GET_REMAINING_STEPS, (message_handler_func_t)get_remaining_steps}, \
	{TYPE_SET_STEP_MODE, (message_handler_func_t)set_step_mode}, \
	{TYPE_GET_STEP_MODE, (message_handler_func_t)get_step_mode}, \
	{TYPE_DRIVE_FORWARD, (message_handler_func_t)drive_forward}, \
	{TYPE_DRIVE_BACKWARD, (message_handler_func_t)drive_backward}, \
	{TYPE_STOP, (message_handler_func_t)stop}, \
	{TYPE_GET_STACK_INPUT_VOLTAGE, (message_handler_func_t)get_stack_input_voltage}, \
	{TYPE_GET_EXTERNAL_INPUT_VOLTAGE, (message_handler_func_t)get_external_input_voltage}, \
	{TYPE_GET_CURRENT_CONSUMPTION, (message_handler_func_t)get_current_consumption}, \
	{TYPE_SET_MOTOR_CURRENT, (message_handler_func_t)set_motor_current}, \
	{TYPE_GET_MOTOR_CURRENT, (message_handler_func_t)get_motor_current}, \
	{TYPE_ENABLE, (message_handler_func_t)enable}, \
	{TYPE_DISABLE, (message_handler_func_t)disable}, \
	{TYPE_IS_ENABLED, (message_handler_func_t)is_enabled}, \
	{TYPE_SET_DECAY, (message_handler_func_t)set_decay}, \
	{TYPE_GET_DECAY, (message_handler_func_t)get_decay}, \
	{TYPE_SET_MINIMUM_VOLTAGE, (message_handler_func_t)set_minimum_voltage}, \
	{TYPE_GET_MINIMUM_VOLTAGE, (message_handler_func_t)get_minimum_voltage}, \
	{TYPE_UNDER_VOLTAGE, (message_handler_func_t)NULL}, \
	{TYPE_POSITION_REACHED, (message_handler_func_t)NULL}, \
	{TYPE_SET_SYNC_RECT, (message_handler_func_t)set_sync_rect}, \
	{TYPE_IS_SYNC_RECT, (message_handler_func_t)is_sync_rect},


typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	uint16_t velocity;
} __attribute__((__packed__)) SetMaxVelocity;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) GetMaxVelocity;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	uint16_t velocity;
} __attribute__((__packed__)) GetMaxVelocityReturn;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) GetCurrentVelocity;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	uint16_t velocity;
} __attribute__((__packed__)) GetCurrentVelocityReturn;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	uint16_t acceleration;
	uint16_t deceleration;
} __attribute__((__packed__)) SetSpeedRamping;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) GetSpeedRamping;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	uint16_t acceleration;
	uint16_t deceleration;
} __attribute__((__packed__)) GetSpeedRampingReturn;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) FullBrake;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	int32_t position;
} __attribute__((__packed__)) SetCurrentPosition;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) GetCurrentPosition;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	int32_t position;
} __attribute__((__packed__)) GetCurrentPositionReturn;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	int32_t position;
} __attribute__((__packed__)) SetTargetPosition;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) GetTargetPosition;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	int32_t position;
} __attribute__((__packed__)) GetTargetPositionReturn;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	int32_t steps;
} __attribute__((__packed__)) SetSteps;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) GetSteps;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	int32_t steps;
} __attribute__((__packed__)) GetStepsReturn;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) GetRemainingSteps;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	int32_t steps;
} __attribute__((__packed__)) GetRemainingStepsReturn;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	uint8_t mode;
} __attribute__((__packed__)) SetStepMode;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) GetStepMode;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	uint8_t mode;
} __attribute__((__packed__)) GetStepModeReturn;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) DriveForward;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) DriveBackward;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) Stop;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) GetStackInputVoltage;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} __attribute__((__packed__)) GetStackInputVoltageReturn;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) GetExternalInputVoltage;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} __attribute__((__packed__)) GetExternalInputVoltageReturn;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) GetCurrentConsumption;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	uint16_t current;
} __attribute__((__packed__)) GetCurrentConsumptionReturn;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	uint16_t current;
} __attribute__((__packed__)) SetMotorCurrent;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) GetMotorCurrent;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	uint16_t current;
} __attribute__((__packed__)) GetMotorCurrentReturn;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) Enable;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) Disable;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) IsEnabled;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	bool enabled;
} __attribute__((__packed__)) IsEnabledReturn;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	uint16_t decay;
} __attribute__((__packed__)) SetDecay;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) GetDecay;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	uint16_t decay;
} __attribute__((__packed__)) GetDecayReturn;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} __attribute__((__packed__)) SetMinimumVoltage;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) GetMinimumVoltage;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} __attribute__((__packed__)) GetMinimumVoltageReturn;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	int16_t voltage;
} __attribute__((__packed__)) UnderVoltageSignal;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	int32_t position;
} __attribute__((__packed__)) PositionReachedSignal;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	bool sync_rect;
} __attribute__((__packed__)) SetSyncRect;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
} __attribute__((__packed__)) IsSyncRect;

typedef struct {
	uint8_t stack_address;
	uint8_t type;
	uint16_t length;
	bool sync_rect;
} __attribute__((__packed__)) IsSyncRectReturn;

void set_max_velocity(uint8_t com, const SetMaxVelocity *data);
void get_max_velocity(uint8_t com, const GetMaxVelocity *data);
void get_current_velocity(uint8_t com, const GetCurrentVelocity *data);
void set_speed_ramping(uint8_t com, const SetSpeedRamping *data);
void get_speed_ramping(uint8_t com, const GetSpeedRamping *data);
void full_brake(uint8_t com, const FullBrake *data);
void set_current_position(uint8_t com, const SetCurrentPosition *data);
void get_current_position(uint8_t com, const GetCurrentPosition *data);
void set_target_position(uint8_t com, const SetTargetPosition *data);
void get_target_position(uint8_t com, const GetTargetPosition *data);
void set_steps(uint8_t com, const SetSteps *data);
void get_steps(uint8_t com, const GetSteps *data);
void get_remaining_steps(uint8_t com, const GetRemainingSteps *data);
void set_step_mode(uint8_t com, const SetStepMode *data);
void get_step_mode(uint8_t com, const GetStepMode *data);
void drive_forward(uint8_t com, const DriveForward *data);
void drive_backward(uint8_t com, const DriveBackward *data);
void stop(uint8_t com, const Stop *data);
void get_stack_input_voltage(uint8_t com, const GetStackInputVoltage *data);
void get_external_input_voltage(uint8_t com, const GetExternalInputVoltage *data);
void get_current_consumption(uint8_t com, const GetCurrentConsumption *data);
void set_motor_current(uint8_t com, const SetMotorCurrent *data);
void get_motor_current(uint8_t com, const GetMotorCurrent *data);
void set_decay(uint8_t com, const SetDecay *data);
void get_decay(uint8_t com, const GetDecay *data);
void enable(uint8_t com, const Enable *data);
void disable(uint8_t com, const Disable *data);
void is_enabled(uint8_t com, const IsEnabled *data);
void set_minimum_voltage(uint8_t com, const SetMinimumVoltage *data);
void get_minimum_voltage(uint8_t com, const GetMinimumVoltage *data);
void set_sync_rect(uint8_t com, const SetSyncRect *data);
void is_sync_rect(uint8_t com, const IsSyncRect *data);

#endif
