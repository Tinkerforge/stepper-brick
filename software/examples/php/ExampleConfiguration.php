<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickStepper.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickStepper;

$host = 'localhost';
$port = 4223;
$uid = '9eggGYnDtnd'; // Change to your UID

$ipcon = new IPConnection($host, $port); // Create IP connection to brickd
$stepper = new BrickStepper($uid); // Create device object

$ipcon->addDevice($stepper); // Add device to IP connection
// Don't use device before it is added to a connection

$stepper->setMotorCurrent(800); // 800mA
$stepper->setStepMode(8); // 1/8 step mode
$stepper->setMaxVelocity(2000); // Velocity 2000 steps/s

// Slow acceleration (500 steps/s^2), 
// Fast deacceleration (5000 steps/s^2)
$stepper->setSpeedRamping(500, 5000);

$stepper->enable();
$stepper->setSteps(60000); // Drive 60000 steps forward

echo "Press key to exit\n";
fgetc(fopen('php://stdin', 'r'));
$ipcon->destroy();

?>
