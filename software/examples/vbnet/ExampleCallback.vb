Imports Tinkerforge

Module ExampleCallback
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "6qAdzq" ' Change to your UID

    Dim rand As System.Random = New System.Random()

    ' Use position reached callback to program random movement
    Sub ReachedCB(ByVal sender As BrickStepper, ByVal position As Integer)
        Dim steps As Integer
        If rand.Next(0, 2) = 0 Then
            steps = rand.Next(1000, 5001) ' steps (forward)
            System.Console.WriteLine("Driving forward: " + steps.ToString() + " steps")
        Else
            steps = rand.Next(-5000, -999) ' steps (backward)
            System.Console.WriteLine("Driving backward: " + steps.ToString() + " steps")
        End If

        Dim vel As Integer = rand.Next(200, 2001) ' steps/s
        Dim acc As Integer = rand.Next(100, 1001) ' steps/s^2
        Dim dec As Integer = rand.Next(100, 1001) ' steps/s^2
        System.Console.WriteLine("Configuration (vel, acc, dec): (" + _
                                 vel.ToString() + ", " + acc.ToString() + ", " + _
                                 dec.ToString() + ")")

        sender.SetSpeedRamping(acc, dec)
        sender.SetMaxVelocity(vel)
        sender.SetSteps(steps)
    End Sub

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim stepper As New BrickStepper(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Register "position reached callback" to ReachedCB
        ' ReachedCB will be called every time a position set with
        ' SetSteps or SetTargetPosition is reached
        AddHandler stepper.PositionReached, AddressOf ReachedCB

        stepper.Enable()
        stepper.SetSteps(1) ' Drive one step forward to get things going

        System.Console.WriteLine("Press key to exit")
        System.Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module
