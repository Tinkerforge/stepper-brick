package main

import (
	"fmt"
	"math/rand"
	"time"
	"tinkerforge/ipconnection"
    "tinkerforge/stepper_brick"
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
		if rng.Int31() % 2 == 0 {
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

	stepper.Disable()
	ipcon.Disconnect()
}
