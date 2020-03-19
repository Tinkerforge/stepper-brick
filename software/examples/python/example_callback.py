#!/usr/bin/env python
# -*- coding: utf-8 -*-

HOST = "localhost"
PORT = 4223
UID = "XXYYZZ" # Change XXYYZZ to the UID of your Stepper Brick

import time
import random

from tinkerforge.ip_connection import IPConnection
from tinkerforge.brick_stepper import BrickStepper

# Use position reached callback to program random movement
def cb_position_reached(position, stepper):
    if random.randint(0, 1):
        steps = random.randint(1000, 5000) # steps (forward)
        print("Driving forward: " + str(steps) + " steps")
    else:
        steps = random.randint(-5000, -1000) # steps (backward)
        print("Driving backward: " + str(steps) + " steps")

    vel = random.randint(200, 2000) # steps/s
    acc = random.randint(100, 1000) # steps/s^2
    dec = random.randint(100, 1000) # steps/s^2
    print("Configuration (vel, acc, dec): " + str((vel, acc, dec)))

    stepper.set_speed_ramping(acc, dec)
    stepper.set_max_velocity(vel)
    stepper.set_steps(steps)

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    stepper = BrickStepper(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    # Register position reached callback to function cb_position_reached
    stepper.register_callback(stepper.CALLBACK_POSITION_REACHED,
                              lambda x: cb_position_reached(x, stepper))

    stepper.enable() # Enable motor power
    stepper.set_steps(1) # Drive one step forward to get things going

    input("Press key to exit\n") # Use raw_input() in Python 2

    # Stop motor before disabling motor power
    stepper.stop() # Request motor stop
    stepper.set_speed_ramping(500,
                              5000) # Fast deacceleration (5000 steps/s^2) for stopping
    time.sleep(0.4) # Wait for motor to actually stop: max velocity (2000 steps/s) / decceleration (5000 steps/s^2) = 0.4 s
    stepper.disable() # Disable motor power

    ipcon.disconnect()
