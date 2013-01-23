/* stepper-brick
 * Copyright (C) 2010-2012 Olaf Lüke <olaf@tinkerforge.com>
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

#include "bricklib/com/com_common.h"

#define FID_SET_MAX_VELOCITY 1
#define FID_GET_MAX_VELOCITY 2
#define FID_GET_CURRENT_VELOCITY 3
#define FID_SET_SPEED_RAMPING 4
#define FID_GET_SPEED_RAMPING 5
#define FID_FULL_BRAKE 6
#define FID_SET_CURRENT_POSITION 7
#define FID_GET_CURRENT_POSITION 8
#define FID_SET_TARGET_POSITION 9
#define FID_GET_TARGET_POSITION 10
#define FID_SET_STEPS 11
#define FID_GET_STEPS 12
#define FID_GET_REMAINING_STEPS 13
#define FID_SET_STEP_MODE 14
#define FID_GET_STEP_MODE 15
#define FID_DRIVE_FORWARD 16
#define FID_DRIVE_BACKWARD 17
#define FID_STOP 18
#define FID_GET_STACK_INPUT_VOLTAGE 19
#define FID_GET_EXTERNAL_INPUT_VOLTAGE 20
#define FID_GET_CURRENT_CONSUMPTION 21
#define FID_SET_MOTOR_CURRENT 22
#define FID_GET_MOTOR_CURRENT 23
#define FID_ENABLE 24
#define FID_DISABLE 25
#define FID_IS_ENABLED 26
#define FID_SET_DECAY 27
#define FID_GET_DECAY 28
#define FID_SET_MINIMUM_VOLTAGE 29
#define FID_GET_MINIMUM_VOLTAGE 30
#define FID_UNDER_VOLTAGE 31
#define FID_POSITION_REACHED 32
#define FID_SET_SYNC_RECT 33
#define FID_IS_SYNC_RECT 34
#define FID_SET_TIME_BASE 35
#define FID_GET_TIME_BASE 36
#define FID_GET_ALL_DATA 37
#define FID_SET_ALL_DATA_PERIOD 38
#define FID_GET_ALL_DATA_PERIOD 39
#define FID_ALL_DATA 40
#define FID_NEW_STATE 41

#define COM_MESSAGES_USER \
	{FID_SET_MAX_VELOCITY, (message_handler_func_t)set_max_velocity}, \
	{FID_GET_MAX_VELOCITY, (message_handler_func_t)get_max_velocity}, \
	{FID_GET_CURRENT_VELOCITY, (message_handler_func_t)get_current_velocity}, \
	{FID_SET_SPEED_RAMPING, (message_handler_func_t)set_speed_ramping}, \
	{FID_GET_SPEED_RAMPING, (message_handler_func_t)get_speed_ramping}, \
	{FID_FULL_BRAKE, (message_handler_func_t)full_brake}, \
	{FID_SET_CURRENT_POSITION, (message_handler_func_t)set_current_position}, \
	{FID_GET_CURRENT_POSITION, (message_handler_func_t)get_current_position}, \
	{FID_SET_TARGET_POSITION, (message_handler_func_t)set_target_position}, \
	{FID_GET_TARGET_POSITION, (message_handler_func_t)get_target_position}, \
	{FID_SET_STEPS, (message_handler_func_t)set_steps}, \
	{FID_GET_STEPS, (message_handler_func_t)get_steps}, \
	{FID_GET_REMAINING_STEPS, (message_handler_func_t)get_remaining_steps}, \
	{FID_SET_STEP_MODE, (message_handler_func_t)set_step_mode}, \
	{FID_GET_STEP_MODE, (message_handler_func_t)get_step_mode}, \
	{FID_DRIVE_FORWARD, (message_handler_func_t)drive_forward}, \
	{FID_DRIVE_BACKWARD, (message_handler_func_t)drive_backward}, \
	{FID_STOP, (message_handler_func_t)stop}, \
	{FID_GET_STACK_INPUT_VOLTAGE, (message_handler_func_t)get_stack_input_voltage}, \
	{FID_GET_EXTERNAL_INPUT_VOLTAGE, (message_handler_func_t)get_external_input_voltage}, \
	{FID_GET_CURRENT_CONSUMPTION, (message_handler_func_t)get_current_consumption}, \
	{FID_SET_MOTOR_CURRENT, (message_handler_func_t)set_motor_current}, \
	{FID_GET_MOTOR_CURRENT, (message_handler_func_t)get_motor_current}, \
	{FID_ENABLE, (message_handler_func_t)enable}, \
	{FID_DISABLE, (message_handler_func_t)disable}, \
	{FID_IS_ENABLED, (message_handler_func_t)is_enabled}, \
	{FID_SET_DECAY, (message_handler_func_t)set_decay}, \
	{FID_GET_DECAY, (message_handler_func_t)get_decay}, \
	{FID_SET_MINIMUM_VOLTAGE, (message_handler_func_t)set_minimum_voltage}, \
	{FID_GET_MINIMUM_VOLTAGE, (message_handler_func_t)get_minimum_voltage}, \
	{FID_UNDER_VOLTAGE, (message_handler_func_t)NULL}, \
	{FID_POSITION_REACHED, (message_handler_func_t)NULL}, \
	{FID_SET_SYNC_RECT, (message_handler_func_t)set_sync_rect}, \
	{FID_IS_SYNC_RECT, (message_handler_func_t)is_sync_rect}, \
	{FID_SET_TIME_BASE, (message_handler_func_t)set_time_base}, \
	{FID_GET_TIME_BASE, (message_handler_func_t)get_time_base}, \
	{FID_GET_ALL_DATA, (message_handler_func_t)get_all_data}, \
	{FID_SET_ALL_DATA_PERIOD, (message_handler_func_t)set_all_data_period}, \
	{FID_GET_ALL_DATA_PERIOD, (message_handler_func_t)get_all_data_period}, \
	{FID_ALL_DATA, (message_handler_func_t)NULL}, \
	{FID_NEW_STATE, (message_handler_func_t)NULL},


typedef struct {
	MessageHeader header;
	uint16_t velocity;
} __attribute__((__packed__)) SetMaxVelocity;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetMaxVelocity;

typedef struct {
	MessageHeader header;
	uint16_t velocity;
} __attribute__((__packed__)) GetMaxVelocityReturn;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetCurrentVelocity;

typedef struct {
	MessageHeader header;
	uint16_t velocity;
} __attribute__((__packed__)) GetCurrentVelocityReturn;

typedef struct {
	MessageHeader header;
	uint16_t acceleration;
	uint16_t deceleration;
} __attribute__((__packed__)) SetSpeedRamping;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetSpeedRamping;

typedef struct {
	MessageHeader header;
	uint16_t acceleration;
	uint16_t deceleration;
} __attribute__((__packed__)) GetSpeedRampingReturn;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) FullBrake;

typedef struct {
	MessageHeader header;
	int32_t position;
} __attribute__((__packed__)) SetCurrentPosition;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetCurrentPosition;

typedef struct {
	MessageHeader header;
	int32_t position;
} __attribute__((__packed__)) GetCurrentPositionReturn;

typedef struct {
	MessageHeader header;
	int32_t position;
} __attribute__((__packed__)) SetTargetPosition;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetTargetPosition;

typedef struct {
	MessageHeader header;
	int32_t position;
} __attribute__((__packed__)) GetTargetPositionReturn;

typedef struct {
	MessageHeader header;
	int32_t steps;
} __attribute__((__packed__)) SetSteps;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetSteps;

typedef struct {
	MessageHeader header;
	int32_t steps;
} __attribute__((__packed__)) GetStepsReturn;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetRemainingSteps;

typedef struct {
	MessageHeader header;
	int32_t steps;
} __attribute__((__packed__)) GetRemainingStepsReturn;

typedef struct {
	MessageHeader header;
	uint8_t mode;
} __attribute__((__packed__)) SetStepMode;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetStepMode;

typedef struct {
	MessageHeader header;
	uint8_t mode;
} __attribute__((__packed__)) GetStepModeReturn;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) DriveForward;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) DriveBackward;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) Stop;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetStackInputVoltage;

typedef struct {
	MessageHeader header;
	uint16_t voltage;
} __attribute__((__packed__)) GetStackInputVoltageReturn;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetExternalInputVoltage;

typedef struct {
	MessageHeader header;
	uint16_t voltage;
} __attribute__((__packed__)) GetExternalInputVoltageReturn;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetCurrentConsumption;

typedef struct {
	MessageHeader header;
	uint16_t current;
} __attribute__((__packed__)) GetCurrentConsumptionReturn;

typedef struct {
	MessageHeader header;
	uint16_t current;
} __attribute__((__packed__)) SetMotorCurrent;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetMotorCurrent;

typedef struct {
	MessageHeader header;
	uint16_t current;
} __attribute__((__packed__)) GetMotorCurrentReturn;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) Enable;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) Disable;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) IsEnabled;

typedef struct {
	MessageHeader header;
	bool enabled;
} __attribute__((__packed__)) IsEnabledReturn;

typedef struct {
	MessageHeader header;
	uint16_t decay;
} __attribute__((__packed__)) SetDecay;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetDecay;

typedef struct {
	MessageHeader header;
	uint16_t decay;
} __attribute__((__packed__)) GetDecayReturn;

typedef struct {
	MessageHeader header;
	uint16_t voltage;
} __attribute__((__packed__)) SetMinimumVoltage;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetMinimumVoltage;

typedef struct {
	MessageHeader header;
	uint16_t voltage;
} __attribute__((__packed__)) GetMinimumVoltageReturn;

typedef struct {
	MessageHeader header;
	int16_t voltage;
} __attribute__((__packed__)) UnderVoltageSignal;

typedef struct {
	MessageHeader header;
	int32_t position;
} __attribute__((__packed__)) PositionReachedSignal;

typedef struct {
	MessageHeader header;
	bool sync_rect;
} __attribute__((__packed__)) SetSyncRect;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) IsSyncRect;

typedef struct {
	MessageHeader header;
	bool sync_rect;
} __attribute__((__packed__)) IsSyncRectReturn;

typedef struct {
	MessageHeader header;
	uint32_t time_base;
} __attribute__((__packed__)) SetTimeBase;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetTimeBase;

typedef struct {
	MessageHeader header;
	uint32_t time_base;
} __attribute__((__packed__)) GetTimeBaseReturn;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetAllData;

typedef struct {
	MessageHeader header;
	uint16_t current_velocity;
	int32_t current_position;
	int32_t remaining_steps;
	uint16_t stack_voltage;
	uint16_t external_voltage;
	uint16_t current_consumption;
} __attribute__((__packed__)) GetAllDataReturn;

typedef struct {
	MessageHeader header;
	uint32_t period;
} __attribute__((__packed__)) SetAllDataPeriod;

typedef struct {
	MessageHeader header;
} __attribute__((__packed__)) GetAllDataPeriod;

typedef struct {
	MessageHeader header;
	uint32_t period;
} __attribute__((__packed__)) GetAllDataPeriodReturn;

typedef struct {
	MessageHeader header;
	uint16_t current_velocity;
	int32_t current_position;
	int32_t remaining_steps;
	uint16_t stack_voltage;
	uint16_t external_voltage;
	uint16_t current_consumption;
} __attribute__((__packed__)) AllDataSignal;

typedef struct {
	MessageHeader header;
	uint8_t state_new;
	uint8_t state_previous;
} __attribute__((__packed__)) NewStateSignal;

void set_max_velocity(const ComType com, const SetMaxVelocity *data);
void get_max_velocity(const ComType com, const GetMaxVelocity *data);
void get_current_velocity(const ComType com, const GetCurrentVelocity *data);
void set_speed_ramping(const ComType com, const SetSpeedRamping *data);
void get_speed_ramping(const ComType com, const GetSpeedRamping *data);
void full_brake(const ComType com, const FullBrake *data);
void set_current_position(const ComType com, const SetCurrentPosition *data);
void get_current_position(const ComType com, const GetCurrentPosition *data);
void set_target_position(const ComType com, const SetTargetPosition *data);
void get_target_position(const ComType com, const GetTargetPosition *data);
void set_steps(const ComType com, const SetSteps *data);
void get_steps(const ComType com, const GetSteps *data);
void get_remaining_steps(const ComType com, const GetRemainingSteps *data);
void set_step_mode(const ComType com, const SetStepMode *data);
void get_step_mode(const ComType com, const GetStepMode *data);
void drive_forward(const ComType com, const DriveForward *data);
void drive_backward(const ComType com, const DriveBackward *data);
void stop(const ComType com, const Stop *data);
void get_stack_input_voltage(const ComType com, const GetStackInputVoltage *data);
void get_external_input_voltage(const ComType com, const GetExternalInputVoltage *data);
void get_current_consumption(const ComType com, const GetCurrentConsumption *data);
void set_motor_current(const ComType com, const SetMotorCurrent *data);
void get_motor_current(const ComType com, const GetMotorCurrent *data);
void set_decay(const ComType com, const SetDecay *data);
void get_decay(const ComType com, const GetDecay *data);
void enable(const ComType com, const Enable *data);
void disable(const ComType com, const Disable *data);
void is_enabled(const ComType com, const IsEnabled *data);
void set_minimum_voltage(const ComType com, const SetMinimumVoltage *data);
void get_minimum_voltage(const ComType com, const GetMinimumVoltage *data);
void set_sync_rect(const ComType com, const SetSyncRect *data);
void is_sync_rect(const ComType com, const IsSyncRect *data);
void set_time_base(const ComType com, const SetTimeBase *data);
void get_time_base(const ComType com, const GetTimeBase *data);
void get_all_data(const ComType com, const GetAllData *data);
void set_all_data_period(const ComType com, const SetAllDataPeriod *data);
void get_all_data_period(const ComType com, const GetAllDataPeriod *data);

#endif
