/* stepper-brick
 * Copyright (C) 2010-2012 Olaf Lüke <olaf@tinkerforge.com>
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
extern uint16_t stepper_output_current;

extern int8_t stepper_state;
extern uint32_t stepper_time_base;
extern uint32_t stepper_all_data_period;

extern bool stepper_sync_rect;

void set_max_velocity(const ComType com, const SetMaxVelocity *data) {
	uint32_t old_velocity_goal = stepper_velocity_goal;
	stepper_velocity_goal = data->velocity;

	if(stepper_state == STEPPER_STATE_DRIVE && old_velocity_goal == 0) {
		TC0_IrqHandler();
	}

	com_return_setter(com, data);
}

void get_max_velocity(const ComType com, const GetMaxVelocity *data) {
	GetMaxVelocityReturn gmvr;

	gmvr.header        = data->header;
	gmvr.header.length = sizeof(GetMaxVelocityReturn);
	gmvr.velocity      = stepper_velocity_goal;

	send_blocking_with_timeout(&gmvr, sizeof(GetMaxVelocityReturn), com);
}

void get_current_velocity(const ComType com, const GetCurrentVelocity *data) {
	GetCurrentVelocityReturn gcvr;

	gcvr.header        = data->header;
	gcvr.header.length = sizeof(GetCurrentVelocityReturn);
	gcvr.velocity      = stepper_velocity > 0xFFFF ? 0xFFFF : stepper_velocity;

	send_blocking_with_timeout(&gcvr, sizeof(GetCurrentVelocityReturn), com);
}

void set_speed_ramping(const ComType com, const SetSpeedRamping *data) {
	stepper_acceleration_sqrt = sqrt_integer_precise(data->acceleration);
	stepper_acceleration      = data->acceleration;
	stepper_deceleration      = data->deceleration;

	com_return_setter(com, data);
}

void get_speed_ramping(const ComType com, const GetSpeedRamping *data) {
	GetSpeedRampingReturn gsrr;

	gsrr.header        = data->header;
	gsrr.header.length = sizeof(GetSpeedRampingReturn);
	gsrr.acceleration  = stepper_acceleration;
	gsrr.deceleration  = stepper_deceleration;

	send_blocking_with_timeout(&gsrr, sizeof(GetSpeedRampingReturn), com);
}

void full_brake(const ComType com, const FullBrake *data) {
	stepper_full_brake();

	com_return_setter(com, data);
}

void set_current_position(const ComType com, const SetCurrentPosition *data) {
	stepper_position = data->position;

	com_return_setter(com, data);
}

void get_current_position(const ComType com, const GetCurrentPosition *data) {
	GetCurrentPositionReturn gcpr;

	gcpr.header        = data->header;
	gcpr.header.length = sizeof(GetCurrentPositionReturn);
	gcpr.position      = stepper_position;

	send_blocking_with_timeout(&gcpr, sizeof(GetCurrentPositionReturn), com);
}

void set_target_position(const ComType com, const SetTargetPosition *data) {
	if(stepper_is_currently_running() || stepper_state == STEPPER_STATE_OFF) {
		com_return_setter(com, data);
		return;
	}

	stepper_state = STEPPER_STATE_TARGET;
	stepper_target_position = data->position;
	stepper_make_step_speedramp(stepper_target_position - stepper_position);

	com_return_setter(com, data);
}

void get_target_position(const ComType com, const GetTargetPosition *data) {
	GetTargetPositionReturn gtpr;

	gtpr.header        = data->header;
	gtpr.header.length = sizeof(GetTargetPositionReturn);
	gtpr.position      = stepper_target_position;

	send_blocking_with_timeout(&gtpr, sizeof(GetTargetPositionReturn), com);
}

void set_steps(const ComType com, const SetSteps *data) {
	if(stepper_is_currently_running() || stepper_state == STEPPER_STATE_OFF) {
		com_return_setter(com, data);
		return;
	}

	stepper_state = STEPPER_STATE_STEPS;
	stepper_steps = data->steps;
	stepper_make_step_speedramp(data->steps);

	com_return_setter(com, data);
}

void get_steps(const ComType com, const GetSteps *data) {
	GetStepsReturn gsr;

	gsr.header        = data->header;
	gsr.header.length = sizeof(GetStepsReturn);
	gsr.steps         = stepper_steps;

	send_blocking_with_timeout(&gsr, sizeof(GetStepsReturn), com);
}

void get_remaining_steps(const ComType com, const GetRemainingSteps *data) {
	GetRemainingStepsReturn grsr;

	grsr.header        = data->header;
	grsr.header.length = sizeof(GetRemainingStepsReturn);
	grsr.steps         = stepper_get_remaining_steps();

	send_blocking_with_timeout(&grsr, sizeof(GetRemainingStepsReturn), com);
}

void set_step_mode(const ComType com, const SetStepMode *data) {
	if(data->mode != 1 && data->mode != 2 && data->mode != 4 && data->mode != 8) {
		com_return_error(data, sizeof(MessageHeader), MESSAGE_ERROR_CODE_INVALID_PARAMETER, com);
		return;
	}

	stepper_set_step_mode(data->mode);

	com_return_setter(com, data);
}

void get_step_mode(const ComType com, const GetStepMode *data) {
	GetStepModeReturn gsmr;

	gsmr.header        = data->header;
	gsmr.header.length = sizeof(GetStepModeReturn);
	gsmr.mode          = stepper_get_step_mode();

	send_blocking_with_timeout(&gsmr, sizeof(GetStepModeReturn), com);
}

void drive_forward(const ComType com, const DriveForward *data) {
	if(stepper_state == STEPPER_STATE_STEPS ||
	   stepper_state == STEPPER_STATE_TARGET ||
	   stepper_state == STEPPER_STATE_OFF) {
		com_return_setter(com, data);
		return;
	}

	stepper_make_drive_speedramp(STEPPER_SPEEDRAMP_STATE_FORWARD);

	com_return_setter(com, data);
}

void drive_backward(const ComType com, const DriveBackward *data) {
	if(stepper_state == STEPPER_STATE_STEPS ||
	   stepper_state == STEPPER_STATE_TARGET ||
	   stepper_state == STEPPER_STATE_OFF) {
		com_return_setter(com, data);
		return;
	}

	stepper_make_drive_speedramp(STEPPER_SPEEDRAMP_STATE_BACKWARD);

	com_return_setter(com, data);
}

void stop(const ComType com, const Stop *data) {
	if(stepper_state == STEPPER_STATE_OFF) {
		com_return_setter(com, data);
		return;
	}

	stepper_make_drive_speedramp(STEPPER_SPEEDRAMP_STATE_STOP);
	com_return_setter(com, data);
}

void get_stack_input_voltage(const ComType com, const GetStackInputVoltage *data) {
	GetStackInputVoltageReturn gsivr;

	gsivr.header        = data->header;
	gsivr.header.length = sizeof(GetStackInputVoltageReturn);
    gsivr.voltage       = stepper_get_stack_voltage();

	send_blocking_with_timeout(&gsivr, sizeof(GetStackInputVoltageReturn), com);
}

void get_external_input_voltage(const ComType com, const GetExternalInputVoltage *data) {
	GetExternalInputVoltageReturn geivr;

	geivr.header        = data->header;
	geivr.header.length = sizeof(GetExternalInputVoltageReturn);
	geivr.voltage       = stepper_get_external_voltage();

	send_blocking_with_timeout(&geivr, sizeof(GetExternalInputVoltageReturn), com);
}

void get_current_consumption(const ComType com, const GetCurrentConsumption *data) {
	GetCurrentConsumptionReturn gccr;

	gccr.header        = data->header;
	gccr.header.length = sizeof(GetCurrentConsumptionReturn);
	gccr.current       = stepper_get_current();

	send_blocking_with_timeout(&gccr, sizeof(GetCurrentConsumptionReturn), com);
}

void set_motor_current(const ComType com, const SetMotorCurrent *data) {
	stepper_set_output_current(data->current);
	com_return_setter(com, data);
}

void get_motor_current(const ComType com, const GetMotorCurrent *data) {
	GetMotorCurrentReturn gmcr;

	gmcr.header        = data->header;
	gmcr.header.length = sizeof(GetMotorCurrentReturn);
	gmcr.current       = stepper_output_current;

	send_blocking_with_timeout(&gmcr, sizeof(GetMotorCurrentReturn), com);
}

void enable(const ComType com, const Enable *data) {
	stepper_enable();
	com_return_setter(com, data);
}

void disable(const ComType com, const Disable *data) {
	stepper_disable();
	com_return_setter(com, data);
}

void is_enabled(const ComType com, const IsEnabled *data) {
	IsEnabledReturn ier;

	ier.header        = data->header;
	ier.header.length = sizeof(IsEnabledReturn);
	ier.enabled       = stepper_state != STEPPER_STATE_OFF;

	send_blocking_with_timeout(&ier, sizeof(IsEnabledReturn), com);
}

void set_decay(const ComType com, const SetDecay *data) {
	stepper_set_decay(data->decay);
	com_return_setter(com, data);
}

void get_decay(const ComType com, const GetDecay *data) {
	GetDecayReturn gdr;

	gdr.header        = data->header;
	gdr.header.length = sizeof(GetDecayReturn);
	gdr.decay         = stepper_decay;

	send_blocking_with_timeout(&gdr, sizeof(GetDecayReturn), com);
}

void set_minimum_voltage(const ComType com, const SetMinimumVoltage *data) {
	stepper_minimum_voltage = data->voltage;
	com_return_setter(com, data);
}

void get_minimum_voltage(const ComType com, const GetMinimumVoltage *data) {
	GetMinimumVoltageReturn gmvr;

	gmvr.header        = data->header;
	gmvr.header.length = sizeof(GetMinimumVoltageReturn);
	gmvr.voltage       = stepper_minimum_voltage;

	send_blocking_with_timeout(&gmvr, sizeof(GetMinimumVoltageReturn), com);
}

void set_sync_rect(const ComType com, const SetSyncRect *data) {
	stepper_sync_rect = data->sync_rect;
	stepper_set_sync_rect(stepper_sync_rect);

	com_return_setter(com, data);
}

void is_sync_rect(const ComType com, const IsSyncRect *data) {
	IsSyncRectReturn isrr;

	isrr.header        = data->header;
	isrr.header.length = sizeof(IsSyncRectReturn);
	isrr.sync_rect     = stepper_sync_rect;

	send_blocking_with_timeout(&isrr, sizeof(IsSyncRectReturn), com);
}

void set_time_base(const ComType com, const SetTimeBase *data) {
	stepper_time_base = data->time_base;

	com_return_setter(com, data);
}

void get_time_base(const ComType com, const GetTimeBase *data) {
	GetTimeBaseReturn gtbr;

	gtbr.header        = data->header;
	gtbr.header.length = sizeof(GetTimeBaseReturn);
	gtbr.time_base     = stepper_time_base;

	send_blocking_with_timeout(&gtbr, sizeof(GetTimeBaseReturn), com);
}

void get_all_data(const ComType com, const GetAllData *data) {
	GetAllDataReturn gadr;

	gadr.header              = data->header;
	gadr.header.length       = sizeof(GetAllDataReturn);
	gadr.current_velocity    = stepper_velocity > 0xFFFF ? 0xFFFF : stepper_velocity;
	gadr.current_position    = stepper_position;
	gadr.remaining_steps     = stepper_get_remaining_steps();
	gadr.stack_voltage       = stepper_get_stack_voltage();
	gadr.external_voltage    = stepper_get_external_voltage();
	gadr.current_consumption = stepper_get_current();

	send_blocking_with_timeout(&gadr, sizeof(GetAllDataReturn), com);
}

void set_all_data_period(const ComType com, const SetAllDataPeriod *data) {
	stepper_all_data_period = data->period;

	com_return_setter(com, data);
}

void get_all_data_period(const ComType com, const GetAllDataPeriod *data) {
	GetAllDataPeriodReturn gadpr;

	gadpr.header        = data->header;
	gadpr.header.length = sizeof(GetAllDataPeriodReturn);
	gadpr.period        = stepper_all_data_period;

	send_blocking_with_timeout(&gadpr, sizeof(GetAllDataPeriodReturn), com);
}
