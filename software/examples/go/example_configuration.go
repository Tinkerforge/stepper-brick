package main

import (
	"fmt"
	"github.com/Tinkerforge/go-api-bindings/ipconnection"
	"github.com/Tinkerforge/go-api-bindings/stepper_brick"
)

const ADDR string = "localhost:4223"
const UID string = "XXYYZZ" // Change XXYYZZ to the UID of your Stepper Brick.

func main() {
	ipcon := ipconnection.New()
	defer ipcon.Close()
	stepper, _ := stepper_brick.New(UID, &ipcon) // Create device object.

	ipcon.Connect(ADDR) // Connect to brickd.
	defer ipcon.Disconnect()
	// Don't use device before ipcon is connected.

	stepper.SetMotorCurrent(800) // 800 mA
	stepper.SetStepMode(8)       // 1/8 step mode
	stepper.SetMaxVelocity(2000) // Velocity 2000 steps/s

	// Slow acceleration (500 steps/s^2),
	// Fast deacceleration (5000 steps/s^2)
	stepper.SetSpeedRamping(500, 5000)

	stepper.Enable()        // Enable motor power
	stepper.SetSteps(60000) // Drive 60000 steps forward

	fmt.Print("Press enter to exit.")
	fmt.Scanln()

	// Stop motor before disabling motor power
	stepper.Stop() // Request motor stop
	stepper.SetSpeedRamping(500,
		5000) // Fast deacceleration (5000 steps/s^2) for stopping
	time.Sleep(400 * time.Millisecond) // Wait for motor to actually stop: max velocity (2000 steps/s) / decceleration (5000 steps/s^2) = 0.4 s
	stepper.Disable()                  // Disable motor power
}
