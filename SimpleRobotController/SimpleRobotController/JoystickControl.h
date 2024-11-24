// JoystickControl.h

#ifndef _JOYSTICKCONTROL_h
#define _JOYSTICKCONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#endif

/// SETUP AlignedJoy Joystick

// PINs DEFINITION
// joystick 1
#define PIN_JOY1_X   8  //(up  down)
#define PIN_JOY1_Y   9  //(left  right)
// TIMERs DEFINITION
// joystick calibration
#define TIME_CAL_1 2000
#define TIME_CAL_2 10000

class JoystickInterface
{
public:
	JoystickInterface() {};	/*\brief Constructor */
	~JoystickInterface() {};	/*\brief Destructor */

	void Read_Joystick_Input() {};
};