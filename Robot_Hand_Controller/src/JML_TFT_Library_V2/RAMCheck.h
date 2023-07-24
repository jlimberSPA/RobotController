// RAMCheck.h

#ifndef _RAMCHECK_h
#define _RAMCHECK_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

//namespace JML_TFT_Library_V2

class RAMCheck
{
public:
	RAMCheck() = default;
	~RAMCheck() = default;
	static int freeRam() {
		extern int __heap_start, * __brkval;
		int v;
		return (int)&v - (__brkval == 0
			? (int)&__heap_start : (int)__brkval);
	}
	static void display_freeram() {
		Serial.print(F("- SRAM left: "));
		Serial.println(freeRam());
	}
};
//}
#endif
