use std::{error::Error, io};

use tinkerforge::{ipconnection::IpConnection, stepper_brick::*};

const HOST: &str = "127.0.0.1";
const PORT: u16 = 4223;
const UID: &str = "XXYYZZ"; // Change XXYYZZ to the UID of your Stepper Brick

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection
    let stepper_brick = StepperBrick::new(UID, &ipcon); // Create device object

    ipcon.connect(HOST, PORT).recv()??; // Connect to brickd
                                        // Don't use device before ipcon is connected

    stepper_brick.set_motor_current(800); // 800mA
    stepper_brick.set_step_mode(8); // 1/8 step mode
    stepper_brick.set_max_velocity(2000); // Velocity 2000 steps/s

    // Slow acceleration (500 steps/s^2),
    // Fast deacceleration (5000 steps/s^2)
    stepper_brick.set_speed_ramping(500, 5000);

    stepper_brick.enable(); // Enable motor power
    stepper_brick.set_steps(60000); // Drive 60000 steps forward

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    stepper_brick.disable();
    ipcon.disconnect();
    Ok(())
}
