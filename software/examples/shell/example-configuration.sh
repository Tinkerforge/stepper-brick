#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XXYYZZ # Change XXYYZZ to the UID of your Stepper Brick

tinkerforge call stepper-brick $uid set-motor-current 800 # 800mA
tinkerforge call stepper-brick $uid set-step-mode step-mode-eighth-step # 1/8 step mode
tinkerforge call stepper-brick $uid set-max-velocity 2000 # Velocity 2000 steps/s

# Slow acceleration (500 steps/s^2),
# Fast deacceleration (5000 steps/s^2)
tinkerforge call stepper-brick $uid set-speed-ramping 500 5000

tinkerforge call stepper-brick $uid enable # Enable motor power
tinkerforge call stepper-brick $uid set-steps 60000 # Drive 60000 steps forward

echo "Press key to exit"; read dummy

tinkerforge call stepper-brick $uid disable
