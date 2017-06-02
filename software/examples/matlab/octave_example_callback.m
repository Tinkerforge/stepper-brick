function octave_example_callback()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XXYYZZ"; % Change XXYYZZ to the UID of your Stepper Brick

    ipcon = javaObject("com.tinkerforge.IPConnection"); % Create IP connection
    stepper = javaObject("com.tinkerforge.BrickStepper", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register position reached callback to function cb_position_reached
    stepper.addPositionReachedCallback(@cb_position_reached);

    stepper.enable(); % Enable motor power
    stepper.setSteps(1); % Drive one step forward to get things going

    input("Press key to exit\n", "s");
    stepper.disable();
    ipcon.disconnect();
end

% Use position reached callback to program random movement
function cb_position_reached(e)
    stepper = e.getSource();

    if randi([0, 1])
        steps = randi([1000, 5000]); % steps (forward);
        fprintf("Driving forward: %g steps\n", steps);
    else
        steps = randi([-5000, -1000]); % steps (backward);
        fprintf("Driving backward: %g steps\n", steps);
    end

    vel = randi([200, 2000]); % steps/s
    acc = randi([100, 1000]); % steps/s^2
    dec = randi([100, 1000]); % steps/s^2
    fprintf("Configuration (vel, acc, dec): %g, %g, %g\n", vel, acc, dec);

    stepper.setSpeedRamping(acc, dec);
    stepper.setMaxVelocity(vel);
    stepper.setSteps(steps);
end
