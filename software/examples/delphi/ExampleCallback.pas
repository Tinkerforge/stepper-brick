program ExampleCallback;

{$ifdef MSWINDOWS}{$apptype CONSOLE}{$endif}
{$ifdef FPC}{$mode OBJFPC}{$H+}{$endif}

uses
  SysUtils, IPConnection, BrickStepper;

type
  TExample = class
  private
    ipcon: TIPConnection;
    stepper: TBrickStepper;
  public
    procedure ReachedCB(const position: longint);
    procedure Execute;
  end;

const
  HOST = 'localhost';
  PORT = 4223;
  UID = '9eggGYnDtnd';

var
  e: TExample;

{ Use position reached callback to program random movement }
procedure TExample.ReachedCB(const position: longint);
var steps: longint; vel: smallint; acc, dec: word;
begin
  if (Random(2) = 0) then begin
    steps := Random(4000) + 1000; { steps (forward) }
    WriteLn(Format('Driving forward: %d steps', [steps]));
  end
  else begin
    steps := -(Random(4000) + 1000); { steps (backward) }
    WriteLn(Format('Driving backward: %d steps', [steps]));
  end;

  vel := Random(1800) + 200; { steps/s }
  acc := Random(900) + 100; { steps/s^2 }
  dec := Random(900) + 100; { steps/s^2 }
  WriteLn(Format('Configuration (vel, acc, dec): %d, %d %d', [vel, acc, dec]));

  stepper.SetSpeedRamping(acc, dec);
  stepper.SetMaxVelocity(vel);
  stepper.SetSteps(steps);
end;

procedure TExample.Execute;
begin
  { Create IP connection to brickd }
  ipcon := TIPConnection.Create(HOST, PORT);

  { Create device object }
  stepper := TBrickStepper.Create(UID);

  { Add device to IP connection }
  ipcon.AddDevice(stepper);
  { Don't use device before it is added to a connection }

  { Register "position reached callback" to procedure ReachedCB.
    ReachedCB will be called every time a position set with
    SetSteps or SetTargetPosition is reached }
  stepper.OnPositionReached := {$ifdef FPC}@{$endif}ReachedCB;

  stepper.Enable;

  { Drive one step forward to get things going }
  stepper.SetSteps(1);

  WriteLn('Press key to exit');
  ReadLn;
  ipcon.Destroy;
end;

begin
  e := TExample.Create;
  e.Execute;
  e.Destroy;
end.
