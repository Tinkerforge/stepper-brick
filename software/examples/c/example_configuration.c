
#include <stdio.h>

#include "ip_connection.h"
#include "brick_stepper.h"

#define HOST "localhost"
#define PORT 4223
#define UID "a4LCLTYxDK9" // Change to your UID

int main() {
	// Create IP connection to brickd
	IPConnection ipcon;
	if(ipcon_create(&ipcon, HOST, PORT) < 0) {
		fprintf(stderr, "Could not create connection\n");
		exit(1);
	}

	// Create device object
	Stepper stepper;
	stepper_create(&stepper, UID); 

	// Add device to IP connection
	if(ipcon_add_device(&ipcon, &stepper) < 0) {
		fprintf(stderr, "Could not connect to Brick\n");
		exit(1);
	}
	// Don't use device before it is added to a connection

	stepper_set_motor_current(&stepper, 800); // 800mA
	stepper_set_step_mode(&stepper, 8); // 1/8 step mode
	stepper_set_max_velocity(&stepper, 2000); // Velocity 2000 steps/s

	// Slow acceleration (500 steps/s^2), 
	// Fast deacceleration (5000 steps/s^2)
	stepper_set_speed_ramping(&stepper, 500, 5000);

	stepper_enable(&stepper);
	stepper_set_steps(&stepper, 60000); // Drive 60000 steps forward

	printf("Press key to exit\n");
	getchar();
	ipcon_destroy(&ipcon);
}
