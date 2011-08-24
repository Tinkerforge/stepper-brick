/*************************************************************
 * This file was automatically generated on 2011-08-23.      *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#include "brick_stepper.h"

#include <string.h>

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

typedef void (*under_voltage_func_t)(uint16_t);
typedef void (*position_reached_func_t)(int32_t);

#ifdef _MSC_VER
	#pragma pack(push)
	#pragma pack(1)

	#define PACKED
#else
	#define PACKED __attribute__((packed))
#endif

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t velocity;
} PACKED SetMaxVelocity;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetMaxVelocity;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t velocity;
} PACKED GetMaxVelocityReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetCurrentVelocity;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t velocity;
} PACKED GetCurrentVelocityReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t acceleration;
	uint16_t deacceleration;
} PACKED SetSpeedRamping;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetSpeedRamping;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t acceleration;
	uint16_t deacceleration;
} PACKED GetSpeedRampingReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED FullBrake;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	int32_t position;
} PACKED SetCurrentPosition;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetCurrentPosition;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	int32_t position;
} PACKED GetCurrentPositionReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	int32_t position;
} PACKED SetTargetPosition;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetTargetPosition;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	int32_t position;
} PACKED GetTargetPositionReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	int32_t steps;
} PACKED SetSteps;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetSteps;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	int32_t steps;
} PACKED GetStepsReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetRemainingSteps;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	int32_t steps;
} PACKED GetRemainingStepsReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t mode;
} PACKED SetStepMode;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetStepMode;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint8_t mode;
} PACKED GetStepModeReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED DriveForward;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED DriveBackward;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED Stop;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetStackInputVoltage;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} PACKED GetStackInputVoltageReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetExternalInputVoltage;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} PACKED GetExternalInputVoltageReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetCurrentConsumption;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t current;
} PACKED GetCurrentConsumptionReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t current;
} PACKED SetMotorCurrent;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetMotorCurrent;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t current;
} PACKED GetMotorCurrentReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED Enable;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED Disable;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED IsEnabled;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	bool enabled;
} PACKED IsEnabledReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t decay;
} PACKED SetDecay;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetDecay;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t decay;
} PACKED GetDecayReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} PACKED SetMinimumVoltage;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
} PACKED GetMinimumVoltage;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} PACKED GetMinimumVoltageReturn;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	uint16_t voltage;
} PACKED UnderVoltageCallback;

typedef struct {
	uint8_t stack_id;
	uint8_t type;
	uint16_t length;
	int32_t position;
} PACKED PositionReachedCallback;

#ifdef _MSC_VER
	#pragma pack(pop)
#endif

int stepper_set_max_velocity(Stepper *stepper, uint16_t velocity) {
	if(stepper->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(stepper);

	SetMaxVelocity smv;
	smv.stack_id = stepper->stack_id;
	smv.type = TYPE_SET_MAX_VELOCITY;
	smv.length = sizeof(SetMaxVelocity);
	smv.velocity = velocity;

	ipcon_device_write(stepper, (char *)&smv, sizeof(SetMaxVelocity));

	ipcon_sem_post_write(stepper);

	return E_OK;
}

int stepper_get_max_velocity(Stepper *stepper, uint16_t *ret_velocity) {
	if(stepper->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(stepper);

	stepper->answer.type = TYPE_GET_MAX_VELOCITY;
	stepper->answer.length = sizeof(GetMaxVelocityReturn);
	GetMaxVelocity gmv;
	gmv.stack_id = stepper->stack_id;
	gmv.type = TYPE_GET_MAX_VELOCITY;
	gmv.length = sizeof(GetMaxVelocity);

	ipcon_device_write(stepper, (char *)&gmv, sizeof(GetMaxVelocity));

	if(ipcon_answer_sem_wait_timeout(stepper) != 0) {
		ipcon_sem_post_write(stepper);
		return E_TIMEOUT;
	}

	GetMaxVelocityReturn *gmvr = (GetMaxVelocityReturn *)stepper->answer.buffer;
	*ret_velocity = gmvr->velocity;

	ipcon_sem_post_write(stepper);

	return E_OK;
}

int stepper_get_current_velocity(Stepper *stepper, uint16_t *ret_velocity) {
	if(stepper->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(stepper);

	stepper->answer.type = TYPE_GET_CURRENT_VELOCITY;
	stepper->answer.length = sizeof(GetCurrentVelocityReturn);
	GetCurrentVelocity gcv;
	gcv.stack_id = stepper->stack_id;
	gcv.type = TYPE_GET_CURRENT_VELOCITY;
	gcv.length = sizeof(GetCurrentVelocity);

	ipcon_device_write(stepper, (char *)&gcv, sizeof(GetCurrentVelocity));

	if(ipcon_answer_sem_wait_timeout(stepper) != 0) {
		ipcon_sem_post_write(stepper);
		return E_TIMEOUT;
	}

	GetCurrentVelocityReturn *gcvr = (GetCurrentVelocityReturn *)stepper->answer.buffer;
	*ret_velocity = gcvr->velocity;

	ipcon_sem_post_write(stepper);

	return E_OK;
}

int stepper_set_speed_ramping(Stepper *stepper, uint16_t acceleration, uint16_t deacceleration) {
	if(stepper->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(stepper);

	SetSpeedRamping ssr;
	ssr.stack_id = stepper->stack_id;
	ssr.type = TYPE_SET_SPEED_RAMPING;
	ssr.length = sizeof(SetSpeedRamping);
	ssr.acceleration = acceleration;
	ssr.deacceleration = deacceleration;

	ipcon_device_write(stepper, (char *)&ssr, sizeof(SetSpeedRamping));

	ipcon_sem_post_write(stepper);

	return E_OK;
}

int stepper_get_speed_ramping(Stepper *stepper, uint16_t *ret_acceleration, uint16_t *ret_deacceleration) {
	if(stepper->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(stepper);

	stepper->answer.type = TYPE_GET_SPEED_RAMPING;
	stepper->answer.length = sizeof(GetSpeedRampingReturn);
	GetSpeedRamping gsr;
	gsr.stack_id = stepper->stack_id;
	gsr.type = TYPE_GET_SPEED_RAMPING;
	gsr.length = sizeof(GetSpeedRamping);

	ipcon_device_write(stepper, (char *)&gsr, sizeof(GetSpeedRamping));

	if(ipcon_answer_sem_wait_timeout(stepper) != 0) {
		ipcon_sem_post_write(stepper);
		return E_TIMEOUT;
	}

	GetSpeedRampingReturn *gsrr = (GetSpeedRampingReturn *)stepper->answer.buffer;
	*ret_acceleration = gsrr->acceleration;
	*ret_deacceleration = gsrr->deacceleration;

	ipcon_sem_post_write(stepper);

	return E_OK;
}

int stepper_full_brake(Stepper *stepper) {
	if(stepper->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(stepper);

	FullBrake fb;
	fb.stack_id = stepper->stack_id;
	fb.type = TYPE_FULL_BRAKE;
	fb.length = sizeof(FullBrake);

	ipcon_device_write(stepper, (char *)&fb, sizeof(FullBrake));

	ipcon_sem_post_write(stepper);

	return E_OK;
}

int stepper_set_current_position(Stepper *stepper, int32_t position) {
	if(stepper->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(stepper);

	SetCurrentPosition scp;
	scp.stack_id = stepper->stack_id;
	scp.type = TYPE_SET_CURRENT_POSITION;
	scp.length = sizeof(SetCurrentPosition);
	scp.position = position;

	ipcon_device_write(stepper, (char *)&scp, sizeof(SetCurrentPosition));

	ipcon_sem_post_write(stepper);

	return E_OK;
}

int stepper_get_current_position(Stepper *stepper, int32_t *ret_position) {
	if(stepper->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(stepper);

	stepper->answer.type = TYPE_GET_CURRENT_POSITION;
	stepper->answer.length = sizeof(GetCurrentPositionReturn);
	GetCurrentPosition gcp;
	gcp.stack_id = stepper->stack_id;
	gcp.type = TYPE_GET_CURRENT_POSITION;
	gcp.length = sizeof(GetCurrentPosition);

	ipcon_device_write(stepper, (char *)&gcp, sizeof(GetCurrentPosition));

	if(ipcon_answer_sem_wait_timeout(stepper) != 0) {
		ipcon_sem_post_write(stepper);
		return E_TIMEOUT;
	}

	GetCurrentPositionReturn *gcpr = (GetCurrentPositionReturn *)stepper->answer.buffer;
	*ret_position = gcpr->position;

	ipcon_sem_post_write(stepper);

	return E_OK;
}

int stepper_set_target_position(Stepper *stepper, int32_t position) {
	if(stepper->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(stepper);

	SetTargetPosition stp;
	stp.stack_id = stepper->stack_id;
	stp.type = TYPE_SET_TARGET_POSITION;
	stp.length = sizeof(SetTargetPosition);
	stp.position = position;

	ipcon_device_write(stepper, (char *)&stp, sizeof(SetTargetPosition));

	ipcon_sem_post_write(stepper);

	return E_OK;
}

int stepper_get_target_position(Stepper *stepper, int32_t *ret_position) {
	if(stepper->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(stepper);

	stepper->answer.type = TYPE_GET_TARGET_POSITION;
	stepper->answer.length = sizeof(GetTargetPositionReturn);
	GetTargetPosition gtp;
	gtp.stack_id = stepper->stack_id;
	gtp.type = TYPE_GET_TARGET_POSITION;
	gtp.length = sizeof(GetTargetPosition);

	ipcon_device_write(stepper, (char *)&gtp, sizeof(GetTargetPosition));

	if(ipcon_answer_sem_wait_timeout(stepper) != 0) {
		ipcon_sem_post_write(stepper);
		return E_TIMEOUT;
	}

	GetTargetPositionReturn *gtpr = (GetTargetPositionReturn *)stepper->answer.buffer;
	*ret_position = gtpr->position;

	ipcon_sem_post_write(stepper);

	return E_OK;
}

int stepper_set_steps(Stepper *stepper, int32_t steps) {
	if(stepper->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(stepper);

	SetSteps ss;
	ss.stack_id = stepper->stack_id;
	ss.type = TYPE_SET_STEPS;
	ss.length = sizeof(SetSteps);
	ss.steps = steps;

	ipcon_device_write(stepper, (char *)&ss, sizeof(SetSteps));

	ipcon_sem_post_write(stepper);

	return E_OK;
}

int stepper_get_steps(Stepper *stepper, int32_t *ret_steps) {
	if(stepper->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(stepper);

	stepper->answer.type = TYPE_GET_STEPS;
	stepper->answer.length = sizeof(GetStepsReturn);
	GetSteps gs;
	gs.stack_id = stepper->stack_id;
	gs.type = TYPE_GET_STEPS;
	gs.length = sizeof(GetSteps);

	ipcon_device_write(stepper, (char *)&gs, sizeof(GetSteps));

	if(ipcon_answer_sem_wait_timeout(stepper) != 0) {
		ipcon_sem_post_write(stepper);
		return E_TIMEOUT;
	}

	GetStepsReturn *gsr = (GetStepsReturn *)stepper->answer.buffer;
	*ret_steps = gsr->steps;

	ipcon_sem_post_write(stepper);

	return E_OK;
}

int stepper_get_remaining_steps(Stepper *stepper, int32_t *ret_steps) {
	if(stepper->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(stepper);

	stepper->answer.type = TYPE_GET_REMAINING_STEPS;
	stepper->answer.length = sizeof(GetRemainingStepsReturn);
	GetRemainingSteps grs;
	grs.stack_id = stepper->stack_id;
	grs.type = TYPE_GET_REMAINING_STEPS;
	grs.length = sizeof(GetRemainingSteps);

	ipcon_device_write(stepper, (char *)&grs, sizeof(GetRemainingSteps));

	if(ipcon_answer_sem_wait_timeout(stepper) != 0) {
		ipcon_sem_post_write(stepper);
		return E_TIMEOUT;
	}

	GetRemainingStepsReturn *grsr = (GetRemainingStepsReturn *)stepper->answer.buffer;
	*ret_steps = grsr->steps;

	ipcon_sem_post_write(stepper);

	return E_OK;
}

int stepper_set_step_mode(Stepper *stepper, uint8_t mode) {
	if(stepper->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(stepper);

	SetStepMode ssm;
	ssm.stack_id = stepper->stack_id;
	ssm.type = TYPE_SET_STEP_MODE;
	ssm.length = sizeof(SetStepMode);
	ssm.mode = mode;

	ipcon_device_write(stepper, (char *)&ssm, sizeof(SetStepMode));

	ipcon_sem_post_write(stepper);

	return E_OK;
}

int stepper_get_step_mode(Stepper *stepper, uint8_t *ret_mode) {
	if(stepper->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(stepper);

	stepper->answer.type = TYPE_GET_STEP_MODE;
	stepper->answer.length = sizeof(GetStepModeReturn);
	GetStepMode gsm;
	gsm.stack_id = stepper->stack_id;
	gsm.type = TYPE_GET_STEP_MODE;
	gsm.length = sizeof(GetStepMode);

	ipcon_device_write(stepper, (char *)&gsm, sizeof(GetStepMode));

	if(ipcon_answer_sem_wait_timeout(stepper) != 0) {
		ipcon_sem_post_write(stepper);
		return E_TIMEOUT;
	}

	GetStepModeReturn *gsmr = (GetStepModeReturn *)stepper->answer.buffer;
	*ret_mode = gsmr->mode;

	ipcon_sem_post_write(stepper);

	return E_OK;
}

int stepper_drive_forward(Stepper *stepper) {
	if(stepper->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(stepper);

	DriveForward df;
	df.stack_id = stepper->stack_id;
	df.type = TYPE_DRIVE_FORWARD;
	df.length = sizeof(DriveForward);

	ipcon_device_write(stepper, (char *)&df, sizeof(DriveForward));

	ipcon_sem_post_write(stepper);

	return E_OK;
}

int stepper_drive_backward(Stepper *stepper) {
	if(stepper->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(stepper);

	DriveBackward db;
	db.stack_id = stepper->stack_id;
	db.type = TYPE_DRIVE_BACKWARD;
	db.length = sizeof(DriveBackward);

	ipcon_device_write(stepper, (char *)&db, sizeof(DriveBackward));

	ipcon_sem_post_write(stepper);

	return E_OK;
}

int stepper_stop(Stepper *stepper) {
	if(stepper->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(stepper);

	Stop s;
	s.stack_id = stepper->stack_id;
	s.type = TYPE_STOP;
	s.length = sizeof(Stop);

	ipcon_device_write(stepper, (char *)&s, sizeof(Stop));

	ipcon_sem_post_write(stepper);

	return E_OK;
}

int stepper_get_stack_input_voltage(Stepper *stepper, uint16_t *ret_voltage) {
	if(stepper->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(stepper);

	stepper->answer.type = TYPE_GET_STACK_INPUT_VOLTAGE;
	stepper->answer.length = sizeof(GetStackInputVoltageReturn);
	GetStackInputVoltage gsiv;
	gsiv.stack_id = stepper->stack_id;
	gsiv.type = TYPE_GET_STACK_INPUT_VOLTAGE;
	gsiv.length = sizeof(GetStackInputVoltage);

	ipcon_device_write(stepper, (char *)&gsiv, sizeof(GetStackInputVoltage));

	if(ipcon_answer_sem_wait_timeout(stepper) != 0) {
		ipcon_sem_post_write(stepper);
		return E_TIMEOUT;
	}

	GetStackInputVoltageReturn *gsivr = (GetStackInputVoltageReturn *)stepper->answer.buffer;
	*ret_voltage = gsivr->voltage;

	ipcon_sem_post_write(stepper);

	return E_OK;
}

int stepper_get_external_input_voltage(Stepper *stepper, uint16_t *ret_voltage) {
	if(stepper->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(stepper);

	stepper->answer.type = TYPE_GET_EXTERNAL_INPUT_VOLTAGE;
	stepper->answer.length = sizeof(GetExternalInputVoltageReturn);
	GetExternalInputVoltage geiv;
	geiv.stack_id = stepper->stack_id;
	geiv.type = TYPE_GET_EXTERNAL_INPUT_VOLTAGE;
	geiv.length = sizeof(GetExternalInputVoltage);

	ipcon_device_write(stepper, (char *)&geiv, sizeof(GetExternalInputVoltage));

	if(ipcon_answer_sem_wait_timeout(stepper) != 0) {
		ipcon_sem_post_write(stepper);
		return E_TIMEOUT;
	}

	GetExternalInputVoltageReturn *geivr = (GetExternalInputVoltageReturn *)stepper->answer.buffer;
	*ret_voltage = geivr->voltage;

	ipcon_sem_post_write(stepper);

	return E_OK;
}

int stepper_get_current_consumption(Stepper *stepper, uint16_t *ret_current) {
	if(stepper->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(stepper);

	stepper->answer.type = TYPE_GET_CURRENT_CONSUMPTION;
	stepper->answer.length = sizeof(GetCurrentConsumptionReturn);
	GetCurrentConsumption gcc;
	gcc.stack_id = stepper->stack_id;
	gcc.type = TYPE_GET_CURRENT_CONSUMPTION;
	gcc.length = sizeof(GetCurrentConsumption);

	ipcon_device_write(stepper, (char *)&gcc, sizeof(GetCurrentConsumption));

	if(ipcon_answer_sem_wait_timeout(stepper) != 0) {
		ipcon_sem_post_write(stepper);
		return E_TIMEOUT;
	}

	GetCurrentConsumptionReturn *gccr = (GetCurrentConsumptionReturn *)stepper->answer.buffer;
	*ret_current = gccr->current;

	ipcon_sem_post_write(stepper);

	return E_OK;
}

int stepper_set_motor_current(Stepper *stepper, uint16_t current) {
	if(stepper->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(stepper);

	SetMotorCurrent smc;
	smc.stack_id = stepper->stack_id;
	smc.type = TYPE_SET_MOTOR_CURRENT;
	smc.length = sizeof(SetMotorCurrent);
	smc.current = current;

	ipcon_device_write(stepper, (char *)&smc, sizeof(SetMotorCurrent));

	ipcon_sem_post_write(stepper);

	return E_OK;
}

int stepper_get_motor_current(Stepper *stepper, uint16_t *ret_current) {
	if(stepper->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(stepper);

	stepper->answer.type = TYPE_GET_MOTOR_CURRENT;
	stepper->answer.length = sizeof(GetMotorCurrentReturn);
	GetMotorCurrent gmc;
	gmc.stack_id = stepper->stack_id;
	gmc.type = TYPE_GET_MOTOR_CURRENT;
	gmc.length = sizeof(GetMotorCurrent);

	ipcon_device_write(stepper, (char *)&gmc, sizeof(GetMotorCurrent));

	if(ipcon_answer_sem_wait_timeout(stepper) != 0) {
		ipcon_sem_post_write(stepper);
		return E_TIMEOUT;
	}

	GetMotorCurrentReturn *gmcr = (GetMotorCurrentReturn *)stepper->answer.buffer;
	*ret_current = gmcr->current;

	ipcon_sem_post_write(stepper);

	return E_OK;
}

int stepper_enable(Stepper *stepper) {
	if(stepper->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(stepper);

	Enable e;
	e.stack_id = stepper->stack_id;
	e.type = TYPE_ENABLE;
	e.length = sizeof(Enable);

	ipcon_device_write(stepper, (char *)&e, sizeof(Enable));

	ipcon_sem_post_write(stepper);

	return E_OK;
}

int stepper_disable(Stepper *stepper) {
	if(stepper->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(stepper);

	Disable d;
	d.stack_id = stepper->stack_id;
	d.type = TYPE_DISABLE;
	d.length = sizeof(Disable);

	ipcon_device_write(stepper, (char *)&d, sizeof(Disable));

	ipcon_sem_post_write(stepper);

	return E_OK;
}

int stepper_is_enabled(Stepper *stepper, bool *ret_enabled) {
	if(stepper->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(stepper);

	stepper->answer.type = TYPE_IS_ENABLED;
	stepper->answer.length = sizeof(IsEnabledReturn);
	IsEnabled ie;
	ie.stack_id = stepper->stack_id;
	ie.type = TYPE_IS_ENABLED;
	ie.length = sizeof(IsEnabled);

	ipcon_device_write(stepper, (char *)&ie, sizeof(IsEnabled));

	if(ipcon_answer_sem_wait_timeout(stepper) != 0) {
		ipcon_sem_post_write(stepper);
		return E_TIMEOUT;
	}

	IsEnabledReturn *ier = (IsEnabledReturn *)stepper->answer.buffer;
	*ret_enabled = ier->enabled;

	ipcon_sem_post_write(stepper);

	return E_OK;
}

int stepper_set_decay(Stepper *stepper, uint16_t decay) {
	if(stepper->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(stepper);

	SetDecay sd;
	sd.stack_id = stepper->stack_id;
	sd.type = TYPE_SET_DECAY;
	sd.length = sizeof(SetDecay);
	sd.decay = decay;

	ipcon_device_write(stepper, (char *)&sd, sizeof(SetDecay));

	ipcon_sem_post_write(stepper);

	return E_OK;
}

int stepper_get_decay(Stepper *stepper, uint16_t *ret_decay) {
	if(stepper->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(stepper);

	stepper->answer.type = TYPE_GET_DECAY;
	stepper->answer.length = sizeof(GetDecayReturn);
	GetDecay gd;
	gd.stack_id = stepper->stack_id;
	gd.type = TYPE_GET_DECAY;
	gd.length = sizeof(GetDecay);

	ipcon_device_write(stepper, (char *)&gd, sizeof(GetDecay));

	if(ipcon_answer_sem_wait_timeout(stepper) != 0) {
		ipcon_sem_post_write(stepper);
		return E_TIMEOUT;
	}

	GetDecayReturn *gdr = (GetDecayReturn *)stepper->answer.buffer;
	*ret_decay = gdr->decay;

	ipcon_sem_post_write(stepper);

	return E_OK;
}

int stepper_set_minimum_voltage(Stepper *stepper, uint16_t voltage) {
	if(stepper->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(stepper);

	SetMinimumVoltage smv;
	smv.stack_id = stepper->stack_id;
	smv.type = TYPE_SET_MINIMUM_VOLTAGE;
	smv.length = sizeof(SetMinimumVoltage);
	smv.voltage = voltage;

	ipcon_device_write(stepper, (char *)&smv, sizeof(SetMinimumVoltage));

	ipcon_sem_post_write(stepper);

	return E_OK;
}

int stepper_get_minimum_voltage(Stepper *stepper, uint16_t *ret_voltage) {
	if(stepper->ipcon == NULL) {
		return E_NOT_ADDED;
	}

	ipcon_sem_wait_write(stepper);

	stepper->answer.type = TYPE_GET_MINIMUM_VOLTAGE;
	stepper->answer.length = sizeof(GetMinimumVoltageReturn);
	GetMinimumVoltage gmv;
	gmv.stack_id = stepper->stack_id;
	gmv.type = TYPE_GET_MINIMUM_VOLTAGE;
	gmv.length = sizeof(GetMinimumVoltage);

	ipcon_device_write(stepper, (char *)&gmv, sizeof(GetMinimumVoltage));

	if(ipcon_answer_sem_wait_timeout(stepper) != 0) {
		ipcon_sem_post_write(stepper);
		return E_TIMEOUT;
	}

	GetMinimumVoltageReturn *gmvr = (GetMinimumVoltageReturn *)stepper->answer.buffer;
	*ret_voltage = gmvr->voltage;

	ipcon_sem_post_write(stepper);

	return E_OK;
}

int stepper_callback_under_voltage(Stepper *stepper, const unsigned char *buffer) {
	UnderVoltageCallback *uvc = (UnderVoltageCallback *)buffer;
	((under_voltage_func_t)stepper->callbacks[uvc->type])(uvc->voltage);
	return sizeof(UnderVoltageCallback);
}

int stepper_callback_position_reached(Stepper *stepper, const unsigned char *buffer) {
	PositionReachedCallback *prc = (PositionReachedCallback *)buffer;
	((position_reached_func_t)stepper->callbacks[prc->type])(prc->position);
	return sizeof(PositionReachedCallback);
}

void stepper_register_callback(Stepper *stepper, uint8_t cb, void *func) {
    stepper->callbacks[cb] = func;
}

void stepper_create(Stepper *stepper, const char *uid) {
	ipcon_device_create(stepper, uid);

	stepper->device_callbacks[TYPE_UNDER_VOLTAGE] = stepper_callback_under_voltage;
	stepper->device_callbacks[TYPE_POSITION_REACHED] = stepper_callback_position_reached;
}
