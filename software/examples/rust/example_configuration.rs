use std::{error::Error, io, thread, time::Duration};
use tinkerforge::{ip_connection::IpConnection, stepper_brick::*};

const HOST: &str = "localhost";
const PORT: u16 = 4223;
const UID: &str = "XXYYZZ"; // Change XXYYZZ to the UID of your Stepper Brick.

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection.
    let stepper = StepperBrick::new(UID, &ipcon); // Create device object.

    ipcon.connect((HOST, PORT)).recv()??; // Connect to brickd.
                                          // Don't use device before ipcon is connected.

    stepper.set_motor_current(800); // 800 mA
    stepper.set_step_mode(8); // 1/8 step mode
    stepper.set_max_velocity(2000); // Velocity 2000 steps/s

    // Slow acceleration (500 steps/s^2),
    // Fast deacceleration (5000 steps/s^2)
    stepper.set_speed_ramping(500, 5000);

    stepper.enable(); // Enable motor power
    stepper.set_steps(60000); // Drive 60000 steps forward

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;

    // Stop motor before disabling motor power
    stepper.stop(); // Request motor stop
    stepper.set_speed_ramping(500, 5000); // Fast deacceleration (5000 steps/s^2) for stopping
    thread::sleep(Duration::from_millis(400)); // Wait for motor to actually stop: max velocity (2000 steps/s) / decceleration (5000 steps/s^2) = 0.4 s
    stepper.disable(); // Disable motor power

    ipcon.disconnect();
    Ok(())
}
