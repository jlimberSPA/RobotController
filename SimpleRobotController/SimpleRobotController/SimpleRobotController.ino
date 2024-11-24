// Visual Micro is in vMicro>General>Tutorial Mode
//
/*
	Name:       SimpleRobotController.ino
	Created:	1/1/2024 2:13:53 PM
	Author:     JOE-HP-LAPTOP\jmlma
*/

// Define User Types below here or use a .h file
//

// Define Function Prototypes that use User Types below here or use a .h file
//

// Define Functions below here or use other .ino or cpp files
//

// The setup() function runs once each time the micro-controller starts
#include "XBeeInterface.h"
#include <Key.h>

#include "KeypadInterface.h"
#include "ScreenInterface.h"
#include "JoystickControl.h"
#include "MotorControl.h"
void setup()
{
	ControllerKeyPad MyKeypad = ControllerKeyPad();
}

// Add the main program code into the continuous loop() function
void loop()
{
}