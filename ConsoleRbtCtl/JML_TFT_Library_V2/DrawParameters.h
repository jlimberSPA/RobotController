// DrawParameters.h

#ifndef _DRAWPARAMETERS_h
#define _DRAWPARAMETERS_h

#ifndef _PSEUDOSERIAL_H
#include "../PseudoSerial.h"
#endif

#include <functional>

//#if defined(ARDUINO) && ARDUINO >= 100
//#include "arduino.h"
//#else
//#include "WProgram.h"
//#endif
//#ifndef _TFT_COLORS_h
//#include "JML_TFT_Colors.h"
//#endif
//#include <SeeedTouchScreen.h>
//namespace stsn = SeeedTouchScreenNamespace;
//using namespace stsn;
//class stsn::Point;

namespace JML_TFT_Library_V2
{
#ifndef _JML_SUPPORT_TYPES

#define _JML_SUPPORT_TYPES
	enum class PushOptions :uint8_t { none, select, unselect, toggle };
	// EventHandlerFunction is a Generic function definition that will be used with function pointers
	// It will allow each button to be assigned a specific callback function to call when pressed
	//std::function<bool()> EVHF;

	// Source: Function pointers should not be used as function parameters
	// Code Smell  Major cpp : S5205 Tags : clumsy cppcoreguidelines
	using EventHandlerFunction = std::function<bool()>;

	enum class ControlTypes :uint8_t { TextBox, TextPanel, Button, JSD };
	class ControlType;
	class ControlElement;
#endif
	/*
	DRAW PARAMETERS:
	- This class provides the basic location and color parameters used for all Control Elements
	*/

	class DrawParameters
	{
	public:
		DrawParameters() = delete;
		DrawParameters(
			const unsigned short aTop, const unsigned short aLeft,
			const unsigned short aHeight, const unsigned short aWidth,
			const unsigned short aForeGround, const unsigned short  aBackground);
		~DrawParameters() = default;

		// Property Getters
		int Left() const;
		int Top() const;
		int Width() const;
		int Height() const;
		int Right() const;
		int Bottom() const;
		int Foreground() const;
		int Background() const;

		const bool IsValid() const;
		//bool Contains(stsn::Point* aPoint) const;
		void SetColor(unsigned short  aForeground, unsigned short  aBackground);
		char* ToString() const;
		void RollCall() const;
	protected:
		static unsigned short const defaultWidth = 20;
		static unsigned short const defaultHeight = 10;

	private:
		unsigned short const mTop;
		unsigned short const mLeft;
		unsigned short const mHeight;
		unsigned short const mWidth;

		unsigned short mForeground = BLACK;
		unsigned short mBackground = WHITE;

		bool mSelected = false;
	};
}
#endif