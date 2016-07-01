<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickStepper.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickStepper;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XXYYZZ'; // Change XXYYZZ to the UID of your Stepper Brick

$ipcon = new IPConnection(); // Create IP connection
$stepper = new BrickStepper(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

$stepper->setMotorCurrent(800); // 800mA
$stepper->setStepMode(8); // 1/8 step mode
$stepper->setMaxVelocity(2000); // Velocity 2000 steps/s

// Slow acceleration (500 steps/s^2),
// Fast deacceleration (5000 steps/s^2)
$stepper->setSpeedRamping(500, 5000);

$stepper->enable(); // Enable motor power
$stepper->setSteps(60000); // Drive 60000 steps forward

echo "Press key to exit\n";
fgetc(fopen('php://stdin', 'r'));
$stepper->disable();
$ipcon->disconnect();

?>
