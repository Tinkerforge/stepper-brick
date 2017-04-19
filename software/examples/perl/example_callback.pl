#!/usr/bin/perl

use Tinkerforge::IPConnection;
use Tinkerforge::BrickStepper;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XXYYZZ'; # Change XXYYZZ to the UID of your Stepper Brick

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
our $stepper = Tinkerforge::BrickStepper->new(&UID, $ipcon); # Create device object

# Use position reached callback to program random movement
sub cb_position_reached
{
    my ($position) = @_;

    my $steps = 0;
    my $vel = 0;
    my $acc = 0;
    my $dec = 0;

    if (int(rand(1)))
    {
        $steps = int(rand(5000 - 1000)) + 1000; # steps (forward)
        print "Driving forward: $steps steps\n";
    }
    else
    {
        $steps = int(rand(5000 - 1000)) + 1000; # steps (backward)
        print "Driving backward: $steps steps\n";
    }

    $vel = int(rand(2000 - 200)) + 200; # steps/s
    $acc = int(rand(1000 - 100)) + 100; # steps/s^2
    $dec = int(rand(1000 - 100)) + 100; # steps/s^2
    print "Configuration (vel, acc, dec): $vel, $acc, $dec\n";

    $stepper->set_speed_ramping($acc, $dec);
    $stepper->set_max_velocity($vel);
    $stepper->set_steps($steps);
}

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Register position reached callback to subroutine cb_position_reached
$stepper->register_callback($stepper->CALLBACK_POSITION_REACHED, 'cb_position_reached');

$stepper->enable(); # Enable motor power
$stepper->set_steps(1); # Drive one step forward to get things going

print "Press key to exit\n";
<STDIN>;
$stepper->disable();
$ipcon->disconnect();
