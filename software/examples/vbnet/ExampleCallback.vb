Imports System
Imports Tinkerforge

Module ExampleCallback
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XXYYZZ" ' Change XXYYZZ to the UID of your Stepper Brick

    Dim rand As Random = New Random()

    ' Use position reached callback to program random movement
    Sub PositionReachedCB(ByVal sender As BrickStepper, ByVal position As Integer)
        Dim steps As Integer

        If rand.Next(0, 2) = 0 Then
            steps = rand.Next(1000, 5001) ' steps (forward)
            Console.WriteLine("Driving forward: " + steps.ToString() + " steps")
        Else
            steps = rand.Next(-5000, -999) ' steps (backward)
            Console.WriteLine("Driving backward: " + steps.ToString() + " steps")
        End If

        Dim vel As Integer = rand.Next(200, 2001) ' steps/s
        Dim acc As Integer = rand.Next(100, 1001) ' steps/s^2
        Dim dec As Integer = rand.Next(100, 1001) ' steps/s^2

        Console.WriteLine("Configuration (vel, acc, dec): (" + vel.ToString() + ", " + _
                          acc.ToString() + ", " + dec.ToString() + ")")

        sender.SetSpeedRamping(acc, dec)
        sender.SetMaxVelocity(vel)
        sender.SetSteps(steps)
    End Sub

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim stepper As New BrickStepper(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Register position reached callback to subroutine PositionReachedCB
        AddHandler stepper.PositionReachedCallback, AddressOf PositionReachedCB

        stepper.Enable() ' Enable motor power
        stepper.SetSteps(1) ' Drive one step forward to get things going

        Console.WriteLine("Press key to exit")
        Console.ReadLine()

        ' Stop motor before disabling motor power
        stepper.Stop() ' Request motor stop
        stepper.SetSpeedRamping(500, _
                                5000) ' Fast deacceleration (5000 steps/s^2) for stopping
        Thread.Sleep(400) ' Wait for motor to actually stop: max velocity (2000 steps/s) / decceleration (5000 steps/s^2) = 0.4 s
        stepper.Disable() ' Disable motor power

        ipcon.Disconnect()
    End Sub
End Module
