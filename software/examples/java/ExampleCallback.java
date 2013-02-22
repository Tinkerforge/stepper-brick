import com.tinkerforge.BrickStepper;
import com.tinkerforge.IPConnection;
import com.tinkerforge.TinkerforgeException;

import java.util.Random;

public class ExampleCallback {
	private static final String host = "localhost";
	private static final int port = 4223;
	private static final String UID = "9yEBJVAgcoj"; // Change to your UID

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions you
	//       might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		// Note: Declare stepper final, so the listener can access it
		final BrickStepper stepper = new BrickStepper(UID, ipcon); // Create device object

		ipcon.connect(host, port); // Connect to brickd
		// Don't use device before ipcon is connected

		// Add and implement position reached listener 
		// (called if position set by setSteps or setTargetPosition is reached)
		stepper.addPositionReachedListener(new BrickStepper.PositionReachedListener() {
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

				try {
					stepper.setSpeedRamping(acc, dec);
					stepper.setMaxVelocity(vel);
					stepper.setSteps(steps);
				} catch(TinkerforgeException e) {
				}
			}
		});

		stepper.enable();
		stepper.setSteps(1); // Drive one step forward to get things going

		System.console().readLine("Press key to exit\n");
		ipcon.disconnect();
	}
}
