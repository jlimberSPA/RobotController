//
//
//
#ifndef _JML_TFT_LIBRARY_h
#include "JML_TFT_Library_V2.h"
#endif

#ifndef HEADER_STD_MEMORY
#include<memory>
#endif

//namespace stsn = SeeedTouchScreenNamespace;
//using namespace stsn;
//class stsn::Point;
constexpr unsigned short MIN_X = 0;
constexpr unsigned short MAX_X = 200;
constexpr unsigned short MIN_Y = 0;
constexpr unsigned short MAX_Y = 300;

namespace JML_TFT_Library_V2
{
#pragma region Page
	Page::Page(const char* aName) : mName{ aName },
		mDPtitle{ DrawParameters(MIN_Y + 2, MAX_X / 4, mHeaderHt, MAX_X / 2,
							WHITE, BLACK) },
		mDPnext{ DrawParameters(MAX_Y - mFooterHt - 2, MAX_X / 2 + 5, mFooterHt, MAX_X / 2 - 15,
							WHITE, BLACK) },
		mDPprevious{ DrawParameters(MAX_Y - mFooterHt - 2, 10, mFooterHt, MAX_X / 2 - 15, WHITE, BLACK) },
		mTitle{ AddTextBox("Title", mDPtitle, aName) }//,
		//	mPreviousPg{ AddButton(mDPprevious, (char*)"PreviousPage",nullptr) }, //::select) },  // aLastPgFunc);
		//	mNextPg{ AddButton(mDPnext, (char*)"Next Page", nullptr) } // , PushOptions::select)  //aNextPgFunc);
	{
		PseudoSerial::print(F("--- New Page "));
		PseudoSerial::print(Name());
		PseudoSerial::println(F(" Created with:"));
		RollCall();
	}

	ControlType* Page::AddTextBox(const char* aName, DrawParameters& aDP, const char* aTxt)
	{
		PseudoSerial::print(F("\n\nBeginning to Add Text Box '"));
		PseudoSerial::print(aName);
		PseudoSerial::print(F("' Page currently has '"));
		PseudoSerial::print(mPageControls.size());
		PseudoSerial::print(F("' controls and '"));
		PseudoSerial::print(mPageControls.capacity());
		PseudoSerial::println(F("' capacity."));
		mPageControls.reserve(1);
		ControlType* ct = ControlTypeFactory::Build(aName, ControlTypes::TextBox, aDP);
		mPageControls.push_back(ct);

		PseudoSerial::print(F("Roll Call from 'Page::AddTextBox' after creating '"));
		PseudoSerial::print(ct->ToString());
		PseudoSerial::println(F("'"));

		PseudoSerial::print(F("\tOn '"));
		PseudoSerial::print(ToString());
		PseudoSerial::print(F("' with '"));
		PseudoSerial::print(mPageControls.size());
		PseudoSerial::print(F("' CTs and '"));
		PseudoSerial::print(mPageControls.capacity());
		PseudoSerial::println(F("' capacity."));
		ct->RollCall();

		PseudoSerial::println(F("Now Trying with last element of mPageControls:"));
		ControlType* tmp = mPageControls.back();
		tmp->RollCall();

		return ct;
	}

	ControlType* Page::AddButton(const char* aName, DrawParameters& aDP,
		const char* aTxt, EventHandlerFunction aEHF)
	{
		ControlType* ct = ControlTypeFactory::Build(aName, ControlTypes::Button, aDP, aEHF);
		mPageControls.push_back(ct);
		return ct;
	}

	//Button& Page::AddButton(ControlElement& aControl, EventHandlerFunction aEvt)
	//{
	//	Button btn = Button(aControl);
	//	mPageButtons.push_back(btn); //, aEvt));
	//	mPageControlWrappers.push_back(btn);
	//	return mPageButtons.back();
	//}
	//Button& Page::AddButton(const char* aTxt,
	//	const unsigned short aTop, const unsigned short aLeft,
	//	const unsigned short aHeight, const unsigned short aWidth,
	//	const unsigned short aForeGround, const unsigned short  aBackground,
	//	EventHandlerFunction aEHF, PushOptions aPush)
	//{
	//	ControlElement aControl = ControlElement(aTxt, aTop, aLeft, aHeight, aWidth,
	//		aForeGround, aBackground, aEHF, aPush);
	//	Button btn = Button(aControl);
	//	mPageButtons.push_back(btn); //, aEvt));
	//	mPageControlWrappers.push_back(btn);
	//	return mPageButtons.back();
	//}

	//void Page::AddJoystickDisplay(ControlElement& aControl)
	//{
	//	//JoystickDisplayControl* jsd = &JoystickDisplayControl(
	//	//	mScreen, aName, aTxt,
	//	//	aTop, aLeft,
	//	//	aForeGround, aBackground);

	//	//mPageControls.push_back(*jsd);
	//	//mPageControls.push_back(jsd);
	//}

	//TextBox& Page::AddTextBox(ControlElement& aControl, char* aCaption = "", char* aValue = "")
	//{
	//	TextBox tb = TextBox(aControl, aCaption, aValue);
	//	mPageTextBoxes.push_back(tb);
	//	mPageControlWrappers.push_back(tb);
	//	return mPageTextBoxes.back();
	//}
	//TextBox& Page::AddTextBox(
	//	const unsigned short aTop, const unsigned short aLeft,
	//	const unsigned short aHeight, const unsigned short aWidth,
	//	const unsigned short aForeGround, const unsigned short  aBackground,
	//	char* aCaption = "", char* aValue = "")
	//{
	//	ControlElement aControl = ControlElement(aCaption, aTop, aLeft, aHeight, aWidth,
	//		aForeGround, aBackground);
	//	TextBox tb = TextBox(aControl);
	//	tb.SetCaption(aCaption);
	//	tb.SetValue(aValue);
	//	mPageTextBoxes.push_back(tb);
	//	mPageControlWrappers.push_back(tb);
	//	return mPageTextBoxes.back();
	//}
	//void Page::AddTextPanel(ControlElement& aControl)
	//{
	//	//TextPanel* tp = &TextPanel(
	//	//	mScreen, aName, aTxt,
	//	//	aTop, aLeft,
	//	//	aHeight, aWidth,
	//	//	aForeGround, aBackground);
	//	//mPageControls.push_back(*tp);
	//	//mPageControls.push_back(tp);
	//	//return tp;
	//}

	//int Page::NumControls(ControlTypes aCtlType)
	//{
	//	auto cwv = GetControlWrapperVector<TextBox>();
	//	return 1;
	//
	//}

	char* Page::ToString() const
	{
		char _output[128];
		strcat_s(_output, "Page: ");
		strcat_s(_output, Name());
		return _output;
	}

	void Page::RollCall() const
	{
		auto sz = mPageControls.size();
		PseudoSerial::print(F("\t"));
		PseudoSerial::print(ToString());
		PseudoSerial::print(F(" with the following "));
		PseudoSerial::print(sz);
		PseudoSerial::println(F(" ControlTypes"));
		for (auto ctl : mPageControls)
		{
			ctl->RollCall();
		}
		PseudoSerial::print(F("\tFinished "));
		PseudoSerial::println(ToString());
	}

	void Page::Refresh() const
	{
		PseudoSerial::print(F("\t - Refreshing Page:"));
		PseudoSerial::print(ToString());
		PseudoSerial::println(F("Past ToString"));
		int ctlNum = 0;
		for (auto& ctl : mPageControls)
		{
			PseudoSerial::print((char*)(ctlNum++));
			PseudoSerial::print(F(" "));
			if (ctl->IsValid())
			{
				ctl->Draw();
			}
			else
			{
				PseudoSerial::print(F(" - Invalid Draw\n"));
			}
		}
	}

	void Page::DrawAll() const
	{
		for (auto& ctl : mPageControls)
		{
			if (ctl->IsValid()) { ctl->Draw(); }
		}
	}

	void Page::SetActive()
	{
		//Tft.drawRectangle(0, 0, MAX_X, MAX_Y, BLACK);
		DrawAll();
	}

	//void Page::HandleTouch(stsn::Point& aPoint)
	//{
	//	ControlType* TouchedControl = GetByPoint(aPoint);
	//	if (TouchedControl->GetString("Text1") == mPageControls[0]->GetString("Text1"))		// Only true if a Control was found (<>nullPtr)
	//	{
	//		TouchedControl->Toggle();
	//	}
	//}

	//ControlType* Page::GetByPoint(stsn::Point& aPoint)
	//{
	//	//PseudoSerial::println("Looking for Point X: " + (char*)aPoint->x + ", Y: " + aPoint->y);

	//	for (auto ctlType : mPageControls)
	//	{
	//		if (ctlType->Contains(aPoint))
	//		{
	//			return ctlType;
	//		}
	//	}
	//	// Reference can't be null, just send reference to title
	//	return mPageControls[0];
	//}

#pragma endregion Page

#pragma region LCD_Panel_V2

#pragma endregion LCD_Panel_V2
	Page* LCD_Panel_V2::AddPage(const char* aName)
	{
		//**************

		// The problem is here.  THe page looses its name, or never gets it assigned
		// Output name is fine on line 188, but gibberish on line 194.

		// ************
		PseudoSerial::print(F("Adding Page:"));
		PseudoSerial::println(aName);
		Page tmp = Page(aName);
		Page* newPage = &tmp; // , lastPG_EHF, nextPg_EHF);
		mPages.push_back(newPage);
		mActivePage = newPage;
		PseudoSerial::print(F(".  newPage address "));
		PseudoSerial::println((int)newPage);
		return newPage;
	}
	//void LCD_Panel_V2::Toggle(stsn::Point aPoint)
	//{
	//	GetActivePage()->HandleTouch(aPoint);
	//}

	bool LCD_Panel_V2::NextPage()
	{
		mPage_Iter++;
		if (LCD_Panel_V2::mPage_Iter == LCD_Panel_V2::mPages.end())
		{
			LCD_Panel_V2::mPage_Iter = LCD_Panel_V2::mPages.begin();
		}
		mActivePage = *mPage_Iter;
		return true;
	}
	bool LCD_Panel_V2::LastPage()
	{
		mPage_Iter--;
		if (mPage_Iter == mPages.begin())
		{
			mPage_Iter = mPages.end();
		}
		mActivePage = *mPage_Iter;
		return true;
	}

	void LCD_Panel_V2::SetActivePage(Page* aPage)
	{
		mActivePage = aPage;
		*mPage_Iter = mActivePage;
	}

	void LCD_Panel_V2::RollCall() const
	{
		PseudoSerial::println(F("LCD Panel Roll Call:"));
		for (auto pg : mPages)
		{
			pg->RollCall();
		}
	}
}