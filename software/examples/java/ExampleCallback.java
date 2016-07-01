import java.util.Random;

import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickStepper;
import com.tinkerforge.TinkerforgeException;

public class ExampleCallback {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;

	// Change XXYYZZ to the UID of your Stepper Brick
	private static final String UID = "XXYYZZ";

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions
	//       you might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		// Note: Declare stepper final, so the listener can access it
		final BrickStepper stepper = new BrickStepper(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Use position reached callback to program random movement
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

		stepper.enable(); // Enable motor power
		stepper.setSteps(1); // Drive one step forward to get things going

		System.out.println("Press key to exit"); System.in.read();
		stepper.disable();
		ipcon.disconnect();
	}
}
