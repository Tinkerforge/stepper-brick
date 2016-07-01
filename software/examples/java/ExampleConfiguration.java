import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickStepper;

public class ExampleConfiguration {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;

	// Change XXYYZZ to the UID of your Stepper Brick
	private static final String UID = "XXYYZZ";

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions
	//       you might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickStepper stepper = new BrickStepper(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		stepper.setMotorCurrent(800); // 800mA
		stepper.setStepMode((short)8); // 1/8 step mode
		stepper.setMaxVelocity(2000); // Velocity 2000 steps/s

		// Slow acceleration (500 steps/s^2),
		// Fast deacceleration (5000 steps/s^2)
		stepper.setSpeedRamping(500, 5000);

		stepper.enable(); // Enable motor power
		stepper.setSteps(60000); // Drive 60000 steps forward

		System.out.println("Press key to exit"); System.in.read();
		stepper.disable();
		ipcon.disconnect();
	}
}
