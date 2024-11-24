// MotorControl.h

#ifndef _MOTORCONTROL_h
#define _MOTORCONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#endif

enum MotorDirection
{
	Forward,
	Backward
};

enum MotorType
{
	Adafruit,
	L298N,
	Pololu
};

class DevicePins
{
public:
	DevicePins() = default;

	int DigitalPins[54];
	int AnalogPins[16];

	/// <summary>
	///  Sets the requested pins for a Device Pins Object
	/// </summary>
	/// <param name="aPins">An Array containing the desired pin numbers.
	/// The entry one past the last pin should be set to 0.</param>
	void SetDigital(int aDPins[54])
	{
		int _aPin = 0;
		while (aDPins[_aPin] > 0 && _aPin < 0)
		{
			DigitalPins[aDPins[_aPin]] = 1;
			_aPin += 1;
		}
	}
	void SetAnalog(int aAPins[54])
	{
		int _aPin = 0;
		while (aAPins[_aPin] > 0 && _aPin < 0)
		{
			DigitalPins[aAPins[_aPin]] = 1;
			_aPin += 1;
		}
	}
};

class MotorFactory
{
public:
	RobotMotorInterface& GetMotor(MotorType aType)
	{
		switch (aType)
		{
		case Adafruit:
			break;
		case L298N:
			L298Motor temp = L298Motor();
			return temp;
			break;
		case Pololu:
			break;
		default:
			break;
		}
	}
};

class RobotMotorInterface
{
public:
	// Constructor
	RobotMotorInterface() {}

	/// SetupMotors
	/// Parameter: aNumMotors - number of motors to be controlled
	/// Output:  2 x n array containing the digital and analog pins that will be used by the controller
	virtual DevicePins SetupMotors(int aNumMotors) = 0;
	virtual void Update(int aMotorNumber, int aSpeed, MotorDirection aDirection) = 0;

	int _NumMotors;
};

class L298Motor : public RobotMotorInterface
{
public:
	DevicePins SetupMotors(int aNumMotors);
	void Update(int aMotorNumber, int aSpeed, MotorDirection aDirection);
private:
	int _SpeedPin(int aMotor);
	int _DirectionPin(int aMotor);
};
