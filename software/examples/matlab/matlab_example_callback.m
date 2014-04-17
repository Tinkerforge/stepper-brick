function matlab_example_callback
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickStepper;

    HOST = 'localhost';
    PORT = 4223;
    UID = '63oL6P'; % Change to your UID
    
    ipcon = IPConnection(); % Create IP connection
    stepper = BrickStepper(UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register "position reached callback" to cb_reached
    % cb_reached will be called every time a position set with
    % set_steps or set_target_position is reached
    set(stepper, 'PositionReachedCallback', @(h, e) cb_reached(e));

    stepper.enable();
    stepper.setSteps(1); % Drive one step forward to get things going

    input('Press any key to exit...\n', 's');
    ipcon.disconnect();
end

% Use position reached callback to program random movement
function cb_reached(e)
    stepper = e.getSource();

    if randi([0, 1])
        steps = randi([1000, 5000]); % steps (forward);
        fprintf('Driving forward: %g steps\n', steps);
    else
        steps = randi([-5000, -1000]); % steps (backward);
        fprintf('Driving backward: %g steps\n', steps);
    end

    vel = randi([200, 2000]); % steps/s
    acc = randi([100, 1000]); % steps/s^2
    dec = randi([100, 1000]); % steps/s^2
    fprintf('Configuration (vel, acc, dec): %g, %g, %g\n', vel, acc, dec);

    stepper.setSpeedRamping(acc, dec);
    stepper.setMaxVelocity(vel);
    stepper.setSteps(steps);
end
