import com.tinkerforge.BrickStepper;
import com.tinkerforge.IPConnection;

import java.util.Random;

public class ExampleCallback {
	private static final String host = "localhost";
	private static final int port = 4223;
	private static final String UID = "9yEBJVAgcoj"; // Change to your UID

	// Declare stepper static, so the listener can use it. In a real program you probably
	// want to make a real listener class (not the anonym inner class) and pass the stepper
	// reference to it. But we want to keep the examples as short es possible.
	static BrickStepper stepper;

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions you
	//       might normally want to catch are described in the commnents below
	public static void main(String args[]) throws Exception {
		// Create connection to brickd
		IPConnection ipcon = new IPConnection(host, port); // Can throw IOException

		stepper = new BrickStepper(UID); // Create device object

		// Add device to IP connection
		ipcon.addDevice(stepper); // Can throw IPConnection.TimeoutException
		// Don't use device before it is added to a connection

		// Add and implement position reached listener 
		// (called if position set by setSteps or setTargetPosition is reached)
		stepper.addListener(new BrickStepper.PositionReachedListener() {
			Random random = new Random();

			public void positionReached(int position) {
				int steps = 0;
				if(random.nextInt(2) == 1) {
					steps = random.nextInt(4001) + 1000; // steps (forward)
				} else {
					steps = random.nextInt(5001) - 6000; // steps (backward)
				}

				int vel = random.nextInt(1801) + 200; // steps/s
				int acc = random.nextInt(901) + 100; // steps/s^2
				int dec = random.nextInt(901) + 100; // steps/s^2
				System.out.println("Configuration (vel, acc, dec): (" + 
				                   vel + ", " + acc + ",  " + dec + ")");

				stepper.setSpeedRamping(acc, dec);
				stepper.setMaxVelocity(vel);
				stepper.setSteps(steps);
			}
		});

		stepper.enable();
		stepper.setSteps(1); // Drive one step forward to get things going

		System.console().readLine("Press key to exit\n");
		ipcon.destroy();
	}
}
