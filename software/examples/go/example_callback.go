package main

import (
	"fmt"
	"github.com/Tinkerforge/go-api-bindings/ipconnection"
	"github.com/Tinkerforge/go-api-bindings/stepper_brick"
	"math/rand"
	"time"
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

	rng := rand.New(rand.NewSource(time.Now().UnixNano()))

	stepper.RegisterPositionReachedCallback(func(position int32) {
		steps := int32(0)
		if rng.Int31()%2 == 0 {
			steps = rng.Int31n(4001) + 1000
			fmt.Printf("Driving forward: %d steps\n", steps)
		} else {
			steps = -(rng.Int31n(4001) + 1000)
			fmt.Printf("Driving backward: %d steps\n", steps)
		}

		vel := uint16(rng.Int31n(1800) + 200)
		acc := uint16(rng.Int31n(900) + 100)
		dec := uint16(rng.Int31n(900) + 100)

		fmt.Printf("Configuration: (vel, acc, dec): (%d, %d, %d)\n", vel, acc, dec)
		stepper.SetSpeedRamping(acc, dec)
		stepper.SetMaxVelocity(vel)
		stepper.SetSteps(steps)
	})

	stepper.Enable()    // Enable motor power
	stepper.SetSteps(1) // Drive one step forward to get things going

	fmt.Print("Press enter to exit.")
	fmt.Scanln()

	// Stop motor before disabling motor power
	stepper.Stop() // Request motor stop
	stepper.SetSpeedRamping(500,
		5000) // Fast deacceleration (5000 steps/s^2) for stopping
	time.Sleep(400 * time.Millisecond) // Wait for motor to actually stop: max velocity (2000 steps/s) / decceleration (5000 steps/s^2) = 0.4 s
	stepper.Disable()                  // Disable motor power
}
