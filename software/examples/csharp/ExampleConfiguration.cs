using System;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XXYYZZ"; // Change XXYYZZ to the UID of your Stepper Brick

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickStepper stepper = new BrickStepper(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		stepper.SetMotorCurrent(800); // 800mA
		stepper.SetStepMode(8); // 1/8 step mode
		stepper.SetMaxVelocity(2000); // Velocity 2000 steps/s

		// Slow acceleration (500 steps/s^2),
		// Fast deacceleration (5000 steps/s^2)
		stepper.SetSpeedRamping(500, 5000);

		stepper.Enable(); // Enable motor power
		stepper.SetSteps(60000); // Drive 60000 steps forward

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();
		stepper.Disable();
		ipcon.Disconnect();
	}
}
