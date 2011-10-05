using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "9yEBJVAgcoj"; // Change to your UID

	static void Main() 
	{
		IPConnection ipcon = new IPConnection(HOST, PORT); // Create connection to brickd
		BrickStepper stepper = new BrickStepper(UID); // Create device object
		ipcon.AddDevice(stepper); // Add device to ip connection
		// Don't use device before it is added to a connection


		stepper.SetMotorCurrent(800); // 800mA
		stepper.SetStepMode(8); // 1/8 step mode
		stepper.SetDecay(12000); // Mixed decay mode

		stepper.SetMaxVelocity(2000); // Velocity 2000 steps/s
		// Slow acceleration (500 steps/s^2), 
		// Fast deacceleration (5000 steps/s^2)
		stepper.SetSpeedRamping(500, 5000);

		stepper.Enable();
		stepper.SetSteps(60000); // Drive 60000 steps forward

		System.Console.WriteLine("Press ctrl+c to exit");
		ipcon.JoinThread();
    }
}
