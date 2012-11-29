#!/usr/bin/env python
# -*- coding: utf-8 -*-  

HOST = "localhost"
PORT = 4223
UID = "a4LCLTYxDK9" # Change to your UID

from tinkerforge.ip_connection import IPConnection
from tinkerforge.brick_stepper import Stepper

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    stepper = Stepper(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    stepper.set_motor_current(800) # 800mA
    stepper.set_step_mode(8) # 1/8 step mode
    stepper.set_max_velocity(2000) # Velocity 2000 steps/s

    # Slow acceleration (500 steps/s^2), 
    # Fast deacceleration (5000 steps/s^2)
    stepper.set_speed_ramping(500, 5000) 

    stepper.enable()
    stepper.set_steps(60000) # Drive 60000 steps forward

    raw_input('Press key to exit\n') # Use input() in Python 3
