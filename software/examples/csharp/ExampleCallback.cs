using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "9yEBJVAgcoj"; // Change to your UID
	
	private static BrickStepper stepper;
	private static System.Random random = new System.Random();

	// Use position reached callback to program random movement 
	static void ReachedCB(int position)
	{
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
		IPConnection ipcon = new IPConnection(HOST, PORT); // Create connection to brickd
		stepper = new BrickStepper(UID); // Create device object
		ipcon.AddDevice(stepper); // Add device to IP connection
		// Don't use device before it is added to a connection

		// Register "position reached callback" to ReachedCB
		// ReachedCB will be called every time a position set with
		// SetSteps or SetTargetPosition is reached
		stepper.RegisterCallback(new BrickStepper.PositionReached(ReachedCB));

		stepper.Enable();
		stepper.SetSteps(1); // Drive one step forward to get things going

		System.Console.WriteLine("Press ctrl+c to exit");
		ipcon.JoinThread();
	}
}
