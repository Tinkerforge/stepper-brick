
#include <stdio.h>
#include <stdlib.h>

#include "ip_connection.h"
#include "brick_stepper.h"

#define HOST "localhost"
#define PORT 4223
#define UID "a4LCLTYxDK9" // Change to your UID

// Use position reached callback to program random movement 
void cb_reached(int32_t position, void *user_data) {
	Stepper *stepper = (Stepper *)user_data;
	int32_t steps;

	(void)position;

	if(rand() % 2) {
		steps = (rand() % 4000) + 1000; // steps (forward)
		printf("Driving forward: %d steps\n", steps);
	} else {
		steps = -((rand() % 4000) + 1000); // steps (backward)
		printf("Driving backward: %d steps\n", steps);
	}

	int16_t vel = (rand() % 1800) + 200; // steps/s
	uint16_t acc = (rand() % 900) + 100; // steps/s^2
	uint16_t dec = (rand() % 900) + 100; // steps/s^2
	printf("Configuration (vel, acc, dec): %d, %d %d\n", vel, acc, dec);

	stepper_set_speed_ramping(stepper, acc, dec);
	stepper_set_max_velocity(stepper, vel);
	stepper_set_steps(stepper, steps);
}

int main() {
	// Create IP connection
	IPConnection ipcon;
	ipcon_create(&ipcon);

	// Create device object
	Stepper stepper;
	stepper_create(&stepper, UID, &ipcon);

	// Connect to brickd
	if(ipcon_connect(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not connect\n");
		exit(1);
	}
	// Don't use device before ipcon is connected

	// Register "position reached callback" to cb_reached
	// cb_reached will be called every time a position set with
	// set_steps or set_target_position is reached
	stepper_register_callback(&stepper,
	                          STEPPER_CALLBACK_POSITION_REACHED,
	                          (void *)cb_reached,
	                          &stepper);

	stepper_enable(&stepper);
	// Drive one step forward to get things going
	stepper_set_steps(&stepper, 1);

	printf("Press key to exit\n");
	getchar();
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
}
