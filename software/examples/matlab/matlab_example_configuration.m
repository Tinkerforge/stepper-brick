function matlab_example_configuration()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickStepper;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XXYYZZ'; % Change XXYYZZ to the UID of your Stepper Brick

    ipcon = IPConnection(); % Create IP connection
    stepper = handle(BrickStepper(UID, ipcon), 'CallbackProperties'); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    stepper.setMotorCurrent(800); % 800mA
    stepper.setStepMode(8); % 1/8 step mode
    stepper.setMaxVelocity(2000); % Velocity 2000 steps/s

    % Slow acceleration (500 steps/s^2),
    % Fast deacceleration (5000 steps/s^2)
    stepper.setSpeedRamping(500, 5000);

    stepper.enable(); % Enable motor power
    stepper.setSteps(60000); % Drive 60000 steps forward

    input('Press key to exit\n', 's');
    stepper.disable();
    ipcon.disconnect();
end
