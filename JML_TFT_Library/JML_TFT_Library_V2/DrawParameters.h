// DrawParameters.h

#ifndef _DRAWPARAMETERS_h
#define _DRAWPARAMETERS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#ifndef _TFT_COLORS_h
#include "JML_TFT_Colors.h"
#endif

#include <SeeedTouchScreen.h>
namespace stsn = SeeedTouchScreenNamespace;
using namespace stsn;
//class stsn::Point;

namespace JML_TFT_Library_V2
{
	//class stsn::Point;

#ifndef _JML_SUPPORT_TYPES

#define _JML_SUPPORT_TYPES
	//using namespace stsn;
	//using SeeedPt = stsn::Point;
	enum class PushOptions :uint8_t { none, select, unselect, toggle };
	typedef bool (*EventHandlerFunction)();
	enum class ControlTypes :uint8_t { TextBox, TextPanel, Button, JSD };
	class IControlType;
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
		bool Contains(stsn::Point* aPoint) const;
		void SetColor(unsigned short  aForeground, unsigned short  aBackground);
		String ToString() const;
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