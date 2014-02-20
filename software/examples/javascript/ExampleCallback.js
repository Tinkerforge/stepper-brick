var Tinkerforge = require('tinkerforge');

var HOST = 'localhost';
var PORT = 4223;
var UID = '63oL6P';// Change to your UID

var ipcon = new Tinkerforge.IPConnection();// Create IP connection
var stepper = new Tinkerforge.BrickStepper(UID, ipcon);// Create device object

ipcon.connect(HOST, PORT,
    function(error) {
        console.log('Error: '+error);        
    }
);// Connect to brickd

// Don't use device before ipcon is connected
ipcon.on(Tinkerforge.IPConnection.CALLBACK_CONNECTED,
    function(connectReason) {
        stepper.enable();
        stepper.setSteps(1);// Drive one step forward to get things going
    }
);

// Register "position reached callback",
// the callback will be called every time a position set with
// setSteps or setTargetPosition is reached.
stepper.on(Tinkerforge.BrickStepper.CALLBACK_POSITION_REACHED,
    // Use position reached callback to program random movement
    function(position) {
        if(Math.floor(Math.random()*2)) {
            var steps = Math.floor((Math.random()*5000)+1000);// steps (forward);
            console.log('Driving forward: '+steps+' steps');
        }
        else {
            var steps = Math.floor((Math.random()*(-1000))+(-5000));// steps (backward);
            console.log('Driving backward: '+steps+' steps');
        }
        var vel = Math.floor((Math.random()*2000)+200);// steps/s
        var acc = Math.floor((Math.random()*1000)+100);// steps/s^2
        var dec = Math.floor((Math.random()*1000)+100);// steps/s^2
        console.log('Configuration (vel, acc, dec): '+vel+', '+acc+', '+dec);

        stepper.setSpeedRamping(acc, dec);
        stepper.setMaxVelocity(vel);
        stepper.setSteps(steps);
    }
);

console.log("Press any key to exit ...");
process.stdin.on('data',
    function(data) {
        ipcon.disconnect();
        process.exit(0);
    }
);

