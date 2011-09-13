import com.tinkerforge.BrickStepper;
import com.tinkerforge.IPConnection;

public class ExampleConfiguration {
	private static final String host = new String("localhost");
	private static final int port = 4223;
	private static final String UID = new String("9yEBJVAgcoj"); // Change to your UID
	
	// Note: To make the example code cleaner we do not handle exceptions. Exceptions you
	//       might normally want to catch are described in the commnents below
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(host, port); // Create connection to brickd (Can throw IOException)

		BrickStepper stepper = new BrickStepper(UID); // Create device object
		ipcon.addDevice(stepper); // Add device to ip connection (Can throw IPConnection.TimeoutException)
		// Don't use device before it is added to a connection
		

		stepper.setMotorCurrent(800); // 800mA
		stepper.setStepMode((short)8); // 1/8 step mode
		stepper.setDecay(12000); // Mixed decay mode
		stepper.setMaxVelocity(2000); // Velocity 2000 steps/s

		// Slow acceleration (500 steps/s^2), 
		// Fast deacceleration (5000 steps/s^2)
		stepper.setSpeedRamping(500, 5000);

		stepper.enable();
		stepper.setSteps(60000); // Drive 60000 steps forward

		System.out.println("Press ctrl+c to exit");
		ipcon.joinThread();
	}
}
