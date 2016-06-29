<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickStepper.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickStepper;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XXYYZZ'; // Change to your UID

// Use position reached callback to program random movement
function cb_positionReached($position, $user_data)
{
    $stepper = $user_data;

    if (rand(0, 1)) {
        $steps = rand(1000, 5000); // steps (forward)
        echo "Driving forward: $steps steps\n";
    } else {
        $steps = rand(-5000, -1000); // steps (backward)
        echo "Driving backward: $steps steps\n";
    }

    $vel = rand(200, 2000); // steps/s
    $acc = rand(100, 1000); // steps/s^2
    $dec = rand(100, 1000); // steps/s^2
    echo "Configuration (vel, acc, dec): $vel, $acc, $dec\n";

    $stepper->setSpeedRamping($acc, $dec);
    $stepper->setMaxVelocity($vel);
    $stepper->setSteps($steps);
}

$ipcon = new IPConnection(); // Create IP connection
$stepper = new BrickStepper(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Register position reached callback to function cb_positionReached
$stepper->registerCallback(BrickStepper::CALLBACK_POSITION_REACHED, 'cb_positionReached',
                           $stepper);

$stepper->enable(); // Enable motor power
$stepper->setSteps(1); // Drive one step forward to get things going

echo "Press ctrl+c to exit\n";
$ipcon->dispatchCallbacks(-1); // Dispatch callbacks forever

?>
