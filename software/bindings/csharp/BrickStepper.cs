/*************************************************************
 * This file was automatically generated on 2011-09-20.      *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

namespace Tinkerforge
{
	public class BrickStepper : Device 
	{
		private static byte TYPE_SET_MAX_VELOCITY = 1;
		private static byte TYPE_GET_MAX_VELOCITY = 2;
		private static byte TYPE_GET_CURRENT_VELOCITY = 3;
		private static byte TYPE_SET_SPEED_RAMPING = 4;
		private static byte TYPE_GET_SPEED_RAMPING = 5;
		private static byte TYPE_FULL_BRAKE = 6;
		private static byte TYPE_SET_CURRENT_POSITION = 7;
		private static byte TYPE_GET_CURRENT_POSITION = 8;
		private static byte TYPE_SET_TARGET_POSITION = 9;
		private static byte TYPE_GET_TARGET_POSITION = 10;
		private static byte TYPE_SET_STEPS = 11;
		private static byte TYPE_GET_STEPS = 12;
		private static byte TYPE_GET_REMAINING_STEPS = 13;
		private static byte TYPE_SET_STEP_MODE = 14;
		private static byte TYPE_GET_STEP_MODE = 15;
		private static byte TYPE_DRIVE_FORWARD = 16;
		private static byte TYPE_DRIVE_BACKWARD = 17;
		private static byte TYPE_STOP = 18;
		private static byte TYPE_GET_STACK_INPUT_VOLTAGE = 19;
		private static byte TYPE_GET_EXTERNAL_INPUT_VOLTAGE = 20;
		private static byte TYPE_GET_CURRENT_CONSUMPTION = 21;
		private static byte TYPE_SET_MOTOR_CURRENT = 22;
		private static byte TYPE_GET_MOTOR_CURRENT = 23;
		private static byte TYPE_ENABLE = 24;
		private static byte TYPE_DISABLE = 25;
		private static byte TYPE_IS_ENABLED = 26;
		private static byte TYPE_SET_DECAY = 27;
		private static byte TYPE_GET_DECAY = 28;
		private static byte TYPE_SET_MINIMUM_VOLTAGE = 29;
		private static byte TYPE_GET_MINIMUM_VOLTAGE = 30;
		private static byte TYPE_UNDER_VOLTAGE = 31;
		private static byte TYPE_POSITION_REACHED = 32;

		public delegate void UnderVoltage(ushort voltage);
		public delegate void PositionReached(int position);

		public BrickStepper(string uid) : base(uid) 
		{
			messageCallbacks[TYPE_UNDER_VOLTAGE] = new MessageCallback(CallbackUnderVoltage);
			messageCallbacks[TYPE_POSITION_REACHED] = new MessageCallback(CallbackPositionReached);
		}

		public void SetMaxVelocity(ushort velocity)
		{
			byte[] data = new byte[6];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_SET_MAX_VELOCITY, 1, data);
			LEConverter.To((ushort)6, 2, data);
			LEConverter.To(velocity, 4, data);

			ipcon.Write(this, data, TYPE_SET_MAX_VELOCITY, false);
		}

		public void GetMaxVelocity(out ushort velocity)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_MAX_VELOCITY, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_MAX_VELOCITY, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetMaxVelocity in time");
			}

			velocity = LEConverter.UShortFrom(4, answer);

			writeEvent.Set();
		}

		public void GetCurrentVelocity(out ushort velocity)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_CURRENT_VELOCITY, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_CURRENT_VELOCITY, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetCurrentVelocity in time");
			}

			velocity = LEConverter.UShortFrom(4, answer);

			writeEvent.Set();
		}

		public void SetSpeedRamping(ushort acceleration, ushort deacceleration)
		{
			byte[] data = new byte[8];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_SET_SPEED_RAMPING, 1, data);
			LEConverter.To((ushort)8, 2, data);
			LEConverter.To(acceleration, 4, data);
			LEConverter.To(deacceleration, 6, data);

			ipcon.Write(this, data, TYPE_SET_SPEED_RAMPING, false);
		}

		public void GetSpeedRamping(out ushort acceleration, out ushort deacceleration)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_SPEED_RAMPING, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_SPEED_RAMPING, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetSpeedRamping in time");
			}

			acceleration = LEConverter.UShortFrom(4, answer);
			deacceleration = LEConverter.UShortFrom(6, answer);

			writeEvent.Set();
		}

		public void FullBrake()
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_FULL_BRAKE, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_FULL_BRAKE, false);
		}

		public void SetCurrentPosition(int position)
		{
			byte[] data = new byte[8];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_SET_CURRENT_POSITION, 1, data);
			LEConverter.To((ushort)8, 2, data);
			LEConverter.To(position, 4, data);

			ipcon.Write(this, data, TYPE_SET_CURRENT_POSITION, false);
		}

		public void GetCurrentPosition(out int position)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_CURRENT_POSITION, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_CURRENT_POSITION, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetCurrentPosition in time");
			}

			position = LEConverter.IntFrom(4, answer);

			writeEvent.Set();
		}

		public void SetTargetPosition(int position)
		{
			byte[] data = new byte[8];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_SET_TARGET_POSITION, 1, data);
			LEConverter.To((ushort)8, 2, data);
			LEConverter.To(position, 4, data);

			ipcon.Write(this, data, TYPE_SET_TARGET_POSITION, false);
		}

		public void GetTargetPosition(out int position)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_TARGET_POSITION, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_TARGET_POSITION, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetTargetPosition in time");
			}

			position = LEConverter.IntFrom(4, answer);

			writeEvent.Set();
		}

		public void SetSteps(int steps)
		{
			byte[] data = new byte[8];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_SET_STEPS, 1, data);
			LEConverter.To((ushort)8, 2, data);
			LEConverter.To(steps, 4, data);

			ipcon.Write(this, data, TYPE_SET_STEPS, false);
		}

		public void GetSteps(out int steps)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_STEPS, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_STEPS, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetSteps in time");
			}

			steps = LEConverter.IntFrom(4, answer);

			writeEvent.Set();
		}

		public void GetRemainingSteps(out int steps)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_REMAINING_STEPS, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_REMAINING_STEPS, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetRemainingSteps in time");
			}

			steps = LEConverter.IntFrom(4, answer);

			writeEvent.Set();
		}

		public void SetStepMode(byte mode)
		{
			byte[] data = new byte[5];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_SET_STEP_MODE, 1, data);
			LEConverter.To((ushort)5, 2, data);
			LEConverter.To(mode, 4, data);

			ipcon.Write(this, data, TYPE_SET_STEP_MODE, false);
		}

		public void GetStepMode(out byte mode)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_STEP_MODE, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_STEP_MODE, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetStepMode in time");
			}

			mode = LEConverter.ByteFrom(4, answer);

			writeEvent.Set();
		}

		public void DriveForward()
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_DRIVE_FORWARD, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_DRIVE_FORWARD, false);
		}

		public void DriveBackward()
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_DRIVE_BACKWARD, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_DRIVE_BACKWARD, false);
		}

		public void Stop()
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_STOP, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_STOP, false);
		}

		public void GetStackInputVoltage(out ushort voltage)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_STACK_INPUT_VOLTAGE, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_STACK_INPUT_VOLTAGE, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetStackInputVoltage in time");
			}

			voltage = LEConverter.UShortFrom(4, answer);

			writeEvent.Set();
		}

		public void GetExternalInputVoltage(out ushort voltage)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_EXTERNAL_INPUT_VOLTAGE, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_EXTERNAL_INPUT_VOLTAGE, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetExternalInputVoltage in time");
			}

			voltage = LEConverter.UShortFrom(4, answer);

			writeEvent.Set();
		}

		public void GetCurrentConsumption(out ushort current)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_CURRENT_CONSUMPTION, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_CURRENT_CONSUMPTION, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetCurrentConsumption in time");
			}

			current = LEConverter.UShortFrom(4, answer);

			writeEvent.Set();
		}

		public void SetMotorCurrent(ushort current)
		{
			byte[] data = new byte[6];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_SET_MOTOR_CURRENT, 1, data);
			LEConverter.To((ushort)6, 2, data);
			LEConverter.To(current, 4, data);

			ipcon.Write(this, data, TYPE_SET_MOTOR_CURRENT, false);
		}

		public void GetMotorCurrent(out ushort current)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_MOTOR_CURRENT, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_MOTOR_CURRENT, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetMotorCurrent in time");
			}

			current = LEConverter.UShortFrom(4, answer);

			writeEvent.Set();
		}

		public void Enable()
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_ENABLE, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_ENABLE, false);
		}

		public void Disable()
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_DISABLE, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_DISABLE, false);
		}

		public void IsEnabled(out bool enabled)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_IS_ENABLED, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_IS_ENABLED, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for IsEnabled in time");
			}

			enabled = LEConverter.BoolFrom(4, answer);

			writeEvent.Set();
		}

		public void SetDecay(ushort decay)
		{
			byte[] data = new byte[6];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_SET_DECAY, 1, data);
			LEConverter.To((ushort)6, 2, data);
			LEConverter.To(decay, 4, data);

			ipcon.Write(this, data, TYPE_SET_DECAY, false);
		}

		public void GetDecay(out ushort decay)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_DECAY, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_DECAY, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetDecay in time");
			}

			decay = LEConverter.UShortFrom(4, answer);

			writeEvent.Set();
		}

		public void SetMinimumVoltage(ushort voltage)
		{
			byte[] data = new byte[6];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_SET_MINIMUM_VOLTAGE, 1, data);
			LEConverter.To((ushort)6, 2, data);
			LEConverter.To(voltage, 4, data);

			ipcon.Write(this, data, TYPE_SET_MINIMUM_VOLTAGE, false);
		}

		public void GetMinimumVoltage(out ushort voltage)
		{
			byte[] data = new byte[4];
			LEConverter.To(stackID, 0, data);
			LEConverter.To(TYPE_GET_MINIMUM_VOLTAGE, 1, data);
			LEConverter.To((ushort)4, 2, data);

			ipcon.Write(this, data, TYPE_GET_MINIMUM_VOLTAGE, true);

			byte[] answer;
			if(!answerQueue.TryDequeue(out answer, IPConnection.TIMEOUT_ANSWER))
			{
				throw new TimeoutException("Did not receive answer for GetMinimumVoltage in time");
			}

			voltage = LEConverter.UShortFrom(4, answer);

			writeEvent.Set();
		}

		public int CallbackUnderVoltage(byte[] data)
		{
			ushort voltage = LEConverter.UShortFrom(4, data);

			((UnderVoltage)callbacks[TYPE_UNDER_VOLTAGE])(voltage);
			return 6;
		}

		public int CallbackPositionReached(byte[] data)
		{
			int position = LEConverter.IntFrom(4, data);

			((PositionReached)callbacks[TYPE_POSITION_REACHED])(position);
			return 8;
		}

		public void RegisterCallback(System.Delegate d)
		{
			if(d.GetType() == typeof(UnderVoltage))
			{
				callbacks[TYPE_UNDER_VOLTAGE] = d;
			}
			else if(d.GetType() == typeof(PositionReached))
			{
				callbacks[TYPE_POSITION_REACHED] = d;
			}
		}
	}
}
