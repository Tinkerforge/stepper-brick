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
        stepper.enable(); // Enable motor power
        stepper.setSteps(1); // Drive one step forward to get things going
    }
);

// Register position reached callback
stepper.on(Tinkerforge.BrickStepper.CALLBACK_POSITION_REACHED,
    // Use position reached callback to program random movement
    function (position) {
        if(Math.floor(Math.random()*2)) {
            var steps = Math.floor((Math.random()*5000)+1000); // steps (forward);
            console.log('Driving forward: '+steps+' steps');
        }
        else {
            var steps = Math.floor((Math.random()*(-1000))+(-5000)); // steps (backward);
            console.log('Driving backward: '+steps+' steps');
        }

        var vel = Math.floor((Math.random()*2000)+200); // steps/s
        var acc = Math.floor((Math.random()*1000)+100); // steps/s^2
        var dec = Math.floor((Math.random()*1000)+100); // steps/s^2
        console.log('Configuration (vel, acc, dec): '+vel+', '+acc+', '+dec);

        stepper.setSpeedRamping(acc, dec);
        stepper.setMaxVelocity(vel);
        stepper.setSteps(steps);
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
