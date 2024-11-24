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
	LCD_Panel_V2* LCD_Panel_V2::GetInstance(IScreen aTFT)
	{
		if (!mInitialized)
		{
			mInstance = new LCD_Panel_V2();// new LCD_Panel_V2();
			mInitialized = true;
		}
		return mInstance;
	}

	Page* LCD_Panel_V2::AddPage(char* aName)
	{
		//**************

		// The problem is here.  THe page looses its name, or never gets it assigned
		// Output name is fine on line 188, but gibberish on line 194.

		// ************
		Serial.print(F("Adding Page:"));
		Serial.println(aName);
		Page* newPage = new Page(aName, this);

		mPages.push_back(newPage);
		mActivePage = newPage;
		mPage_Iter = &mActivePage;
		Serial.print(F(".  newPage address "));
		Serial.println((int)newPage);
		return newPage;
	}
	Page* LCD_Panel_V2::AddPage(const __FlashStringHelper* aName)
	{
		//**************

		// The problem is here.  THe page looses its name, or never gets it assigned
		// Output name is fine on line 188, but gibberish on line 194.

		// ************
		Serial.print(F("Adding Page:"));
		Serial.println(aName);
		Page* newPage = new Page(aName, this);

		mPages.push_back(newPage);
		mActivePage = newPage;
		mPage_Iter = &mActivePage;
		Serial.print(F(".  newPage address "));
		Serial.println((int)newPage);
		return newPage;
	}
	void LCD_Panel_V2::Toggle(stsn::Point aPoint) const
	{
		GetActivePage()->HandleTouch(aPoint);
	}

	bool LCD_Panel_V2::NextPage()
	{
		if (++LCD_Panel_V2::mPage_Iter == LCD_Panel_V2::mPages.end())
		{
			LCD_Panel_V2::mPage_Iter = LCD_Panel_V2::mPages.begin();
		}
		mActivePage = *mPage_Iter;
		return true;
	}
	bool LCD_Panel_V2::LastPage()
	{
		if (--mPage_Iter == mPages.begin())
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
	}
	void LCD_Panel_V2::RollCall() const
	{
		Serial.println(F("LCD Panel Roll Call:"));
		for (auto pg : mPages)
		{
			pg->RollCall();
		}
	}
}