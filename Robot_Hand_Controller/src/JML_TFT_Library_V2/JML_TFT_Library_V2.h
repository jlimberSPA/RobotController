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
#ifndef __HEADER_TYPE_TRAITS
#include <type_traits>
#endif
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

namespace stsn = SeeedTouchScreenNamespace;
using namespace stsn;
class stsn::Point;

namespace JML_TFT_Library_V2
{
	// EventHandlerFunction is a Generic function definition that will be used with function pointers
	// It will allow each button to be assigned a specific callback function to call when pressed
#ifndef _JML_SUPPORT_TYPES
#define _JML_SUPPORT_TYPES
	//using SeeedPt = stsn::Point;
	enum class PushOptions :uint8_t { none, select, unselect, toggle };
	typedef bool (*EventHandlerFunction)();
	enum class ControlTypes :uint8_t { TextBox, TextPanel, Button, JSD };
	class ControlType;
	class ControlElement;
#endif

	//const char* ControlTypeToString(ControlTypes aCT)  noexcept
	//{
	//	switch (aCT)
	//	{
	//	case ControlTypes::TextBox: return "TextBox";
	//	case ControlTypes::TextPanel: return "TextPanel";
	//	case ControlTypes::Button: return "Button";
	//	case ControlTypes::JSD: return "JSD";
	//	}
	//}

	class Page
	{
	public:
		Page() = delete;
		Page(char* aName);
		~Page() = default;

		// Property Accessors
		String Name() const { return (String)mName; }

		// Methods:
		ControlType* AddTextBox(char* aName, DrawParameters& aDP, char* aTxt);
		ControlType* AddButton(char* aName, DrawParameters& aDP, char* aTxt, EventHandlerFunction aEHF);

		//Button& AddButton(ControlElement& aControl, EventHandlerFunction aEvt);
		//Button& AddButton(const char* aTxt,
		//	const unsigned short aTop, const unsigned short aLeft,
		//	const unsigned short aHeight, const unsigned short aWidth,
		//	const unsigned short aForeGround, const unsigned short  aBackground,
		//	EventHandlerFunction aEHF, PushOptions aPush);
		//void AddJoystickDisplay(ControlElement& aControl);
		//TextBox& AddTextBox(ControlElement& aControl, char* aCaption = "", char* aValue = "");
		//TextBox& AddTextBox(
		//	const unsigned short aTop, const unsigned short aLeft,
		//	const unsigned short aHeight, const unsigned short aWidth,
		//	const unsigned short aForeGround, const unsigned short  aBackground,
		//	char* aCaption = "", char* aValue = "");
		//void AddTextPanel(ControlElement& aControl);
		//int GetNumControls(ControlTypes ct)
		//{
		//	switch (ct) {
		//	case ControlTypes::TextBox:
		//		return sizeof(mPageTextBoxes) / sizeof(TextBox);
		//	case ControlTypes::Button:
		//		return sizeof(mPageButtons) / sizeof(Button);
		//	case ControlTypes::TextPanel:
		//		return sizeof(mPageTextPanels) / sizeof(TextPanel);
		//	case ControlTypes::JSD:
		//		return sizeof(mPageJSDs) / sizeof(JoystickDisplayControl);
		//	}
		//}

		String ToString() const;
		void RollCall() const;

		//		void AddToAutoRefreshList(ControlType& aCtl);
		void Refresh() const;
		void DrawAll() const;
		void SetActive();

		void HandleTouch(stsn::Point& aPoint);

	private:

		// Backing Fields
		char* mName;
		int mHeaderHt = 10;
		int mFooterHt = 30;
		DrawParameters mDPtitle;
		DrawParameters mDPnext;
		DrawParameters mDPprevious;
		ControlType* mTitle;
		//ControlType& mNextPg;
		//ControlType& mPreviousPg;

		std::vector<ControlType*> mPageControls = std::vector<ControlType*>();
		ControlType* GetByPoint(stsn::Point& aPoint);
		//void Page::Update(std::vector<ControlElement&>& aControlList);
	};

	class LCD_Panel_V2
	{
	public:
		LCD_Panel_V2() {};
		~LCD_Panel_V2() = default;

		// Property Getters
		Page* GetActivePage() { return mActivePage; }
		Page* AddPage(char* aName);

		stsn::TouchScreen& GetTouchPanel() { return myTouchPanel; }

		//TFT* myScreen;
		//Page GetPage(int idx);
		//String PageCount();
		//String ToString();
		//static int _pageCount;

		// Methods
		void SetActivePage(Page* aPage);
		void RollCall() const;
		//void Select(stsn::Point aPoint);
		void Toggle(stsn::Point aPoint);
		//void Select(char* aName);
		//void Toggle(char* aName);
		//void Push(stsn::Point aPoint);

		//void FullRefresh();
		void ReDraw()
		{
			GetActivePage()->Refresh();
		};
		bool NextPage();
		bool LastPage();
	private:
		//void SetActivePage(Page* aPage);

		// Private Methods for EventHandlers

		EventHandlerFunction nextPg_EHF = (EventHandlerFunction)&JML_TFT_Library_V2::LCD_Panel_V2::NextPage;
		EventHandlerFunction lastPG_EHF = (EventHandlerFunction)&JML_TFT_Library_V2::LCD_Panel_V2::LastPage;

		// Backing Fields
		std::vector<Page*> mPages;
		std::vector<Page*>::iterator mPage_Iter;
		Page* mActivePage;

		stsn::TouchScreen myTouchPanel =
			stsn::TouchScreen(XP, YP, XM, YM);
	};
}
#endif