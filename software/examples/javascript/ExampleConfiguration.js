var Tinkerforge = require('tinkerforge');

var HOST = 'localhost';
var PORT = 4223;
var UID = 'XXYYZZ'; // Change XXYYZZ to the UID of your Stepper Brick

var ipcon = new Tinkerforge.IPConnection(); // Create IP connection
var stepper = new Tinkerforge.BrickStepper(UID, ipcon); // Create device object

ipcon.connect(HOST, PORT,
    function (error) {
        console.log('Error: ' + error);
    }
); // Connect to brickd
// Don't use device before ipcon is connected

ipcon.on(Tinkerforge.IPConnection.CALLBACK_CONNECTED,
    function (connectReason) {
        stepper.setMotorCurrent(800); // 800mA
        stepper.setStepMode(8); // 1/8 step mode
        stepper.setMaxVelocity(2000); // Velocity 2000 steps/s

        // Slow acceleration (500 steps/s^2),
        // Fast deacceleration (5000 steps/s^2)
        stepper.setSpeedRamping(500, 5000);

        stepper.enable(); // Enable motor power
        stepper.setSteps(60000); // Drive 60000 steps forward
    }
);

console.log('Press key to exit');
process.stdin.on('data',
    function (data) {
        stepper.disable();
        ipcon.disconnect();
        process.exit(0);
    }
);
