/*************************************************************
 * This file was automatically generated on 2011-09-13.      *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generator git on tinkerforge.com                   *
 *************************************************************/

package com.tinkerforge;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.concurrent.TimeUnit;


public class BrickStepper extends Device {
	private final static byte TYPE_SET_MAX_VELOCITY = (byte)1;
	private final static byte TYPE_GET_MAX_VELOCITY = (byte)2;
	private final static byte TYPE_GET_CURRENT_VELOCITY = (byte)3;
	private final static byte TYPE_SET_SPEED_RAMPING = (byte)4;
	private final static byte TYPE_GET_SPEED_RAMPING = (byte)5;
	private final static byte TYPE_FULL_BRAKE = (byte)6;
	private final static byte TYPE_SET_CURRENT_POSITION = (byte)7;
	private final static byte TYPE_GET_CURRENT_POSITION = (byte)8;
	private final static byte TYPE_SET_TARGET_POSITION = (byte)9;
	private final static byte TYPE_GET_TARGET_POSITION = (byte)10;
	private final static byte TYPE_SET_STEPS = (byte)11;
	private final static byte TYPE_GET_STEPS = (byte)12;
	private final static byte TYPE_GET_REMAINING_STEPS = (byte)13;
	private final static byte TYPE_SET_STEP_MODE = (byte)14;
	private final static byte TYPE_GET_STEP_MODE = (byte)15;
	private final static byte TYPE_DRIVE_FORWARD = (byte)16;
	private final static byte TYPE_DRIVE_BACKWARD = (byte)17;
	private final static byte TYPE_STOP = (byte)18;
	private final static byte TYPE_GET_STACK_INPUT_VOLTAGE = (byte)19;
	private final static byte TYPE_GET_EXTERNAL_INPUT_VOLTAGE = (byte)20;
	private final static byte TYPE_GET_CURRENT_CONSUMPTION = (byte)21;
	private final static byte TYPE_SET_MOTOR_CURRENT = (byte)22;
	private final static byte TYPE_GET_MOTOR_CURRENT = (byte)23;
	private final static byte TYPE_ENABLE = (byte)24;
	private final static byte TYPE_DISABLE = (byte)25;
	private final static byte TYPE_IS_ENABLED = (byte)26;
	private final static byte TYPE_SET_DECAY = (byte)27;
	private final static byte TYPE_GET_DECAY = (byte)28;
	private final static byte TYPE_SET_MINIMUM_VOLTAGE = (byte)29;
	private final static byte TYPE_GET_MINIMUM_VOLTAGE = (byte)30;
	private final static byte TYPE_UNDER_VOLTAGE = (byte)31;
	private final static byte TYPE_POSITION_REACHED = (byte)32;

	public class SpeedRamping {
		public int acceleration;
		public int deacceleration;

		public String toString() {
			 return "[" + "acceleration = " + acceleration + ", " + "deacceleration = " + deacceleration + "]";
		}
	}

	public interface UnderVoltageListener {
		public void underVoltage(int voltage);
	}

	public interface PositionReachedListener {
		public void positionReached(int position);
	}

	public BrickStepper(String uid) {
		super(uid);

		callbacks[TYPE_UNDER_VOLTAGE] = new CallbackListener() {
			public void callback(byte[] data) {
				ByteBuffer bb = ByteBuffer.wrap(data, 4, data.length - 4);
				bb.order(ByteOrder.LITTLE_ENDIAN);

				int voltage = IPConnection.unsignedShort(bb.getShort());

				((UnderVoltageListener)listenerObjects[TYPE_UNDER_VOLTAGE]).underVoltage(voltage);
			}
		};

		callbacks[TYPE_POSITION_REACHED] = new CallbackListener() {
			public void callback(byte[] data) {
				ByteBuffer bb = ByteBuffer.wrap(data, 4, data.length - 4);
				bb.order(ByteOrder.LITTLE_ENDIAN);

				int position = (bb.getInt());

				((PositionReachedListener)listenerObjects[TYPE_POSITION_REACHED]).positionReached(position);
			}
		};
	}

	public void setMaxVelocity(int velocity)  {
		ByteBuffer bb = ByteBuffer.allocate(6);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.put((byte)stackID);
		bb.put((byte)TYPE_SET_MAX_VELOCITY);
		bb.putShort((short)6);
		bb.putShort((short)velocity);

		ipcon.write(this, bb, TYPE_SET_MAX_VELOCITY, false);
	}

	public int getMaxVelocity() throws IPConnection.TimeoutException {
		ByteBuffer bb = ByteBuffer.allocate(4);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.put((byte)stackID);
		bb.put((byte)TYPE_GET_MAX_VELOCITY);
		bb.putShort((short)4);

		ipcon.write(this, bb, TYPE_GET_MAX_VELOCITY, true);

		byte[] answer = null;
		try {
			answer = answerQueue.poll(IPConnection.TIMEOUT_ANSWER, TimeUnit.MILLISECONDS);
			if(answer == null) {
				throw new IPConnection.TimeoutException("Did not receive answer for getMaxVelocity in time");
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		bb = ByteBuffer.wrap(answer, 4, answer.length - 4);
		bb.order(ByteOrder.LITTLE_ENDIAN);

		int velocity = IPConnection.unsignedShort(bb.getShort());

		semaphoreWrite.release();
		return velocity;
	}

	public int getCurrentVelocity() throws IPConnection.TimeoutException {
		ByteBuffer bb = ByteBuffer.allocate(4);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.put((byte)stackID);
		bb.put((byte)TYPE_GET_CURRENT_VELOCITY);
		bb.putShort((short)4);

		ipcon.write(this, bb, TYPE_GET_CURRENT_VELOCITY, true);

		byte[] answer = null;
		try {
			answer = answerQueue.poll(IPConnection.TIMEOUT_ANSWER, TimeUnit.MILLISECONDS);
			if(answer == null) {
				throw new IPConnection.TimeoutException("Did not receive answer for getCurrentVelocity in time");
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		bb = ByteBuffer.wrap(answer, 4, answer.length - 4);
		bb.order(ByteOrder.LITTLE_ENDIAN);

		int velocity = IPConnection.unsignedShort(bb.getShort());

		semaphoreWrite.release();
		return velocity;
	}

	public void setSpeedRamping(int acceleration, int deacceleration)  {
		ByteBuffer bb = ByteBuffer.allocate(8);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.put((byte)stackID);
		bb.put((byte)TYPE_SET_SPEED_RAMPING);
		bb.putShort((short)8);
		bb.putShort((short)acceleration);
		bb.putShort((short)deacceleration);

		ipcon.write(this, bb, TYPE_SET_SPEED_RAMPING, false);
	}

	public SpeedRamping getSpeedRamping() throws IPConnection.TimeoutException {
		ByteBuffer bb = ByteBuffer.allocate(4);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.put((byte)stackID);
		bb.put((byte)TYPE_GET_SPEED_RAMPING);
		bb.putShort((short)4);

		ipcon.write(this, bb, TYPE_GET_SPEED_RAMPING, true);

		byte[] answer = null;
		try {
			answer = answerQueue.poll(IPConnection.TIMEOUT_ANSWER, TimeUnit.MILLISECONDS);
			if(answer == null) {
				throw new IPConnection.TimeoutException("Did not receive answer for getSpeedRamping in time");
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		bb = ByteBuffer.wrap(answer, 4, answer.length - 4);
		bb.order(ByteOrder.LITTLE_ENDIAN);

		SpeedRamping obj = new SpeedRamping();
		obj.acceleration = IPConnection.unsignedShort(bb.getShort());
		obj.deacceleration = IPConnection.unsignedShort(bb.getShort());

		semaphoreWrite.release();
		return obj;
	}

	public void fullBrake()  {
		ByteBuffer bb = ByteBuffer.allocate(4);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.put((byte)stackID);
		bb.put((byte)TYPE_FULL_BRAKE);
		bb.putShort((short)4);

		ipcon.write(this, bb, TYPE_FULL_BRAKE, false);
	}

	public void setCurrentPosition(int position)  {
		ByteBuffer bb = ByteBuffer.allocate(8);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.put((byte)stackID);
		bb.put((byte)TYPE_SET_CURRENT_POSITION);
		bb.putShort((short)8);
		bb.putInt((int)position);

		ipcon.write(this, bb, TYPE_SET_CURRENT_POSITION, false);
	}

	public int getCurrentPosition() throws IPConnection.TimeoutException {
		ByteBuffer bb = ByteBuffer.allocate(4);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.put((byte)stackID);
		bb.put((byte)TYPE_GET_CURRENT_POSITION);
		bb.putShort((short)4);

		ipcon.write(this, bb, TYPE_GET_CURRENT_POSITION, true);

		byte[] answer = null;
		try {
			answer = answerQueue.poll(IPConnection.TIMEOUT_ANSWER, TimeUnit.MILLISECONDS);
			if(answer == null) {
				throw new IPConnection.TimeoutException("Did not receive answer for getCurrentPosition in time");
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		bb = ByteBuffer.wrap(answer, 4, answer.length - 4);
		bb.order(ByteOrder.LITTLE_ENDIAN);

		int position = (bb.getInt());

		semaphoreWrite.release();
		return position;
	}

	public void setTargetPosition(int position)  {
		ByteBuffer bb = ByteBuffer.allocate(8);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.put((byte)stackID);
		bb.put((byte)TYPE_SET_TARGET_POSITION);
		bb.putShort((short)8);
		bb.putInt((int)position);

		ipcon.write(this, bb, TYPE_SET_TARGET_POSITION, false);
	}

	public int getTargetPosition() throws IPConnection.TimeoutException {
		ByteBuffer bb = ByteBuffer.allocate(4);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.put((byte)stackID);
		bb.put((byte)TYPE_GET_TARGET_POSITION);
		bb.putShort((short)4);

		ipcon.write(this, bb, TYPE_GET_TARGET_POSITION, true);

		byte[] answer = null;
		try {
			answer = answerQueue.poll(IPConnection.TIMEOUT_ANSWER, TimeUnit.MILLISECONDS);
			if(answer == null) {
				throw new IPConnection.TimeoutException("Did not receive answer for getTargetPosition in time");
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		bb = ByteBuffer.wrap(answer, 4, answer.length - 4);
		bb.order(ByteOrder.LITTLE_ENDIAN);

		int position = (bb.getInt());

		semaphoreWrite.release();
		return position;
	}

	public void setSteps(int steps)  {
		ByteBuffer bb = ByteBuffer.allocate(8);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.put((byte)stackID);
		bb.put((byte)TYPE_SET_STEPS);
		bb.putShort((short)8);
		bb.putInt((int)steps);

		ipcon.write(this, bb, TYPE_SET_STEPS, false);
	}

	public int getSteps() throws IPConnection.TimeoutException {
		ByteBuffer bb = ByteBuffer.allocate(4);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.put((byte)stackID);
		bb.put((byte)TYPE_GET_STEPS);
		bb.putShort((short)4);

		ipcon.write(this, bb, TYPE_GET_STEPS, true);

		byte[] answer = null;
		try {
			answer = answerQueue.poll(IPConnection.TIMEOUT_ANSWER, TimeUnit.MILLISECONDS);
			if(answer == null) {
				throw new IPConnection.TimeoutException("Did not receive answer for getSteps in time");
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		bb = ByteBuffer.wrap(answer, 4, answer.length - 4);
		bb.order(ByteOrder.LITTLE_ENDIAN);

		int steps = (bb.getInt());

		semaphoreWrite.release();
		return steps;
	}

	public int getRemainingSteps() throws IPConnection.TimeoutException {
		ByteBuffer bb = ByteBuffer.allocate(4);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.put((byte)stackID);
		bb.put((byte)TYPE_GET_REMAINING_STEPS);
		bb.putShort((short)4);

		ipcon.write(this, bb, TYPE_GET_REMAINING_STEPS, true);

		byte[] answer = null;
		try {
			answer = answerQueue.poll(IPConnection.TIMEOUT_ANSWER, TimeUnit.MILLISECONDS);
			if(answer == null) {
				throw new IPConnection.TimeoutException("Did not receive answer for getRemainingSteps in time");
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		bb = ByteBuffer.wrap(answer, 4, answer.length - 4);
		bb.order(ByteOrder.LITTLE_ENDIAN);

		int steps = (bb.getInt());

		semaphoreWrite.release();
		return steps;
	}

	public void setStepMode(short mode)  {
		ByteBuffer bb = ByteBuffer.allocate(5);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.put((byte)stackID);
		bb.put((byte)TYPE_SET_STEP_MODE);
		bb.putShort((short)5);
		bb.put((byte)mode);

		ipcon.write(this, bb, TYPE_SET_STEP_MODE, false);
	}

	public short getStepMode() throws IPConnection.TimeoutException {
		ByteBuffer bb = ByteBuffer.allocate(4);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.put((byte)stackID);
		bb.put((byte)TYPE_GET_STEP_MODE);
		bb.putShort((short)4);

		ipcon.write(this, bb, TYPE_GET_STEP_MODE, true);

		byte[] answer = null;
		try {
			answer = answerQueue.poll(IPConnection.TIMEOUT_ANSWER, TimeUnit.MILLISECONDS);
			if(answer == null) {
				throw new IPConnection.TimeoutException("Did not receive answer for getStepMode in time");
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		bb = ByteBuffer.wrap(answer, 4, answer.length - 4);
		bb.order(ByteOrder.LITTLE_ENDIAN);

		short mode = IPConnection.unsignedByte(bb.get());

		semaphoreWrite.release();
		return mode;
	}

	public void driveForward()  {
		ByteBuffer bb = ByteBuffer.allocate(4);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.put((byte)stackID);
		bb.put((byte)TYPE_DRIVE_FORWARD);
		bb.putShort((short)4);

		ipcon.write(this, bb, TYPE_DRIVE_FORWARD, false);
	}

	public void driveBackward()  {
		ByteBuffer bb = ByteBuffer.allocate(4);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.put((byte)stackID);
		bb.put((byte)TYPE_DRIVE_BACKWARD);
		bb.putShort((short)4);

		ipcon.write(this, bb, TYPE_DRIVE_BACKWARD, false);
	}

	public void stop()  {
		ByteBuffer bb = ByteBuffer.allocate(4);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.put((byte)stackID);
		bb.put((byte)TYPE_STOP);
		bb.putShort((short)4);

		ipcon.write(this, bb, TYPE_STOP, false);
	}

	public int getStackInputVoltage() throws IPConnection.TimeoutException {
		ByteBuffer bb = ByteBuffer.allocate(4);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.put((byte)stackID);
		bb.put((byte)TYPE_GET_STACK_INPUT_VOLTAGE);
		bb.putShort((short)4);

		ipcon.write(this, bb, TYPE_GET_STACK_INPUT_VOLTAGE, true);

		byte[] answer = null;
		try {
			answer = answerQueue.poll(IPConnection.TIMEOUT_ANSWER, TimeUnit.MILLISECONDS);
			if(answer == null) {
				throw new IPConnection.TimeoutException("Did not receive answer for getStackInputVoltage in time");
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		bb = ByteBuffer.wrap(answer, 4, answer.length - 4);
		bb.order(ByteOrder.LITTLE_ENDIAN);

		int voltage = IPConnection.unsignedShort(bb.getShort());

		semaphoreWrite.release();
		return voltage;
	}

	public int getExternalInputVoltage() throws IPConnection.TimeoutException {
		ByteBuffer bb = ByteBuffer.allocate(4);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.put((byte)stackID);
		bb.put((byte)TYPE_GET_EXTERNAL_INPUT_VOLTAGE);
		bb.putShort((short)4);

		ipcon.write(this, bb, TYPE_GET_EXTERNAL_INPUT_VOLTAGE, true);

		byte[] answer = null;
		try {
			answer = answerQueue.poll(IPConnection.TIMEOUT_ANSWER, TimeUnit.MILLISECONDS);
			if(answer == null) {
				throw new IPConnection.TimeoutException("Did not receive answer for getExternalInputVoltage in time");
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		bb = ByteBuffer.wrap(answer, 4, answer.length - 4);
		bb.order(ByteOrder.LITTLE_ENDIAN);

		int voltage = IPConnection.unsignedShort(bb.getShort());

		semaphoreWrite.release();
		return voltage;
	}

	public int getCurrentConsumption() throws IPConnection.TimeoutException {
		ByteBuffer bb = ByteBuffer.allocate(4);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.put((byte)stackID);
		bb.put((byte)TYPE_GET_CURRENT_CONSUMPTION);
		bb.putShort((short)4);

		ipcon.write(this, bb, TYPE_GET_CURRENT_CONSUMPTION, true);

		byte[] answer = null;
		try {
			answer = answerQueue.poll(IPConnection.TIMEOUT_ANSWER, TimeUnit.MILLISECONDS);
			if(answer == null) {
				throw new IPConnection.TimeoutException("Did not receive answer for getCurrentConsumption in time");
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		bb = ByteBuffer.wrap(answer, 4, answer.length - 4);
		bb.order(ByteOrder.LITTLE_ENDIAN);

		int current = IPConnection.unsignedShort(bb.getShort());

		semaphoreWrite.release();
		return current;
	}

	public void setMotorCurrent(int current)  {
		ByteBuffer bb = ByteBuffer.allocate(6);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.put((byte)stackID);
		bb.put((byte)TYPE_SET_MOTOR_CURRENT);
		bb.putShort((short)6);
		bb.putShort((short)current);

		ipcon.write(this, bb, TYPE_SET_MOTOR_CURRENT, false);
	}

	public int getMotorCurrent() throws IPConnection.TimeoutException {
		ByteBuffer bb = ByteBuffer.allocate(4);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.put((byte)stackID);
		bb.put((byte)TYPE_GET_MOTOR_CURRENT);
		bb.putShort((short)4);

		ipcon.write(this, bb, TYPE_GET_MOTOR_CURRENT, true);

		byte[] answer = null;
		try {
			answer = answerQueue.poll(IPConnection.TIMEOUT_ANSWER, TimeUnit.MILLISECONDS);
			if(answer == null) {
				throw new IPConnection.TimeoutException("Did not receive answer for getMotorCurrent in time");
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		bb = ByteBuffer.wrap(answer, 4, answer.length - 4);
		bb.order(ByteOrder.LITTLE_ENDIAN);

		int current = IPConnection.unsignedShort(bb.getShort());

		semaphoreWrite.release();
		return current;
	}

	public void enable()  {
		ByteBuffer bb = ByteBuffer.allocate(4);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.put((byte)stackID);
		bb.put((byte)TYPE_ENABLE);
		bb.putShort((short)4);

		ipcon.write(this, bb, TYPE_ENABLE, false);
	}

	public void disable()  {
		ByteBuffer bb = ByteBuffer.allocate(4);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.put((byte)stackID);
		bb.put((byte)TYPE_DISABLE);
		bb.putShort((short)4);

		ipcon.write(this, bb, TYPE_DISABLE, false);
	}

	public boolean isEnabled() throws IPConnection.TimeoutException {
		ByteBuffer bb = ByteBuffer.allocate(4);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.put((byte)stackID);
		bb.put((byte)TYPE_IS_ENABLED);
		bb.putShort((short)4);

		ipcon.write(this, bb, TYPE_IS_ENABLED, true);

		byte[] answer = null;
		try {
			answer = answerQueue.poll(IPConnection.TIMEOUT_ANSWER, TimeUnit.MILLISECONDS);
			if(answer == null) {
				throw new IPConnection.TimeoutException("Did not receive answer for isEnabled in time");
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		bb = ByteBuffer.wrap(answer, 4, answer.length - 4);
		bb.order(ByteOrder.LITTLE_ENDIAN);

		boolean enabled = (bb.get()) != 0;

		semaphoreWrite.release();
		return enabled;
	}

	public void setDecay(int decay)  {
		ByteBuffer bb = ByteBuffer.allocate(6);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.put((byte)stackID);
		bb.put((byte)TYPE_SET_DECAY);
		bb.putShort((short)6);
		bb.putShort((short)decay);

		ipcon.write(this, bb, TYPE_SET_DECAY, false);
	}

	public int getDecay() throws IPConnection.TimeoutException {
		ByteBuffer bb = ByteBuffer.allocate(4);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.put((byte)stackID);
		bb.put((byte)TYPE_GET_DECAY);
		bb.putShort((short)4);

		ipcon.write(this, bb, TYPE_GET_DECAY, true);

		byte[] answer = null;
		try {
			answer = answerQueue.poll(IPConnection.TIMEOUT_ANSWER, TimeUnit.MILLISECONDS);
			if(answer == null) {
				throw new IPConnection.TimeoutException("Did not receive answer for getDecay in time");
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		bb = ByteBuffer.wrap(answer, 4, answer.length - 4);
		bb.order(ByteOrder.LITTLE_ENDIAN);

		int decay = IPConnection.unsignedShort(bb.getShort());

		semaphoreWrite.release();
		return decay;
	}

	public void setMinimumVoltage(int voltage)  {
		ByteBuffer bb = ByteBuffer.allocate(6);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.put((byte)stackID);
		bb.put((byte)TYPE_SET_MINIMUM_VOLTAGE);
		bb.putShort((short)6);
		bb.putShort((short)voltage);

		ipcon.write(this, bb, TYPE_SET_MINIMUM_VOLTAGE, false);
	}

	public int getMinimumVoltage() throws IPConnection.TimeoutException {
		ByteBuffer bb = ByteBuffer.allocate(4);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		bb.put((byte)stackID);
		bb.put((byte)TYPE_GET_MINIMUM_VOLTAGE);
		bb.putShort((short)4);

		ipcon.write(this, bb, TYPE_GET_MINIMUM_VOLTAGE, true);

		byte[] answer = null;
		try {
			answer = answerQueue.poll(IPConnection.TIMEOUT_ANSWER, TimeUnit.MILLISECONDS);
			if(answer == null) {
				throw new IPConnection.TimeoutException("Did not receive answer for getMinimumVoltage in time");
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		bb = ByteBuffer.wrap(answer, 4, answer.length - 4);
		bb.order(ByteOrder.LITTLE_ENDIAN);

		int voltage = IPConnection.unsignedShort(bb.getShort());

		semaphoreWrite.release();
		return voltage;
	}

	public void addListener(Object o) {
		if(o instanceof UnderVoltageListener) {
			listenerObjects[TYPE_UNDER_VOLTAGE] = o;
		} else if(o instanceof PositionReachedListener) {
			listenerObjects[TYPE_POSITION_REACHED] = o;
		}
	}
}