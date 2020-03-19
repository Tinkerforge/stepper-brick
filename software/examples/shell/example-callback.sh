#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XXYYZZ # Change XXYYZZ to the UID of your Stepper Brick

# Use position reached callback to program random movement
tinkerforge dispatch stepper-brick $uid position-reached\
 --execute "echo Changing configuration;
            tinkerforge call stepper-brick $uid set-max-velocity $(((RANDOM%1800)+1200));
            tinkerforge call stepper-brick $uid set-speed-ramping $(((RANDOM%900)+100)) $(((RANDOM%900)+100));
            if [ $((RANDOM % 2)) -eq 1 ];
            then tinkerforge call stepper-brick $uid set-steps $(((RANDOM%4000)+1000));
            else tinkerforge call stepper-brick $uid set-steps $(((RANDOM%4000)-5000));
            fi" &

tinkerforge call stepper-brick $uid enable # Enable motor power
tinkerforge call stepper-brick $uid set-steps 1 # Drive one step forward to get things going

echo "Press key to exit"; read dummy

# Stop motor before disabling motor power
tinkerforge call stepper-brick $uid stop # Request motor stop
tinkerforge call stepper-brick $uid set-speed-ramping 500 5000 # Fast deacceleration (5000 steps/s^2) for stopping
sleep 0.4 # Wait for motor to actually stop: max velocity (2000 steps/s) / decceleration (5000 steps/s^2) = 0.4 s
tinkerforge call stepper-brick $uid disable # Disable motor power

kill -- -$$ # Stop callback dispatch in background
