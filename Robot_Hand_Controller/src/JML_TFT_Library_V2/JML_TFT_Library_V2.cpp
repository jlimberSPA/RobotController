//
//
//
#ifndef _JML_TFT_LIBRARY_h
#include "JML_TFT_Library_V2.h"
#endif

#ifndef HEADER_STD_MEMORY
#include<memory>
#endif

namespace stsn = SeeedTouchScreenNamespace;
using namespace stsn;
class stsn::Point;

namespace JML_TFT_Library_V2
{
#pragma region Page
	Page::Page(char* aName) :
		mDPtitle{ DrawParameters(MIN_Y + 2, MAX_X / 4, mHeaderHt, MAX_X / 2,
							WHITE, BLACK) },
		mDPnext{ DrawParameters(MAX_Y - mFooterHt - 2, MAX_X / 2 + 5, mFooterHt, MAX_X / 2 - 15,
							WHITE, BLACK) },
		mDPprevious{ DrawParameters(MAX_Y - mFooterHt - 2, 10, mFooterHt, MAX_X / 2 - 15, WHITE, BLACK) },
		mTitle{ AddTextBox("Title", mDPtitle, aName) }//,
		//	mPreviousPg{ AddButton(mDPprevious, (char*)"PreviousPage",nullptr) }, //::select) },  // aLastPgFunc);
		//	mNextPg{ AddButton(mDPnext, (char*)"Next Page", nullptr) } // , PushOptions::select)  //aNextPgFunc);
	{
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

	String Page::ToString()
	{
		String _output = "Page: " + (String)mName + " All Controls:";
		_output += "\n\t";
		Serial.print(mName);
		for (auto ctl : mPageControls)
		{
			_output = "\n\t\t";
			_output += ctl->ToString();
			Serial.print(_output);
		}
		_output += "\n";
	}

	void Page::Refresh()
	{
		Serial.print("\n\t - Refreshing Page:");
		Serial.println((String)mName);
		Serial.print(ToString()); //"[" + (String)(mPageControls.size()) + "]ctls%%\n"
		Serial.println("Past ToString");
		for (auto& ctl : mPageControls)
		{
			if (ctl->IsValid())
			{
				ctl->Draw();
			}
			else
			{
				Serial.print(" - Invalid Draw\n");
			}
		}
	}

	void Page::DrawAll()
	{
		for (auto& ctl : mPageControls)
		{
			if (ctl->IsValid()) { ctl->Draw(); }
		}
	}

	void Page::SetActive()
	{
		Tft.drawRectangle(0, 0, MAX_X, MAX_Y, BLACK);
		DrawAll();
	}

	void Page::HandleTouch(stsn::Point& aPoint)
	{
		ControlType* TouchedControl = GetByPoint(aPoint);
		if (TouchedControl->GetString("Text1") == mPageControls[0]->GetString("Text1"))		// Only true if a Control was found (<>nullPtr)
		{
			TouchedControl->Toggle();
		}
	}

	ControlType* Page::GetByPoint(stsn::Point& aPoint)
	{
		//Serial.println("Looking for Point X: " + (String)aPoint->x + ", Y: " + aPoint->y);

		for (auto ctlType : mPageControls)
		{
			if (ctlType->Contains(aPoint))
			{
				return ctlType;
			}
		}
		// Reference can't be null, just send reference to title
		return mPageControls[0];
	}

#pragma endregion Page

#pragma region LCD_Panel_V2

#pragma endregion LCD_Panel_V2
	Page* LCD_Panel_V2::AddPage(char* aName)
	{
		//**************

		// The problem is here.  THe page looses its name, or never gets it assigned
		// Output name is fine on line 188, but gibberish on line 194.

		// ************
		Serial.println("Adding Page:" + (String)aName);
		Page tmp = Page(aName);
		Page* newPage = &tmp; // , lastPG_EHF, nextPg_EHF);
		mPages.push_back(newPage);
		mActivePage = newPage;
		Serial.print("Page Named: ");
		Serial.print(mActivePage->Name());
		Serial.print(".  newPage address ");
		Serial.print((int)newPage);
		Serial.print(" ActivePage address ");
		Serial.println((int)mActivePage);

		return newPage;
	}
	void LCD_Panel_V2::Toggle(stsn::Point aPoint)
	{
		GetActivePage()->HandleTouch(aPoint);
	}

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
		mPage_Iter = &mActivePage;
	};
}