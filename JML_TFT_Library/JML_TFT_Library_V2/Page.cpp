#include "Page.h"

namespace JML_TFT_Library_V2
{
	Page::Page(char* aName, LCD_Panel_V2* aPanel) : mName{ (const __FlashStringHelper*)aName }, mParentLCD{ aPanel }
	{
		mControlCt = 0;
		AddButton(F("Next_Page"), DrawParameters(MAX_Y - mFooterHt - 2, MAX_X / 2 + 5,
			mFooterHt, MAX_X / 2 - 15, WHITE, BLACK), F("Next"), nullptr);
		AddButton("Previous_Page", DrawParameters(MAX_Y - mFooterHt - 2, 10,
			mFooterHt, MAX_X / 2 - 15, WHITE, BLACK), "Previous", nullptr);
		AddTextBox("Title", DrawParameters(MIN_Y + 2, MAX_X / 4, mHeaderHt, MAX_X / 2,
			WHITE, BLACK), aName);
		//mPageControls.reserve(10);
		Serial.print(F("--- New Page "));
		Serial.print(Name());
		Serial.println(F(" Created with:"));
		RollCall();
	}
	Page::Page(const __FlashStringHelper* aName, LCD_Panel_V2* aPanel) : mName{ aName }, mParentLCD{ aPanel }
	{
		mControlCt = 0;
		AddButton(F("Next_Page"), DrawParameters(MAX_Y - mFooterHt - 2, MAX_X / 2 + 5,
			mFooterHt, MAX_X / 2 - 15, WHITE, BLACK), F("Next"), nullptr);
		AddButton(F("Previous_Page"), DrawParameters(MAX_Y - mFooterHt - 2, 10,
			mFooterHt, MAX_X / 2 - 15, WHITE, BLACK), F("Previous"), nullptr);
		AddTextBox(F("Title"), DrawParameters(MIN_Y + 2, MAX_X / 4, mHeaderHt, MAX_X / 2,
			WHITE, BLACK), aName);
		//mPageControls.reserve(10);
		Serial.print(F("--- New Page "));
		Serial.print(Name());
		Serial.println(F(" Created with:"));
		RollCall();
	}
	void Page::AddTextBox(const char* aName, const DrawParameters& aDP, const char* aTxt)
	{
		mControlCt = 0;
		/*		Serial.print(F("\n\nBeginning to Add Text Box '"));
				Serial.print(aName);
				Serial.print(F("' Page currently has '"));
				Serial.print(mPageControls.size());
				Serial.print(F("' controls and '"));
				Serial.print(mPageControls.capacity());
				Serial.println(F("' capacity."));
		*/
		//mPageControls.reserve(1);
		IControlType* ct = new TextBox(aName, aDP, aTxt);
		mPageControls->controls[mControlCt] = ct;

		//mPageControls[mControlCt] = ct;
		//mPageControls.push_back(ct);
		/*		Serial.print(F("Roll Call from 'Page::AddTextBox' after creating '"));
				Serial.print(ct->ToString());
				Serial.println(F("'"));

				Serial.print(F("\tOn '"));
				Serial.print(ToString());
				Serial.print(F("' with '"));
				Serial.print(mPageControls.size());
				Serial.print(F("' CTs and '"));
				Serial.print(mPageControls.capacity());
				Serial.println(F("' capacity."));
				ct->RollCall();

				//Serial.println(F("Now Trying with last element of mPageControls:"));
				//IControlType* tmp = mPageControls.back();
				//tmp->RollCall();
				*/
	}
	void Page::AddTextBox(const __FlashStringHelper* aName, const DrawParameters& aDP, const __FlashStringHelper* aTxt)
	{
		//mPageControls.reserve(1);
		IControlType* ct = new TextBox(aName, aDP, aTxt);
		mPageControls->controls[0] = ct;
		//mPageControls.push_back(ct);
	}

	void Page::AddButton(const char* aName, const DrawParameters& aDP,
		const char* aTxt, EventHandlerFunction aEHF)
	{
		IControlType* ct = new Button(aName, aDP, aTxt, aEHF);
		mPageControls->controls[0] = ct;
		//mPageControls.push_back(ct);
	}
	void Page::AddButton(const __FlashStringHelper* aName, const DrawParameters& aDP,
		const __FlashStringHelper* aTxt, EventHandlerFunction aEHF)
	{
		IControlType* ct = new Button(aName, aDP, aTxt, aEHF);
		mPageControls->controls[0] = ct;
		//* *mPageControls[0] = ct;
	}

	String Page::ToString() const
	{
		String _output = "Page: ";
		_output.concat(Name());
		return _output;
	}

	void Page::RollCall()
	{
		auto sz = mPageControls->sz;
		Serial.print(F("\t"));
		Serial.print(ToString());
		Serial.print(F(" with the following "));
		Serial.print(sz);
		Serial.println(F(" ControlTypes"));
		for (auto ctl : mPageControls->controls)
		{
			ctl->RollCall();
		}
		Serial.print(F("\tFinished "));
		Serial.println(ToString());
	}

	void Page::Refresh() const
	{
		Serial.print(F("\t - Refreshing Page:"));
		Serial.print(ToString());
		Serial.println(F("Past ToString"));
		int ctlNum = 0;
		for (auto& ctl : mPageControls->controls)
		{
			Serial.print((String)(ctlNum++));
			Serial.print(F(" "));
			if (ctl->IsValid())
			{
				ctl->Draw();
			}
			else
			{
				Serial.print(F(" - Invalid Draw\n"));
			}
		}
	}

	void Page::DrawAll() const
	{
		for (auto& ctl : mPageControls->controls)
		{
			if (ctl->IsValid()) { ctl->Draw(); }
		}
	}

	void Page::SetActive() const
	{
		Tft.drawRectangle(0, 0, MAX_X, MAX_Y, BLACK);
		DrawAll();
	}

	void Page::HandleTouch(stsn::Point& aPoint)
	{
		IControlType* TouchedControl = GetByPoint(aPoint);
		// Only true if a Control was found (<>nullPtr)
		if (TouchedControl->GetName() == mPageControls->controls[0]->GetName())
		{
			TouchedControl->Toggle();
		}
	}

	IControlType* Page::GetByPoint(stsn::Point& aPoint)
	{
		//Serial.println("Looking for Point X: " + (String)aPoint->x + ", Y: " + aPoint->y);

		for (auto ctlType : mPageControls->controls)
		{
			if (ctlType->Contains(aPoint))
			{
				return ctlType;
			}
		}
		// Reference can't be null, just send reference to title
		return mPageControls->controls[0];
	}
}