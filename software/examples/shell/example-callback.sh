#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XXYYZZ # Change to your UID

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

tinkerforge call stepper-brick $uid disable

kill -- -$$ # Stop callback dispatch in background
