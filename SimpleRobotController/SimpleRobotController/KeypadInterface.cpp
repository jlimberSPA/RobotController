//
//
//

#include "KeypadInterface.h"

char ControllerKeyPad::GetKey()
{
	char key = _keypad.getKey();
	return key;
}
String ControllerKeyPad::GetString(int aNumChars) {
	String result = "";
	while (result.length() < aNumChars) {
		char key = _keypad.getKey();
		result += key;
	}
	return result;
}