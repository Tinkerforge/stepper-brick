var IPConnection = require('Tinkerforge/IPConnection');
var BrickStepper = require('Tinkerforge/BrickStepper');

var HOST = 'localhost';
var PORT = 4223;
var UID = '63oL6P';// Change to your UID

var ipcon = new IPConnection();// Create IP connection
var stepper = new BrickStepper(UID, ipcon);// Create device object

ipcon.connect(HOST, PORT,
    function(error) {
        if(error === IPConnection.ERROR_ALREADY_CONNECTED) {
            console.log('Error: Already connected');        
        }
    }
);// Connect to brickd

// Don't use device before ipcon is connected
ipcon.on(IPConnection.CALLBACK_CONNECTED,
    function(connectReason) {
        stepper.setMotorCurrent(800);// 800mA
        stepper.setStepMode(8);// 1/8 step mode
        stepper.setMaxVelocity(2000);// Velocity 2000 steps/s
        // Slow acceleration (500 steps/s^2), 
        // Fast deacceleration (5000 steps/s^2)
        stepper.setSpeedRamping(500, 5000); 
        stepper.enable();
        stepper.setSteps(60000);// Drive 60000 steps forward     
    }
);

console.log("Press any key to exit ...");
process.stdin.on('data', function(data) {
	    ipcon.disconnect(
            function(error) {
                if(error === IPConnection.ERROR_NOT_CONNECTED) {
                    console.log('Error: Not connected');        
                }
            }
        );
process.exit(0);
});

