#!/bin/sh
# connects to localhost:4223 by default, use --host and --port to change it

# change to your UID
uid=XYZ

tinkerforge call stepper-brick $uid set-motor-current 800 # 800mA
tinkerforge call stepper-brick $uid set-step-mode 8 # 1/8 step mode
tinkerforge call stepper-brick $uid set-max-velocity 2000 # velocity 2000 steps/s

# slow acceleration (500 steps/s^2), 
# fast deacceleration (5000 steps/s^2)
tinkerforge call stepper-brick $uid set-speed-ramping 500 5000

tinkerforge call stepper-brick $uid enable
tinkerforge call stepper-brick $uid set-steps 60000 # drive 60000 steps forward
