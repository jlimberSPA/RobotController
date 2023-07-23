/*
 Name:		JML_TFT_Library.h
 Created:	3/6/2023 10:12:16 PM
 Author:	jmlma
 Editor:	http://www.visualmicro.com
*/

//#ifndef _JML_TFT_Library_h
//#define _JML_TFT_Library_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <stdint.h>
#ifndef TFTv2_h
#include <TFTv2.h>
#endif

#ifndef SeeedTouchScreen	// Should be defined in Robot_Hand_Controller.ino
#include <SeeedTouchScreen.h>
#endif
#include <array>
#include <vector>

//#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) // mega
//#define YP A2   // must be an analog pin, use "An" notation!
//#define XM A1   // must be an analog pin, use "An" notation!
//#define YM 54   // can be a digital pin, this is A0
//#define XP 57   // can be a digital pin, this is A3
//
//#elif defined(__AVR_ATmega32U4__) // leonardo
//#define YP A2   // must be an analog pin, use "An" notation!
//#define XM A1   // must be an analog pin, use "An" notation!
//#define YM 18   // can be a digital pin, this is A0
//#define XP 21   // can be a digital pin, this is A3
//#elif defined(ARDUINO_SAMD_VARIANT_COMPLIANCE) // samd21
//
//#define YP A2   // must be an analog pin, use "An" notation!
//#define XM A1   // must be an analog pin, use "An" notation!
//#define YM A4   // can be a digital pin, this is A0
//#define XP A3   // can be a digital pin, this is A3
//#undef ShowSerial
//#define ShowSerial SerialUSB
//
//#else //168, 328, something else
////#define YP A2   // must be an analog pin, use "An" notation!
////#define XM A1   // must be an analog pin, use "An" notation!
////#define YM 14   // can be a digital pin, this is A0
////#define XP 17   // can be a digital pin, this is A3
//
//#endif
//
//Measured ADC values for (0,0) and (210-1,320-1)
//TS_MINX corresponds to ADC value when X = 0
//TS_MINY corresponds to ADC value when Y = 0
//TS_MAXX corresponds to ADC value when X = 240 -1
//TS_MAXY corresponds to ADC value when Y = 320 -1
//
//#define TS_MINX 116*2
//#define TS_MAXX 890*2
//#define TS_MINY 83*2
//#define TS_MAXY 913*2
//
// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// The 2.8" TFT Touch shield has 300 ohms across the X plate
//
// The following colors should already be defined for the display in TFTv2.h
// They are repeated here for reference only
//#ifndef BLACK
////Basic Colors
//#define RED		0xf800
//#define GREEN	0x07e0
//#define BLUE	0x001f
//#define BLACK	0x0000
//#define YELLOW	0xffe0
//#define WHITE	0xffff
//
////Other Colors
//#define CYAN		0x07ff
//#define BRIGHT_RED	0xf810
//#define GRAY1		0x8410
//#define GRAY2		0x4208
//#endif // !BLACK

// Colors for this display are 16 bit, this means they use a two byte notation vs 3 bytes for RGB
// 139 colors are defined in the following file:
#include "JML_TFT_Colors.h"

// EventHandlerFunction is a Generic function definition that will be used with function pointers
// It will allow each button to be assigned a specific callback function to call when pressed
typedef bool (*EventHandlerFunction)();

namespace JML_TFT_Library
{
	using SeeedPt = SeeedTouchScreenNamespace::Point;
	//	class TFT;
	enum class PushOptions :uint8_t { none, select, unselect, toggle };
	enum class ControlTypes :uint8_t { Control, TextBox, TextPanel, Button, JSD };

	class Control
	{
	public:
		Control();
		Control(const char* aName, TFT* aScreen, const char* aTxt,
			const unsigned short aTop, const unsigned short aLeft,
			const unsigned short aHeight, const unsigned short aWidth,
			const unsigned short aForeGround, const unsigned short  aBackground);
		Control(const char* aName, TFT* aScreen, const char* aTxt,
			const unsigned short aTop, const unsigned short aLeft,
			const unsigned short aHeight, const unsigned short aWidth,
			const unsigned short aForeGround, const unsigned short  aBackground,
			PushOptions aPush);
		Control(const char* aName, TFT* aScreen, const char* aTxt,
			const unsigned short aTop, const unsigned short aLeft,
			const unsigned short aHeight, const unsigned short aWidth,
			const unsigned short aForeGround, const unsigned short  aBackground,
			PushOptions aPush, EventHandlerFunction aEHF);
		~Control();

		// Property Getters
		int Left() const;
		int Top() const;
		int Width() const;
		int Height() const;
		int Right() const;
		int Bottom() const;
		char* Text() const;
		const char* Name() const;
		const bool IsValid() const;
		virtual String ToString() const;
		virtual ControlTypes ControlType()  const { return ControlTypes::Control; };

		// Property Setters
		void SetName(char* aName);
		void SetPos(unsigned short  aTop, unsigned short  aLeft);
		void SetSize(unsigned short  aHeight, unsigned short  aWidth);
		void SetText(char* aTxt);
		void SetColor(unsigned short  aForeground, unsigned short  aBackground);

		// Methods
		virtual void Draw() const;
		void Flash();
		void Select();
		void UnSelect();
		virtual void Toggle();

		bool Contains(SeeedPt aPoint) const;

		//const char* ControlTypeToString()  const noexcept
		//{
		//	switch (ControlType())
		//	{
		//	case ControlTypes::Control: return "Control";
		//	case ControlTypes::TextBox: return "TextBox";
		//	case ControlTypes::TextPanel: return "TextPanel";
		//	case ControlTypes::Button: return "Button";
		//	case ControlTypes::JSD: return "JSD";
		//	}
		//}
	protected:
		unsigned short mForeground = BLACK;
		unsigned short mBackground = WHITE;
		// Backing Fields
		bool mSelected = false;
		const char* mName = "";
		char* mTxt;				 // = 0;

		unsigned short  mTop;    // = -1;
		unsigned short  mLeft;   // = -1;
		unsigned short  mWidth;  // = 20;  removed because of error: JML_TFT_Library.h: 172:29: warning: 'JML_TFT_Library::Control::mHeight'
		unsigned short  mHeight; // = 10;  will be initialized after [-Wreorder] unsigned short  mHeight = 10

		// Defines a variable of type EventHandlerFunction (a function pointer)
		// to hold a reference to the function for the OnClick event
		EventHandlerFunction OnClickEventHandler;
		bool mHasEHF = false;

		// Backing Fields
		PushOptions		mPush = PushOptions::none;
		TFT* mScreen;
	};

	class TextBox : public Control
	{
	public:
		TextBox();
		TextBox(TFT* aScreen, const char* aName, const char* aTxt,
			const unsigned short aTop, const unsigned short aLeft,
			const unsigned short aHeight, const unsigned short aWidth,
			const unsigned short aForeGround, const unsigned short  aBackground);
		~TextBox();

		void Draw();

		ControlTypes ControlType() { return ControlTypes::TextBox; };

		void SetCaption(char* aCaption);
		void SetValue(char* aVal);
		String ToString();
		char* GetText();

	private:
		char* mVal;
		char* mCaption;
	};

	class TextPanel : public Control
	{
	public:
		TextPanel();
		TextPanel(TFT* aScreen, const char* aName, const char* aTxt,
			const unsigned short aTop, const unsigned short aLeft,
			const unsigned short aLines, const unsigned short aWidth,
			const unsigned short aForeGround, const unsigned short  aBackground);

		~TextPanel();
		ControlTypes ControlType() { return ControlTypes::TextPanel; };
		// Methods
		void writeln(String aStr);
		void Draw();
	private:
		// Backing Fields
		const static unsigned short mMaxLines = 10;
		const static int mLineHeight = 20;
		std::array<String, mMaxLines> mRows;
	};
	class Button : public Control
	{
	public:
		Button();
		//		Button(LCD_Panel_V2);
		Button(const char* aTxt,
			const unsigned short aTop, const unsigned short aLeft,
			const unsigned short aHeight, const unsigned short aWidth,
			const unsigned short aForeGround, const unsigned short  aBackground,
			PushOptions aPush);
		Button(const char* aTxt,
			const unsigned short aTop, const unsigned short aLeft,
			const unsigned short aHeight, const unsigned short aWidth,
			const unsigned short aForeGround, const unsigned short  aBackground,
			PushOptions aPush,
			EventHandlerFunction aEHF);

		~Button();

		// Methods
		void Toggle();

		// Property Getters
		String ToString();
		void OnPushed();
		ControlTypes ControlType() { return ControlTypes::Button; };

	private:
	};

	/**
	@brief This class represents an on-screen control to display the X/Y position of the joystick
	*/
	class JoystickDisplayControl : public Control
	{
	public:
		JoystickDisplayControl();
		JoystickDisplayControl(TFT* aScreen, const char* aName, const char* aTxt,
			const unsigned short aTop, const unsigned short aLeft,
			const unsigned short aForeGround, const unsigned short  aBackground);	/*@brief Constructor*/
		~JoystickDisplayControl() {};/*@brief Destructor*/

		void Update(uint16_t aJSx, uint16_t aJSy);
		void Draw();
		ControlTypes ControlType() { return ControlTypes::JSD; };
	private:
		void GetCenter();

		static const unsigned short mSize = 60;		/**< Control is Square, this is the dimension */
		int ctlCtrX = 0;
		int ctlCtrY = 0;

		TextBox mJoystick_X;
		TextBox mJoystick_Y;
		int16_t mJSx, mJSy;
		String xLbl, yLbl;
	};

	class Page
	{
	public:
		Page();
		Page(TFT* aScreen, const char* aName, EventHandlerFunction aLastPgFunc, EventHandlerFunction aNextPgFunc);
		~Page();

		// Property Accessors
		char* Name() { return mName; }

		// Methods:
		void AddButton(const char* aName, const char* aTxt,
			const unsigned short aTop, const unsigned short aLeft,
			const unsigned short aHeight, const unsigned short aWidth,
			const unsigned short aForeGround, const unsigned short  aBackground,
			PushOptions aPush);

		void AddButton(const char* aName, const char* aTxt,
			const unsigned short aTop, const unsigned short aLeft,
			const unsigned short aHeight, const unsigned short aWidth,
			const unsigned short aForeGround, const unsigned short  aBackground,
			PushOptions aPush,
			EventHandlerFunction aEvt);

		void AddJoystickDisplay(const char* aName, const char* aTxt,
			const unsigned short aTop, const unsigned short aLeft,
			const unsigned short aForeGround, const unsigned short  aBackground);

		void AddTextBox(const char* aName, const char* aTxt,
			const unsigned short aTop, const unsigned short aLeft,
			const unsigned short aHeight, const unsigned short aWidth,
			const unsigned short aForeGround, const unsigned short  aBackground);

		void AddTextPanel(const char* aName, const char* aTxt,
			const unsigned short aTop, const unsigned short aLeft,
			const unsigned short aHeight, const unsigned short aWidth,
			const unsigned short aForeGround, const unsigned short  aBackground);
		int NumControls();
		Control* GetControl(uint8_t aIdx);
		Control* GetControl(char* aName);
		String ToString();

		void AddToAutoRefreshList(char* aName);
		void AddToAutoRefreshList(Control* aCtl);
		void Refresh();
		void DrawAll();
		void SetActive();

		void Toggle(SeeedTouchScreenNamespace::Point aPoint);
		void Select(SeeedTouchScreenNamespace::Point aPoint);
		void Push(SeeedTouchScreenNamespace::Point aPoint);

	private:

		// Backing Fields
		char* mName;
		int mHeaderHt = 10;
		int mFooterHt = 30;
		Control* mTitle;
		Button* mNextPg;
		Button* mLastPg;

		std::vector<Control> mControls = std::vector<Control>();
		std::vector<Control*> mControls_ptrs = std::vector<Control*>();
		std::vector<Control*> mRefreshList = std::vector<Control*>();
		Button* LastButton;
		Control* GetByPoint(SeeedTouchScreenNamespace::Point aPoint);
		TFT* mScreen;
	};

	class LCD_Panel_V2
	{
	public:
		LCD_Panel_V2();
		~LCD_Panel_V2();

		// Property Getters
		SeeedTouchScreenNamespace::TouchScreen* myTouchPanel();
		TFT* myScreen;
		Page GetPage(int idx);
		Page* GetActivePage();
		String PageCount();
		Page* AddPage(char* aName);
		String ToString();
		static int _pageCount;

		// Methods
		void SetActivePage(Page* aPage);

		void Select(SeeedTouchScreenNamespace::Point aPoint);
		void Toggle(SeeedTouchScreenNamespace::Point aPoint);
		void Select(char* aName);
		void Toggle(char* aName);
		void Push(SeeedTouchScreenNamespace::Point aPoint);

		// ************ Next Step ***************
		// add method for selecting active pages
		void ReDraw();
		bool NextPage();
		bool LastPage();
	private:

		// Private Methods for EventHandlers

		EventHandlerFunction nextPg_EHF = (EventHandlerFunction)&JML_TFT_Library::LCD_Panel_V2::NextPage;
		EventHandlerFunction lastPG_EHF = (EventHandlerFunction)&JML_TFT_Library::LCD_Panel_V2::LastPage;

		// Backing Fields
		SeeedTouchScreenNamespace::TouchScreen mTouch = SeeedTouchScreenNamespace::TouchScreen(XP, YP, XM, YM);
		static std::vector<Page> mPages;
		std::vector<Page>::iterator mPage_Iter;
		Page* mActivePage;

		// Methods

		Control* GetByName(char* aName);
		//Control* GetByPoint(SeeedTouchScreen::Point aPoint);
	};
}
