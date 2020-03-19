#!/usr/bin/env python
# -*- coding: utf-8 -*-

HOST = "localhost"
PORT = 4223
UID = "XXYYZZ" # Change XXYYZZ to the UID of your Stepper Brick

import time

from tinkerforge.ip_connection import IPConnection
from tinkerforge.brick_stepper import BrickStepper

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    stepper = BrickStepper(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    stepper.set_motor_current(800) # 800 mA
    stepper.set_step_mode(8) # 1/8 step mode
    stepper.set_max_velocity(2000) # Velocity 2000 steps/s

    # Slow acceleration (500 steps/s^2),
    # Fast deacceleration (5000 steps/s^2)
    stepper.set_speed_ramping(500, 5000)

    stepper.enable() # Enable motor power
    stepper.set_steps(60000) # Drive 60000 steps forward

    input("Press key to exit\n") # Use raw_input() in Python 2

    # Stop motor before disabling motor power
    stepper.stop() # Request motor stop
    stepper.set_speed_ramping(500,
                              5000) # Fast deacceleration (5000 steps/s^2) for stopping
    time.sleep(0.4) # Wait for motor to actually stop: max velocity (2000 steps/s) / decceleration (5000 steps/s^2) = 0.4 s
    stepper.disable() # Disable motor power

    ipcon.disconnect()
