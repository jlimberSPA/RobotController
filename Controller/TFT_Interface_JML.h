// TFT_Interface_JML.h

#ifndef _TFT_INTERFACE_JML_h
#define _TFT_INTERFACE_JML_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#endif
#include <vector>
#include <stdint.h>

#include <TFTv2.h>
#include <SeeedTouchScreen.h>
//
//
//#include "SeeedTouchScreen.h"	// Display Control
//#include "TFTv2.h"				// Touch Sensor
//#ifndef __PRESSURE
//	#include "..\..\libraries\TFT_Touch_Shield_v2.0\TFTv2.h"
//	#include "..\..\libraries\TFT_Touch_Shield_v2.0\SeeedTouchScreen.h"
//#endif // !__PRESSURE


#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) // mega
#define YP A2   // must be an analog pin, use "An" notation!
#define XM A1   // must be an analog pin, use "An" notation!
#define YM 54   // can be a digital pin, this is A0
#define XP 57   // can be a digital pin, this is A3

#elif defined(__AVR_ATmega32U4__) // leonardo
#define YP A2   // must be an analog pin, use "An" notation!
#define XM A1   // must be an analog pin, use "An" notation!
#define YM 18   // can be a digital pin, this is A0
#define XP 21   // can be a digital pin, this is A3
#elif defined(ARDUINO_SAMD_VARIANT_COMPLIANCE) // samd21

#define YP A2   // must be an analog pin, use "An" notation!
#define XM A1   // must be an analog pin, use "An" notation!
#define YM A4   // can be a digital pin, this is A0
#define XP A3   // can be a digital pin, this is A3
#undef ShowSerial
#define ShowSerial SerialUSB

#else //168, 328, something else
#define YP A2   // must be an analog pin, use "An" notation!
#define XM A1   // must be an analog pin, use "An" notation!
#define YM 14   // can be a digital pin, this is A0
#define XP 17   // can be a digital pin, this is A3

#endif

//Measured ADC values for (0,0) and (210-1,320-1)
//TS_MINX corresponds to ADC value when X = 0
//TS_MINY corresponds to ADC value when Y = 0
//TS_MAXX corresponds to ADC value when X = 240 -1
//TS_MAXY corresponds to ADC value when Y = 320 -1

#define TS_MINX 116*2
#define TS_MAXX 890*2
#define TS_MINY 83*2
#define TS_MAXY 913*2


// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// The 2.8" TFT Touch shield has 300 ohms across the X plate


namespace TFT_Interface_JML
{
	// EventHandlerFunction is a Generic function definition that will be used with function pointers
	// It will allow each button to be assigned a specific callback function to call when pressed
	typedef bool (*EventHandlerFunction)();

	class Button
	{
	public:
		Button();
//		Button(LCD_Panel_V2);
		Button(String aName,
			unsigned short  aTop, unsigned short  aLeft,
			unsigned short  aHeight, unsigned short  aWidth,
			char* aTxt,
			unsigned short  aForeGround, unsigned short  aBackground);
		Button(String aName,
			unsigned short  aTop, unsigned short  aLeft,
			unsigned short  aHeight, unsigned short  aWidth,
			char* aTxt,
			unsigned short  aForeGround, unsigned short  aBackground, 
			EventHandlerFunction aEHF);

		~Button();
		int Left();
		int Top();
		int Width();
		int Height();
		int Right();
		int Bottom();

		void Draw();
		void Flash();
		void Select();
		void UnSelect();
		void Toggle();
		bool IsValid();
		bool Contains(Point aPoint);

		String Name();
		void SetName(String aName);
		void SetPos(unsigned short  aTop, unsigned short  aLeft);
		void SetSize(unsigned short  aHeight, unsigned short  aWidth);
		void SetText(char* aTxt);
		void SetColor(unsigned short  aForeground, unsigned short  aBackground);

	private:
		// Defines a variable of type EventHandlerFunction (a function pointer)
		// to hold a reference to the function for the OnClick event
		EventHandlerFunction OnClickEventHandler;
		unsigned short  mTop = -1;
		unsigned short  mLeft = -1;
		unsigned short  mWidth = 20;
		unsigned short  mHeight = 10;
		unsigned short mForeground;
		unsigned short mBackground;
		bool mSelected;
		String mName;
		char* mTxt;
//		LCD_Panel_V2 mTs;
	};

	class LCD_Panel_V2
	{

	public:
		LCD_Panel_V2();
		~LCD_Panel_V2();
		TouchScreen myTouchPanel();
		void AddButton(String, unsigned short, unsigned short, unsigned short, unsigned short, char*, unsigned short, unsigned short);
		void AddButton(String, unsigned short, unsigned short, unsigned short, unsigned short, char*, unsigned short, unsigned short, EventHandlerFunction);
		void Select(Point aPoint);
		void Toggle(Point aPoint);
		void Select(String aName);
		void Toggle(String aName);

	private:
		void ReDraw();
		TouchScreen mTouch = TouchScreen(XP, YP, XM, YM);
		std::vector<Button> mBtns = std::vector<Button>();
		Button* GetByName(String aName);
		Button* GetByPoint(Point aPoint);

	};



}