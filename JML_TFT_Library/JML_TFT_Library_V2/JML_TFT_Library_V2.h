#ifndef _JML_TFT_LIBRARY_h
#define _JML_TFT_LIBRARY_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#ifndef __HEADER_CSTDLIB
#include <cstdlib>
#endif
#ifndef _STDLIB_H_
#include <stdlib.h>
#endif
//#ifndef __HEADER_TYPE_TRAITS
//#include <type_traits>
//#endif
#ifndef _GCC_WRAP_STDINT_H
#include <stdint.h>
#endif
#ifndef TFTv2_h
#include <TFTv2.h>
#endif // !TFTv2_h
#ifndef SeeedTouchScreen	// Should be defined in Robot_Hand_Controller.ino
#include <SeeedTouchScreen.h>
#endif
#ifndef __STD_HEADER_VECTOR
#include <vector>
#endif
// Colors for this display are 16 bit, this means they use a two byte notation vs 3 bytes for RGB
// 139 colors are defined in the following file:
#ifndef _DRAWPARAMETERS_h
#include "DrawParameters.h"
#endif

#ifndef _CONTROLELEMENT_h
#include "ControlElement.h"
#endif

#ifndef _CONTROLTYPE_h
#include "ControlType.h"
#endif

#ifndef _TFT_COLORS_h
#include "JML_TFT_Colors.h"
#endif

#include <list>
#include "Page.h"
namespace stsn = SeeedTouchScreenNamespace;
using namespace stsn;
//class stsn::Point;

namespace JML_TFT_Library_V2
{
	// EventHandlerFunction is a Generic function definition that will be used with function pointers
	// It will allow each button to be assigned a specific callback function to call when pressed
//#ifndef _JML_SUPPORT_TYPES
//#define _JML_SUPPORT_TYPES
//	//using SeeedPt = stsn::Point;
//	enum class PushOptions :uint8_t { none, select, unselect, toggle };
//	typedef bool (*EventHandlerFunction)();
//	enum class ControlTypes :uint8_t { TextBox, TextPanel, Button, JSD };
//	class IControlType;
//	class ControlElement;
//#endif

	// LCD_Panel_V2 uses the singleton pattern
	// The constructor is private, so instances can't be created directly
	// Instead the GetInstance method provides access to the one and only instance
	// If it hasn't been created yet, it creates it.  Otherwise it just returns it.
	class LCD_Panel_V2
	{
	public:
		static LCD_Panel_V2* GetInstance(IScreen aTFT);
		~LCD_Panel_V2() = default;

		// Property Getters
		Page* GetActivePage() const { return mActivePage; }
		stsn::TouchScreen* GetTouchPanel() { return &myTouchPanel; };

		// Methods
		Page* AddPage(char* aName);
		Page* AddPage(const __FlashStringHelper* aName);
		void SetActivePage(Page* aPage);
		void RollCall() const;
		void Toggle(stsn::Point aPoint) const;
		void ReDraw() const
		{
			GetActivePage()->Refresh();
		};
		bool NextPage();
		bool LastPage();
	private:
		// Private Constructor
		LCD_Panel_V2() {};
		LCD_Panel_V2(LCD_Panel_V2& panel) = delete;
		LCD_Panel_V2(LCD_Panel_V2* panel) = delete;
		LCD_Panel_V2(LCD_Panel_V2** panel) = delete;
		void operator=(const LCD_Panel_V2* panel) = delete;

		static LCD_Panel_V2* mInstance;
		static bool mInitialized;
		static IScreen myTFT;
		// Private Methods for EventHandlers
		//bool (*nextPg_EHF)() = *NextPage;
		//bool (*lastPg_EHF)();

		// Need to fully qualify NextPage and Last Page
		// warning: ISO C++ forbids taking the address of an unqualified or parenthesized non-static member function to form a pointer to member function
		EventHandlerFunction nextPg_EHF = (EventHandlerFunction)&JML_TFT_Library_V2::LCD_Panel_V2::NextPage;
		EventHandlerFunction lastPG_EHF = (EventHandlerFunction)&JML_TFT_Library_V2::LCD_Panel_V2::LastPage;

		// Backing Fields
		std::vector<Page*> mPages;

		// Note: mPage_Iter and mActivePage can't be initialized until there is a Page to point to.
		// This is done in AddPage, and gets updated every time a page is added.
		std::vector<Page*>::iterator mPage_Iter;
		Page* mActivePage;

		stsn::TouchScreen myTouchPanel = stsn::TouchScreen(XP, YP, XM, YM);
	};
}
#endif