using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "9yEBJVAgcoj"; // Change to your UID
	
	private static System.Random random = new System.Random();

	// Use position reached callback to program random movement 
	static void ReachedCB(object sender, int position)
	{
		BrickStepper stepper = (BrickStepper)sender;
		int steps;
		if(random.Next(0, 2) == 0)
		{
			steps = random.Next(1000, 5001); // steps (forward)
			System.Console.WriteLine("Driving forward: " + steps + " steps");
		}
		else
		{
			steps = random.Next(-5000, -999); // steps (backward)
			System.Console.WriteLine("Driving backward: " + steps + " steps");
		}

		ushort vel = (ushort)random.Next(200, 2001); // steps/s
		ushort acc = (ushort)random.Next(100, 1001); // steps/s^2
		ushort dec = (ushort)random.Next(100, 1001); // steps/s^2
		System.Console.WriteLine("Configuration (vel, acc, dec): (" +
		                         vel + ", " + acc + ", " + dec + ")");

		stepper.SetSpeedRamping(acc, dec);
		stepper.SetMaxVelocity(vel);
		stepper.SetSteps(steps);
	}

	static void Main() 
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickStepper stepper = new BrickStepper(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Register "position reached callback" to ReachedCB
		// ReachedCB will be called every time a position set with
		// SetSteps or SetTargetPosition is reached
		stepper.PositionReached += ReachedCB;

		stepper.Enable();
		stepper.SetSteps(1); // Drive one step forward to get things going

		System.Console.WriteLine("Press key to exit");
		System.Console.ReadKey();
	}
}
