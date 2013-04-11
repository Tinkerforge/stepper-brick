import com.tinkerforge.BrickStepper;
import com.tinkerforge.IPConnection;

public class ExampleConfiguration {
	private static final String host = "localhost";
	private static final int port = 4223;
	private static final String UID = "9yEBJVAgcoj"; // Change to your UID

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions you
	//       might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickStepper stepper = new BrickStepper(UID, ipcon); // Create device object

		ipcon.connect(host, port); // Connect to brickd
		// Don't use device before ipcon is connected

		stepper.setMotorCurrent(800); // 800mA
		stepper.setStepMode((short)8); // 1/8 step mode
		stepper.setMaxVelocity(2000); // Velocity 2000 steps/s

		// Slow acceleration (500 steps/s^2), 
		// Fast deacceleration (5000 steps/s^2)
		stepper.setSpeedRamping(500, 5000);

		stepper.enable();
		stepper.setSteps(60000); // Drive 60000 steps forward

		System.console().readLine("Press key to exit\n");
		ipcon.disconnect();
	}
}
