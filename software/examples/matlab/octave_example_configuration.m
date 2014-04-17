function octave_example_configuration()
    more off;
    
    HOST = "localhost";
    PORT = 4223;
    UID = "63oL6P"; % Change to your UID

    ipcon = java_new("com.tinkerforge.IPConnection"); % Create IP connection
    stepper = java_new("com.tinkerforge.BrickStepper", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    stepper.setMotorCurrent(800); % 800mA
    stepper.setStepMode(8); % 1/8 step mode
    stepper.setMaxVelocity(2000); % Velocity 2000 steps/s

    % Slow acceleration (500 steps/s^2), 
    % Fast deacceleration (5000 steps/s^2)
    stepper.setSpeedRamping(500, 5000);

    stepper.enable();
    stepper.setSteps(60000); % Drive 60000 steps forward

    input("Press any key to exit...\n", "s");
    ipcon.disconnect();
end
