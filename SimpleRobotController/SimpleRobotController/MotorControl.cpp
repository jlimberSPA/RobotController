//
//
//

#include "MotorControl.h"

DevicePins L298Motor::SetupMotors(int aNumMotors)
{
	DevicePins _Pins = DevicePins();
	_NumMotors = aNumMotors;

	for (int _Motor = 0; _Motor < aNumMotors; _Motor += 1)
	{
		int sp = _SpeedPin(_Motor);
		int dp = _DirectionPin(_Motor);

		// Set Pin Mode
		pinMode(sp, OUTPUT);
		pinMode(dp, OUTPUT);

		// prep pin numbers for passing to calling function
		_Pins.DigitalPins[sp] = 1;
		_Pins.DigitalPins[dp] = 1; //
	}
	return _Pins;
}

/// <summary>
/// Set the motor speed and direction
/// </summary>
/// <param name="aMotorNumber">index number</param>
/// <param name="aSpeed">0 to 100</param>
/// <param name="aDirection">MotorDirection enum</param>
void L298Motor::Update(int aMotorNumber, int aSpeed, MotorDirection aDirection)
{
	switch (aDirection)
	{
	case Forward:
		digitalWrite(_DirectionPin(aMotorNumber), HIGH);
		break;
	case Backward:
		digitalWrite(_DirectionPin(aMotorNumber), LOW);
		break;
	default:
		break;
	}

	aSpeed = constrain(aSpeed, 0, 100);
	aSpeed = map(aSpeed, 0, 100, 0, 255);

	analogWrite(_SpeedPin(aMotorNumber), aSpeed);
}

int L298Motor::_SpeedPin(int aMotor)
{
	return 2 + aMotor;
}

int L298Motor::_DirectionPin(int aMotor)
{
	return 22 + aMotor;
}