// KeypadInterface.h

#ifndef _KEYPADINTERFACE_h
#define _KEYPADINTERFACE_h
#include <Keypad.h>
#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#endif

class ControllerKeyPad
{
public:
	// Constructor ...
	ControllerKeyPad() {}

	// Fields
private:
	static const byte KEYPAD_ROWS = 4;
	static const byte KEYPAD_COLS = 4;

	byte rowPins[KEYPAD_ROWS] = { 5, 4, 3, 2 };
	byte colPins[KEYPAD_COLS] = { A3, A2, A1, A0 };

	char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
	  {'1', '2', '3', 'A'},
	  {'4', '5', '6', 'B'},
	  {'7', '8', '9', 'C'},
	  {'*', '0', '#', 'D'}
	};

	Keypad _keypad = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);

	// Methods
public:
	char GetKey() {}
	String GetString(int aNumChars) {}
};
