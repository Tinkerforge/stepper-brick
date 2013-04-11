#!/usr/bin/env python
# -*- coding: utf-8 -*-  

HOST = "localhost"
PORT = 4223
UID = "a4LCLTYxDK9" # Change to your UID

from tinkerforge.ip_connection import IPConnection
from tinkerforge.brick_stepper import Stepper

import random

ipcon = IPConnection() # Create IP connection
stepper = Stepper(UID, ipcon) # Create device object

# Use position reached callback to program random movement
def cb_reached(position):
    if random.randint(0, 1):
        steps = random.randint(1000, 5000) # steps (forward)
        print('Driving forward: ' + str(steps) + ' steps')
    else:
        steps = random.randint(-5000, -1000) # steps (backward)
        print('Driving backward: ' + str(steps) + ' steps')

    vel = random.randint(200, 2000) # steps/s
    acc = random.randint(100, 1000) # steps/s^2
    dec = random.randint(100, 1000) # steps/s^2
    print('Configuration (vel, acc, dec): ' + str((vel, acc, dec)))

    stepper.set_speed_ramping(acc, dec)
    stepper.set_max_velocity(vel)
    stepper.set_steps(steps)

if __name__ == "__main__":
    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    # Register "position reached callback" to cb_reached
    # cb_reached will be called every time a position set with
    # set_steps or set_target_position is reached
    stepper.register_callback(stepper.CALLBACK_POSITION_REACHED, cb_reached)

    stepper.enable()
    stepper.set_steps(1) # Drive one step forward to get things going

    raw_input('Press key to exit\n') # Use input() in Python 3
    ipcon.disconnect()
