#!/bin/sh
# connects to localhost:4223 by default, use --host and --port to change it

# change to your UID
uid=XYZ

tinkerforge call stepper-brick $uid enable

# drive some steps forward to get things going
tinkerforge call stepper-brick $uid set-steps 100

# use position-reached callback to program random movement 
tinkerforge dispatch stepper-brick $uid position-reached\
 --execute "echo Changing configuration;
            tinkerforge call stepper-brick $uid set-max-velocity $(((RANDOM % 1800) + 1200));
            tinkerforge call stepper-brick $uid set-speed-ramping $(((RANDOM % 900) + 100)) $(((RANDOM % 900) + 100));
            if [ $((RANDOM % 2)) -eq 1 ];
            then tinkerforge call stepper-brick $uid set-steps $(((RANDOM % 4000) + 1000));
            else tinkerforge call stepper-brick $uid set-steps $(((RANDOM % 4000) - 5000));
            fi"
