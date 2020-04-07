Imports System
Imports System.Threading
Imports Tinkerforge

Module ExampleConfiguration
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XXYYZZ" ' Change XXYYZZ to the UID of your Stepper Brick

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim stepper As New BrickStepper(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        stepper.SetMotorCurrent(800) ' 800 mA
        stepper.SetStepMode(8) ' 1/8 step mode
        stepper.SetMaxVelocity(2000) ' Velocity 2000 steps/s

        ' Slow acceleration (500 steps/s^2),
        ' Fast deacceleration (5000 steps/s^2)
        stepper.SetSpeedRamping(500, 5000)

        stepper.Enable() ' Enable motor power
        stepper.SetSteps(60000) ' Drive 60000 steps forward

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
