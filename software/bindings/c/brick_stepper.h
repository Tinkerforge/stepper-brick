/*************************************************************
 * This file was automatically generated on 23.08.2011.      *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

#ifndef BRICK_STEPPER_H
#define BRICK_STEPPER_H

#include "ip_connection.h"

typedef Device Stepper;

#define STEPPER_CALLBACK_UNDER_VOLTAGE 31
#define STEPPER_CALLBACK_POSITION_REACHED 32

void stepper_create(Stepper *stepper, const char *uid);

int stepper_set_max_velocity(Stepper *stepper, uint16_t velocity);
int stepper_get_max_velocity(Stepper *stepper, uint16_t *ret_velocity);
int stepper_get_current_velocity(Stepper *stepper, uint16_t *ret_velocity);
int stepper_set_speed_ramping(Stepper *stepper, uint16_t acceleration, uint16_t deacceleration);
int stepper_get_speed_ramping(Stepper *stepper, uint16_t *ret_acceleration, uint16_t *ret_deacceleration);
int stepper_full_brake(Stepper *stepper);
int stepper_set_current_position(Stepper *stepper, int32_t position);
int stepper_get_current_position(Stepper *stepper, int32_t *ret_position);
int stepper_set_target_position(Stepper *stepper, int32_t position);
int stepper_get_target_position(Stepper *stepper, int32_t *ret_position);
int stepper_set_steps(Stepper *stepper, int32_t steps);
int stepper_get_steps(Stepper *stepper, int32_t *ret_steps);
int stepper_get_remaining_steps(Stepper *stepper, int32_t *ret_steps);
int stepper_set_step_mode(Stepper *stepper, uint8_t mode);
int stepper_get_step_mode(Stepper *stepper, uint8_t *ret_mode);
int stepper_drive_forward(Stepper *stepper);
int stepper_drive_backward(Stepper *stepper);
int stepper_stop(Stepper *stepper);
int stepper_get_stack_input_voltage(Stepper *stepper, uint16_t *ret_voltage);
int stepper_get_external_input_voltage(Stepper *stepper, uint16_t *ret_voltage);
int stepper_get_current_consumption(Stepper *stepper, uint16_t *ret_current);
int stepper_set_motor_current(Stepper *stepper, uint16_t current);
int stepper_get_motor_current(Stepper *stepper, uint16_t *ret_current);
int stepper_enable(Stepper *stepper);
int stepper_disable(Stepper *stepper);
int stepper_is_enabled(Stepper *stepper, bool *ret_enabled);
int stepper_set_decay(Stepper *stepper, uint16_t decay);
int stepper_get_decay(Stepper *stepper, uint16_t *ret_decay);
int stepper_set_minimum_voltage(Stepper *stepper, uint16_t voltage);
int stepper_get_minimum_voltage(Stepper *stepper, uint16_t *ret_voltage);
int stepper_under_voltage(Stepper *stepper, uint16_t *ret_voltage);
int stepper_position_reached(Stepper *stepper, int32_t *ret_position);

void stepper_register_callback(Stepper *stepper, uint8_t cb, void *func);

#endif