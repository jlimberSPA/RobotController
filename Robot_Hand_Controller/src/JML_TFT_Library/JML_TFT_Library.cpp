/*
 Name:		JML_TFT_Library.cpp
 Created:	3/6/2023 10:12:16 PM
 Author:	jmlma
 Editor:	http://www.visualmicro.com
*/

#include "JML_TFT_Library.h"
#include <math.h>
#include <TFTv2.h>
//#include <typeinfo>
//#include <stdexcept>
//#include <cstring>

namespace JML_TFT_Library
{
	//-----------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------
	/// ///////////////////////////////// CONTROL ////////////////////////////////////////////////////////////////////
	//-----------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------
#pragma region Control

	Control::Control()
	{
	}
	Control::Control(const char* aName, TFT* aScreen, const char* aTxt,
		const unsigned short aTop, const unsigned short aLeft,
		const unsigned short aHeight, const unsigned short aWidth,
		const unsigned short aForeGround, const unsigned short  aBackground) :
		mScreen(aScreen), mName(aName), mTop(aTop), mLeft(aLeft), mHeight(aHeight), mWidth(aWidth),
		mTxt((char*)aTxt), mForeground(aForeGround), mBackground(aBackground)
	{
		UnSelect();

		//	Serial.println("\t 1) Control " + (String)Name() + " was a " + (String)this->ControlTypeToString());
	}
	Control::Control(const char* aName, TFT* aScreen, const char* aTxt,
		const unsigned short aTop, const unsigned short aLeft,
		const unsigned short aHeight, const unsigned short aWidth,
		const unsigned short aForeGround, const unsigned short  aBackground,
		PushOptions aPush) :
		mScreen(aScreen), mName(aName), mTop(aTop), mLeft(aLeft), mHeight(aHeight), mWidth(aWidth),
		mTxt((char*)aTxt), mForeground(aForeGround), mBackground(aBackground), mPush(aPush)

	{
		UnSelect();
		//	Serial.println("\t 1) Control " + (String)Name() + " was a " + (String)this->ControlTypeToString());
	}
	Control::Control(const char* aName, TFT* aScreen, const char* aTxt,
		const unsigned short aTop, const unsigned short aLeft,
		const unsigned short aHeight, const unsigned short aWidth,
		const unsigned short aForeGround, const unsigned short  aBackground,
		PushOptions aPush, EventHandlerFunction aEHF) :
		mScreen(aScreen), mName(aName), mTop(aTop), mLeft(aLeft), mHeight(aHeight), mWidth(aWidth),
		mTxt((char*)aTxt), mForeground(aForeGround), mBackground(aBackground), mPush(aPush), OnClickEventHandler(aEHF)
	{
		UnSelect();
		mHasEHF = true;
		//Serial.println("\t** Control " + (String)Name() + " was a button with EHF");
	//	Serial.println("\t 1) Control " + (String)Name() + " was a " + (String)this->ControlTypeToString());
	}
	Control::~Control()
	{
	}

	void Control::SetName(char* aName)
	{
		mName = aName;
	}
	void Control::SetPos(unsigned short  aTop, unsigned short  aLeft)
	{
		mTop = aTop;
		mLeft = aLeft;
	}
	void Control::SetSize(unsigned short  aHeight, unsigned short  aWidth)
	{
		mHeight = aHeight;
		mWidth = aWidth;
	}
	void Control::SetText(char* aTxt)
	{
		mTxt = aTxt;
		//Serial.print("Setting ");
		//Serial.print(mName);
		//Serial.print(" text to ");
		//Serial.print(aTxt);
		//Serial.print(".  Length: ");
		//Serial.println(((String)aTxt).length());
	}

	void Control::SetColor(unsigned short  aForeground, unsigned short  aBackground)
	{
		mForeground = aForeground;
		mBackground = aBackground;
	}

	/* COORDINATES ON PANEL

		(0,0) x ->			119		Max X (239,0)
	y	-----------------------------------------
	|	|										|
	v	|										|
		|				TOP						|
		|		.................				|
		| LEFT	:				: RIGHT			|
		|		:				:				|
		|		.................				|
		|			  BOTTOM					|
		|										|
		|										|
		|										|
	159	|										|
		|										|
		|										|
		|										|
		|										|
		|										|
		|										|
		|										|
		|										|
		|										|
		|										|
		-----------------------------------------
		(0,319) Max Y					(239,319)

	*/
	int Control::Left() const
	{
		return mLeft;
	}
	int Control::Top() const
	{
		return mTop;
	}
	int Control::Width() const
	{
		return mWidth;
	}
	int Control::Height() const
	{
		return mHeight;
	}
	int Control::Right() const
	{
		return mLeft + mWidth;
	}
	int Control::Bottom() const
	{
		return mTop + mHeight;
	}
	char* Control::Text() const
	{
		return mTxt;
	}
	const char* Control::Name() const
	{
		return mName;
	}

	const bool Control::IsValid() const
	{
		bool validX = (mLeft > 0) && (mLeft <= 240);
		bool validY = (mTop > 0) && (mTop <= 320);
		bool validName = (strlen(mName) > 0);
		bool allValid = validName && validX && validY;
		if (!allValid)
		{
#ifdef DEBUG
			Serial.println(" ** Invalid Button" + ToString());
#endif // DEBUG
		}
		//Serial.print("Button: " + Name());
		//Serial.print("\t Text: " + (String)Text());
		//Serial.print("\t Top, Left: (" + (String)Top() + ", " + Left() + "");
		//Serial.print("\t Bottom, Right: (" + (String)Bottom() + ", " + Right() + "");
		//Serial.print("\t Width, Height: (" + (String)Width() + ", " + Height() + "");
		//Serial.println("\t Has Callback: " + (String)mHasEHF + " IsValid: " + allValid);

		return allValid;
	}
	String Control::ToString() const
	{
		String result;
		result += ControlTypeToString() + (String)": " + Name();
		result += "\t Text: " + (String)Text();
		result += "\t Left, Top: (" + (String)Left() + ", " + Top() + ")";
		result += "\t Right, Bottom: (" + (String)Right() + ", " + Bottom() + ")";
		result += "\t Width, Height: (" + (String)Width() + ", " + Height() + ")";
		return result;
	}

	void Control::Draw() const
	{
		if (IsValid())
		{
			Tft.fillRectangle(Left(), Top(), Width(), Height(), mBackground);
			Tft.drawString(mTxt,
				(unsigned short)(Left() + 2),
				(unsigned short)(Top() + 4),
				(unsigned short)2,
				mForeground, PORTRAIT);
			//Serial.println(mName + "/" + mTxt + (String)".  L,B: (" + Left() + (String)"," + Bottom() + (String)") R,T: (" + Right() + (String)"," + Top() + (String)")");
			if (mSelected)
			{
				//				Serial.println("Drawing Border for " + (String)mTxt + " State: " + mSelected);
				Tft.drawRectangle(Left(), Top(), Width(), Height(), YELLOW);
				Tft.drawRectangle(Left() + 2, Top() + 2, Width() - 4, Height() - 4, YELLOW);
			}
			else
			{
				//				Serial.println("Not Drawing Border " + (String)mTxt + " Selected State: " + mSelected);
			}
		}
	}

	void Control::Flash()
	{
	}

	void Control::Select()
	{
		mSelected = true;
		SetName("Selected");
#ifdef DEBUG
		//	Serial.println("\t** Control Select set '" + (String)Name() + "/" + (String)Text() + "' selection status: " + mSelected);

#endif // DEBUG
	}

	void Control::UnSelect()
	{
		mSelected = false;
#ifdef DEBUG
		//	Serial.println("\t** Control UnSelect set '" + (String)Name() + "/" + (String)Text() + "' selection status: " + mSelected);
#endif // DEBUG

		//Serial.print(mName.length()); Serial.print("/"); Serial.println(((String)mTxt).length());
	}

	void Control::Toggle()
	{
		mSelected = !mSelected;
#ifdef DEBUG
		//	Serial.println("\nButton Toggle set '" + (String)Name() + "/" + (String)Text() + "' to " + mSelected);
#endif // DEBUG

		if (mHasEHF) {
			OnClickEventHandler();
			//	Serial.println("\t - Calling EHF for " + (String)Name());
		}
	}

	bool Control::Contains(SeeedPt aPoint) const
	{
		if (IsValid())
		{
			//Serial.print("Checking if point (" + (String)aPoint.x + ", " + (String)aPoint.y + ") is inside box. ");
			//"Left/Right: " + Left() + " <-> " + Right());

			if (aPoint.x >= std::min(Left(), Right()) && aPoint.x <= std::max(Left(), Right()))
			{
				//Serial.println("  -- Yes, inside L/R Checking if point.y (" + (String)aPoint.y + ") is inside box. Bottom/Top: " + Bottom() + " <-> " + Top());

				if (aPoint.y >= std::min(Bottom(), Top()) && aPoint.y <= std::max(Bottom(), Top()))
				{
					//Serial.println(" -- Yes, inside Box.");

					return true;
				}
				else
				{
					//Serial.println(" -- No, NOT inside B/T.");
				}
			}
			else
			{
				//Serial.println("  -- No, NOT inside L/R.  Not testing B/T.");
			}
		}
		return false;
	}
#pragma endregion

	//-----------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------
	/// 	///////////////////////////////// TEXT Box ////////////////////////////////////////////////////////////////////
	//-----------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------
#pragma region TextBox

	TextBox::TextBox()
	{
	}

	TextBox::TextBox(TFT* aScreen, const char* aName, const char* aTxt,
		const unsigned short aTop, const unsigned short aLeft,
		const unsigned short aHeight, const unsigned short aWidth,
		const unsigned short aForeGround, const unsigned short  aBackground) :
		Control(aScreen, aName, aTxt, aTop, aLeft, aHeight, aWidth, aForeGround, aBackground)
	{
		//	Serial.println("\t 2) Control " + (String)Name() + " was a " + (String)this->ControlTypeToString());
	}

	TextBox::~TextBox()
	{
	}

	char* TextBox::GetText()
	{
		return mVal; //strcat(mCaption, mVal);
	}

	void TextBox::Draw()
	{
		if (IsValid())
		{
			Tft.fillRectangle(Left(), Top(), Width(), Height(), mBackground);
			Tft.drawString(GetText(),
				(unsigned short)(Left() + 2),
				(unsigned short)(Top() + 4),
				(unsigned short)2,
				mForeground, PORTRAIT);
			//Serial.println(mName + "/" + mTxt + (String)".  L,B: (" + Left() + (String)"," + Bottom() + (String)") R,T: (" + Right() + (String)"," + Top() + (String)")");
			if (mSelected)
			{
				//				Serial.println("Drawing Border for " + (String)mTxt + " State: " + mSelected);
				Tft.drawRectangle(Left(), Top(), Width(), Height(), YELLOW);
				Tft.drawRectangle(Left() + 2, Top() + 2, Width() - 4, Height() - 4, YELLOW);
			}
			else
			{
				//				Serial.println("Not Drawing Border " + (String)mTxt + " Selected State: " + mSelected);
			}
		}
	}
	void TextBox::SetCaption(char* aCaption)
	{
		mCaption = aCaption;
	}

	void TextBox::SetValue(char* aVal)
	{
		mVal = aVal;

		// Change the displayed text of this Text Box
		//String Temp = mCaption + (String)"";
		//mTxt = (char*)Temp.concat(mVal);
	}

	String TextBox::ToString()
	{
		String result;
		result += "\n" + (String)ControlTypeToString() + " Control Name: " + Name();
		result += "\n\t Text: " + (String)Text();
		result += "\n\t Left, Top: (" + (String)Left() + ", " + Top() + ")";
		result += "\t Right, Bottom: (" + (String)Right() + ", " + Bottom() + ")";
		result += "\t Width, Height: (" + (String)Width() + ", " + Height() + ")";
		result += "\n\t Caption: " + (String)mCaption + ", Value: " + mVal;
		return result;
	}

#pragma endregion

	//-----------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------
	///////////////////////////////// TEXT PANEL ////////////////////////////////////////////////////////////////////
	//-----------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------
#pragma region TextPanel

	TextPanel::TextPanel()
	{
		for (size_t i = 0; i < mMaxLines; i++)
		{
			mRows[i] = "";
		}
		//	Serial.println("Control " + (String)Name() + " was a text panel");
	}

	TextPanel::TextPanel(TFT* aScreen, const char* aName, const char* aTxt,
		const unsigned short aTop, const unsigned short aLeft,
		const unsigned short aLines, const unsigned short aWidth,
		const unsigned short aForeGround, const unsigned short  aBackground) :
		Control(aScreen, aName, aTxt, aTop, aLeft, std::min(mMaxLines, aLines)* mLineHeight, aWidth, aForeGround, aBackground)
	{
		TextPanel();
		//	Serial.println("\t 2) Control " + (String)Name() + " (TextPanel) was a " + (String)this->ControlTypeToString());
	}

	TextPanel::~TextPanel()
	{
	}

	void TextPanel::writeln(String aStr)
	{
		for (size_t i = mMaxLines - 1; i > 0; i--)
		{
			mRows[i] = mRows[i - 1];
		}
		mRows[0] = aStr;
	}

	void TextPanel::Draw()
	{
		if (IsValid())
		{
			Tft.fillRectangle(Left(), Top(), Width(), Height(), mBackground);
			for (size_t i = 0; i < mMaxLines; i++)
			{
				Tft.drawString((char*)(mRows[i].c_str()),
					(unsigned short)(Left() + 2),
					(unsigned short)(Top() + 4 + (mMaxLines - i - 1) * mLineHeight),
					(unsigned short)1,
					mForeground, PORTRAIT);
			}

			if (mSelected)
			{
				//				Serial.println("Drawing Border for " + (String)mTxt + " State: " + mSelected);
				Tft.drawRectangle(Left(), Top(), Width(), Height(), YELLOW);
				Tft.drawRectangle(Left() + 2, Top() + 2, Width() - 4, Height() - 4, YELLOW);
			}
			else
			{
				//				Serial.println("Not Drawing Border " + (String)mTxt + " Selected State: " + mSelected);
			}
		}
	}
#pragma endregion

	//-----------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------//////////////////////////////// BUTTON /////////////////////////////////////////////////////////////////////
	//////////////////////////////// BUTTON /////////////////////////////////////////////////////////////////////
	//-----------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------
#pragma region Button

	Button::Button()
	{
	}

	Button::Button(const char* aTxt,
		const unsigned short aTop, const unsigned short aLeft,
		const unsigned short aHeight, const unsigned short aWidth,
		const unsigned short aForeGround, const unsigned short  aBackground,
		PushOptions aPush) :
		Control(aTxt, aTop, aLeft, aHeight, aWidth, aForeGround, aBackground, aPush)
	{
#ifdef DEBUG
		//	Serial.println("\t** Control " + (String)Name() + " was a button");

#endif // DEBUG
	//	Serial.println("\t 2) Control " + (String)Name() + " (Button) was a " + (String)this->ControlTypeToString());
}

	Button::Button(const char* aTxt,
		const unsigned short aTop, const unsigned short aLeft,
		const unsigned short aHeight, const unsigned short aWidth,
		const unsigned short aForeGround, const unsigned short  aBackground,
		PushOptions aPush,
		EventHandlerFunction aEHF) : Control(aTxt, aTop, aLeft, aHeight, aWidth, aForeGround, aBackground, aPush, aEHF)
	{
		//Button;
	//	Serial.println("\t 2) Control " + (String)Name() + " (Button w/ EHF) was a " + (String)this->ControlTypeToString());
	}

	Button::~Button()
	{
	}

	void Button::Toggle()
	{
		//	Serial.println("Calling Button Toggle");
	}

	String Button::ToString()
	{
		String result;
		result += "Button: " + (String)Name();
		result += "\t Text: " + (String)Text();
		result += "\t Left, Top: (" + (String)Left() + ", " + Top() + "";
		result += "\t Right, Bottom: (" + (String)Right() + ", " + Bottom() + "";
		result += "\t Width, Height: (" + (String)Width() + ", " + Height() + "";
		result += "\t Has Callback: " + mHasEHF;
		return result;
	}

	void Button::OnPushed()
	{
		switch (mPush)
		{
		none:
			break;
		Select:
			Select();
			break;
		UnSelect:
			UnSelect();
			break;
		Toggle:
			Toggle();
			break;

		default:
			break;
		}
	}

#pragma endregion

	//-----------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------
	///////////////////////////////// JOYSTICK DISPLAY CONTROL ////////////////////////////////////////////////////////////////////
	//-----------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------
#pragma region Button
	JoystickDisplayControl::JoystickDisplayControl()
	{
	}

	JoystickDisplayControl::JoystickDisplayControl(TFT* aScreen, const char* aName, const char* aTxt,
		const unsigned short aTop, const unsigned short aLeft,
		const unsigned short aForeGround, const unsigned short  aBackground)
		: Control(aScreen, aName, aTxt, aTop + 30, aLeft, mSize, mSize,
			aForeGround, aBackground)
	{
#ifdef DEBUG
		//	Serial.println("\t** Control " + (String)Name() + " was a JDC");
#endif
	//	Serial.println("\t 2) Control " + (String)Name() + " (JSD) was a " + (String)this->ControlTypeToString());
		mJoystick_X = TextBox(aScreen, "X: ", "X: ", aTop, 20, 30, 100, WHITE, MIDNIGHT_BLUE);
		mJoystick_Y = TextBox(aScreen, "Y: ", "Y: ", aTop, 130, 30, 100, WHITE, MAROON);
		xLbl = mJoystick_X.Name();
		yLbl = mJoystick_Y.Name();
	}

	void JoystickDisplayControl::Update(uint16_t aJSx, uint16_t aJSy)
	{
		mJSx = 20;
		mJSy = 800;
		char* _JSx = "20";
		char* _JSy = "800";
		mJoystick_X.SetValue(_JSx);
		mJoystick_Y.SetValue(_JSy);
		//Serial.println((String)mJSx + (String)" Update " + (String)mJSy);
	}

	void JoystickDisplayControl::Draw()
	{
		Control::Draw(); // Draw the background Square

		mJoystick_X.Draw();
		mJoystick_Y.Draw();
		GetCenter();	// Ensure center point is current
		//Serial.println("\n" + (String)mJSx + (String)" // " + (String)mJSy);
		int16_t JSx = map(mJSx, 0, 1000, 0, mSize);
		int16_t JSy = map(mJSy, 0, 1000, 0, mSize);
#ifdef DEBUG

		//	Serial.println((String)mJSx + (String)"/" + (String)mJSy + (String)"/" + (String)JSx + (String)"/" + (String)JSy);
		//	Serial.println(mJoystick_X.ToString());

#endif // DEBUG
		Tft.drawLine(ctlCtrX, ctlCtrY, ctlCtrX + JSx - mSize / 2, ctlCtrY + JSy - mSize / 2, mForeground);
	}
	void JoystickDisplayControl::GetCenter()
	{
		ctlCtrX = Left() + Width() / 2;
		ctlCtrY = Top() + Height() / 2;
	}
#pragma endregion Button

	//-----------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------
	///////////////////////////////// Page ////////////////////////////////////////////////////////////////////
	//-----------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------

	Page::Page() : mName((char*)"Default" + LCD_Panel_V2::_pageCount)
	{
	}
	Page::Page(TFT* aScreen, const char* aName, EventHandlerFunction aLastPgFunc, EventHandlerFunction aNextPgFunc)
	{
		mScreen = aScreen;
		aName = strcat((char*)aName, (const char*)LCD_Panel_V2::_pageCount);
		mName = (char*)aName;

		//mTitle =
		AddTextBox(aName, (char*)aName, MIN_Y + 2, MAX_X / 4, mHeaderHt, MAX_X / 2, WHITE, BLACK);

		//mLastPg =
		AddButton((char*)"PreviousPage", (char*)"Previous Page", MAX_Y - mFooterHt - 2, 10, mFooterHt, MAX_X / 2 - 15,
			WHITE, BLACK, PushOptions::select, aLastPgFunc);

		//mNextPg =
		AddButton((char*)"NextPage", (char*)"Next Page", MAX_Y - mFooterHt - 2, MAX_X / 2 + 5, mFooterHt, MAX_X / 2 - 15,
			WHITE, BLACK, PushOptions::select, aNextPgFunc);

#ifdef DEBUG
		//	Serial.println("\t* Created new page '" + (String)aName + "' Starting with : " + (String)mControls.size() + " controls.");
#endif
	}
	Page::~Page()
	{
	}

	void Page::AddButton(const char* aName, const char* aTxt,
		const unsigned short aTop, const unsigned short aLeft,
		const unsigned short aHeight, const unsigned short aWidth,
		const unsigned short aForeGround, const unsigned short  aBackground,
		PushOptions aPush)
	{
#ifdef DEBUG
		//	Serial.println("\t* About to add button to: " + this->mName);

#endif // DEBUG
		Button* btn = &Button(
			mScreen, aName, aTxt,
			aTop, aLeft,
			aHeight, aWidth,
			aForeGround, aBackground,
			aPush);
		mControls.push_back(*btn);
		mControls_ptrs.push_back(btn);
		//btn.Draw();

#ifdef DEBUG
	//	Serial.print("\t* Created new button " + (String)aName + " - ");
	//	Serial.print("'" + (String)btn.Name() + "'");
	//	Serial.print(mName);
	//	Serial.println("\t  it now has " + (String)mControls.size() + " controls.\n");

#endif // DEBUG
		//return btn;
	}
	void Page::AddButton(const char* aName, const char* aTxt,
		const unsigned short aTop, const unsigned short aLeft,
		const unsigned short aHeight, const unsigned short aWidth,
		const unsigned short aForeGround, const unsigned short  aBackground,
		PushOptions aPush,
		EventHandlerFunction aEvt)
	{
		Button* btn = &Button(
			mScreen, aName, aTxt,
			aTop, aLeft,
			aHeight, aWidth,
			aForeGround, aBackground,
			aPush, aEvt);
		mControls.push_back(*btn);
		mControls_ptrs.push_back(btn);
		//		btn.Draw();
	//	Serial.println("\t 3) Created new button '" + (String)aName); // +"' on " + mName + " it now has " + (String)mControls.size() + " controls.\n");
		//return btn;
	}

	void Page::AddJoystickDisplay(const char* aName, const char* aTxt,
		const unsigned short aTop, const unsigned short aLeft,
		const unsigned short aForeGround, const unsigned short  aBackground)
	{
		JoystickDisplayControl* jsd = &JoystickDisplayControl(
			mScreen, aName, aTxt,
			aTop, aLeft,
			aForeGround, aBackground);

		mControls.push_back(*jsd);
		mControls_ptrs.push_back(jsd);
#ifdef DEBUG
		//	Serial.println("\t* Created new jsd '" + (String)aName + "' on " + mName + " it now has " + (String)mControls.size() + " controls.\n");
#endif // DEBUG

		//return jsd;
	}

	void Page::AddTextBox(const char* aName, const char* aTxt,
		const unsigned short aTop, const unsigned short aLeft,
		const unsigned short aHeight, const unsigned short aWidth,
		const unsigned short aForeGround, const unsigned short  aBackground)
	{
		TextBox* tb = &TextBox(
			mScreen, aName, aTxt,
			aTop, aLeft,
			aHeight, aWidth,
			aForeGround, aBackground);
		mControls.push_back(*tb);
		mControls_ptrs.push_back(tb);
		//		tb.Draw();
#ifdef DEBUG
		Serial.println("\t* Created new tb '" + (String)aName + "' on " + mName + " it now has " + (String)mControls.size() + " controls.\n")
#endif // DEBUG
			;

		//return tb;
	}

	void Page::AddTextPanel(const char* aName, const char* aTxt,
		const unsigned short aTop, const unsigned short aLeft,
		const unsigned short aHeight, const unsigned short aWidth,
		const unsigned short aForeGround, const unsigned short  aBackground)
	{
		TextPanel* tp = &TextPanel(
			mScreen, aName, aTxt,
			aTop, aLeft,
			aHeight, aWidth,
			aForeGround, aBackground);
		mControls.push_back(*tp);
		mControls_ptrs.push_back(tp);
		//		tp.Draw();
#ifdef DEBUG
	//	Serial.println("\t* Created new tp '" + (String)aName + "' on " + mName + " it now has " + (String)mControls.size() + " controls.\n");
#endif // DEBUG

		//return tp;
	}

	int Page::NumControls()
	{
		return mControls.size();
	}

	Control* Page::GetControl(uint8_t aIdx)
	{
		return &mControls[aIdx];
	}
	Control* Page::GetControl(char* aName)
	{
		for (int ctl_idx = 0; ctl_idx < mControls.size(); ctl_idx += 1)
		{
			if (mControls[ctl_idx].Name() == aName)
			{
				return &mControls[ctl_idx];
			}
		}
	}
	String Page::ToString()
	{
		String _output = "Page: " + (String)mName + " All Controls:";
		for (int i = 0; i < mControls.size(); i++)
		{
			_output += "\n";
			_output += mControls[i].ToString();
		}
		_output += "\n";

		_output += "Page: " + (String)mName + " All Control Pointers: ";
		for (auto* ctl : mControls_ptrs) //int i = 0; i < mControls_ptrs.size(); i++)
		{
			_output += "\n";
			_output += "a control pointer"; // *ctl->Name();//mControls_ptrs[i]->ToString();
		}
		_output += "\n";

		_output += "      " + (String)mName + " Auto Refresh Controls:";
		for (int i = 0; i < mRefreshList.size(); i++)
		{
			_output += "\n";
			_output += mRefreshList[i]->ToString();
		}
		_output += "\n";

		return _output;
	}

	void Page::AddToAutoRefreshList(char* aName)
	{
		Control* aCtl = GetControl(aName);
		mRefreshList.push_back(aCtl);
	}

	void Page::AddToAutoRefreshList(Control* aCtl)
	{
		mRefreshList.push_back(aCtl);
	}

	void Page::Refresh()
	{
		/*Serial.println("\t- Refreshing Page: " + (String)Name()
			+ ". Has " + mControls.size() + " controls, "
			+ " and " + mRefreshList.size() + " refreshable controls.");*/
		for (int ctl = 0; ctl < mRefreshList.size(); ctl++)
		{
			//Serial.print("\t\t -- Refreshable Control #" + (String)ctl
			//	+ " named ");
			//Serial.println(" -- Button: " + (String)b + " - " + mControls[b].Text());
			if (mRefreshList[ctl]->IsValid())
			{
				//Serial.println("\t - Refreshing Control " + (String)mRefreshList[ctl]->Name()
				//	+ " Control Type " + mRefreshList[ctl]->ControlTypeToString());
				//Serial.println(mRefreshList[ctl]->Name());
				mRefreshList[ctl]->Draw();
			}
			else
			{
				//Serial.println(" - InValid - No Draw ");
			}
		}
	}

	void Page::DrawAll()
	{
		for (int ctl = 0; ctl < mControls.size(); ctl++)
		{
			//Serial.println(" -- Button: " + (String)b + " - " + mControls[b].Text());
			if (mControls[ctl].IsValid())
			{
				//	Serial.println("\t - Drawing Control " + (String)mControls[ctl].Name()
				//		+ " Control Type " + mControls[ctl].ControlTypeToString());
					//Serial.println(" - Valid - Called Draw");
				mControls[ctl].Draw();
			}
			else
			{
				//Serial.println(" - InValid - No Draw " + mControls[b].ToString());
			}
		}
	}

	void Page::SetActive()
	{
		//Tft.drawRectangle(0, 0, MAX_X, MAX_Y, BLACK);
		DrawAll();
	}

	void Page::Toggle(SeeedTouchScreenNamespace::Point aPoint)
	{
		//	Serial.println(ToString());

		Control* selectedControl = GetByPoint(aPoint);

		Control* aCtl = GetControl((char*)selectedControl->Name());
		//	Serial.println("\t - Found Control " + (String)aCtl->Name()
		//		+ " Control Type " + aCtl->ControlTypeToString());
		//		aCtl->Toggle();
	}
	void Page::Select(SeeedTouchScreenNamespace::Point aPoint)
	{
		//	Serial.println(ToString());

		Control* selectedControl = GetByPoint(aPoint);

		Control* aCtl = GetControl((char*)selectedControl->Name());
		//	Serial.println("\t - Found Control " + (String)aCtl->Name()
		//		+ " Control Type " + aCtl->ControlTypeToString());
		//		aCtl->Toggle();
	}
	void Page::Push(SeeedTouchScreenNamespace::Point aPoint)
	{
		//	Serial.println(ToString());

		Control* selectedControl = GetByPoint(aPoint);

		Control* aCtl = GetControl((char*)selectedControl->Name());
		//	Serial.println("\t - Found Control " + (String)aCtl->Name()
		//		+ " Control Type " + aCtl->ControlTypeToString());
		//		aCtl->Toggle();
	}

	Control* Page::GetByPoint(SeeedTouchScreenNamespace::Point aPoint)
	{
		//Serial.println("Looking for Point X: " + (String)aPoint.x + ", Y: " + aPoint.y);
		Control* btn;
		for (int b = 0; b < NumControls(); b++)
		{
			//Serial.println("Checking Button Lower Left: X: "
			//	+ (String)mActivePage->GetControl(b)->Left()
			//	+ ", Y: " + (String)mActivePage->GetControl(b)->Bottom()
			//	+ ".  Upper Right: X: " + (String)mActivePage->GetControl(b)->Right()
			//	+ ", Y: " + (String)mActivePage->GetControl(b)->Top());

			if (GetControl(b)->Contains(aPoint))
			{
				//	Serial.println(" --- Match: Control '" + (String)(GetControl(b)->Name()) + "'");
				btn = GetControl(b);
				return btn;
			}
			else
			{
				//Serial.println(" --- No Match");
			}
		}
		//Serial.println();
		btn = nullptr;
		return btn;
	}

	//-----------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------
	///////////////////////////////// LCD_Panel_V2 ////////////////////////////////////////////////////////////////////
	//-----------------------------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------------------------

	int LCD_Panel_V2::_pageCount = 0;
	std::vector<Page> LCD_Panel_V2::mPages = std::vector<Page>();

	LCD_Panel_V2::LCD_Panel_V2()
	{
#ifdef DEBUG
		//	Serial.println("\n[Creating New LCD Panel]");
#endif // DEBUG
		myScreen = &TFT();
		//myScreen->TFTinit();
	}

	LCD_Panel_V2::~LCD_Panel_V2()
	{
	}
	Page LCD_Panel_V2::GetPage(int idx)
	{
		return mPages.at(idx);
	}
	Page* LCD_Panel_V2::GetActivePage()
	{
		return mActivePage;
	}
	Page* LCD_Panel_V2::AddPage(char* aName)
	{
		//	Serial.println("\t *LCD Panel has [" + PageCount() + "] pages.  Adding new page '" + aName + "'");
		Page* newPage = &Page(myScreen, aName, lastPG_EHF, nextPg_EHF);
		//	Serial.println("\t** Confirming new page is named " + (String)newPage->Name());
		//  LCD_Panel_V2::mActivePage = &newPage;
		LCD_Panel_V2::mPages.push_back(*newPage);
		LCD_Panel_V2::_pageCount++;
		//	Serial.println("\t*LCD Panel now has[" + PageCount() + "] pages.\n");
		return newPage;
	}

	String LCD_Panel_V2::PageCount()
	{
		String out = (String)LCD_Panel_V2::mPages.size() + " Pages: ";
		for (int pg = 0; pg < LCD_Panel_V2::mPages.size(); pg++)
		{
			out += mPages.at(pg).Name() + (String)"(" + mPages.at(pg).NumControls() + ")";
		}
		return out;
	}

	String LCD_Panel_V2::ToString()
	{
		String _output = "* LCD Panel Contents: ";
		_output += "\t " + LCD_Panel_V2::mPages.size() + (String)" Pages, with pagecount: " + (String)LCD_Panel_V2::_pageCount + "\n";
		for (int i = 0; i < LCD_Panel_V2::mPages.size(); i++)
		{
			_output += "\n\t* Page# " + (String)i + "\n";
			_output += LCD_Panel_V2::mPages[i].ToString();
		}
		_output += "\n\n";
		return _output;
	}

	void LCD_Panel_V2::SetActivePage(Page* aPage)
	{
		delay(2000);
		Serial.println("About to Set Active");
		Serial.println(aPage->Name());
		if (aPage != nullptr)
		{
			mActivePage = aPage;
			mActivePage->SetActive();
		}
	}

	void LCD_Panel_V2::Select(SeeedTouchScreenNamespace::Point aPoint)
	{
		GetActivePage()->Select(aPoint);
		//Control* btn = GetByPoint(aPoint);
		//if (btn != nullptr && btn->IsValid()) { btn->Select(); }
		//ReDraw();
	}

	void LCD_Panel_V2::Toggle(SeeedTouchScreenNamespace::Point aPoint)
	{
		GetActivePage()->Toggle(aPoint);
	}
	void LCD_Panel_V2::Push(SeeedTouchScreenNamespace::Point aPoint)
	{
		GetActivePage()->Push(aPoint);
		//Button* btn = static_cast<Button*>(GetByPoint(aPoint));
		//if (btn != nullptr && btn->IsValid()) { btn->OnPushed(); }
		//ReDraw();
	}

	bool LCD_Panel_V2::NextPage()
	{
		mPage_Iter++;
		if (LCD_Panel_V2::mPage_Iter == LCD_Panel_V2::mPages.end())
		{
			LCD_Panel_V2::mPage_Iter = LCD_Panel_V2::mPages.begin();
		}
		mActivePage = LCD_Panel_V2::mPage_Iter;
		return true;
	}

	bool LCD_Panel_V2::LastPage()
	{
		LCD_Panel_V2::mPage_Iter--;
		if (LCD_Panel_V2::mPage_Iter == LCD_Panel_V2::mPages.begin())
		{
			LCD_Panel_V2::mPage_Iter = LCD_Panel_V2::mPages.end();
		}
		LCD_Panel_V2::mActivePage = LCD_Panel_V2::mPage_Iter;
		return true;
	}

	void LCD_Panel_V2::Select(char* aName)
	{
		Control* btn = GetByName(aName);
		if (btn != nullptr && btn->IsValid()) { btn->Select(); }
		ReDraw();
	}
	void LCD_Panel_V2::Toggle(char* aName)
	{
		Control* btn = GetByName(aName);
		if (btn != nullptr && btn->IsValid()) { btn->Toggle(); }
		ReDraw();
	}

	void LCD_Panel_V2::ReDraw()
	{
		//Serial.println("ReDrawing Buttons:");
		GetActivePage()->Refresh();
	}

	SeeedTouchScreenNamespace::TouchScreen* LCD_Panel_V2::myTouchPanel()
	{
		return &mTouch;
	}

	Control* LCD_Panel_V2::GetByName(char* aName)
	{
		Control* btn;
		for (int b = 0; b < LCD_Panel_V2::mActivePage->NumControls(); b++)
		{
			if (LCD_Panel_V2::mActivePage->GetControl(b)->Name() == aName)
			{
				btn = LCD_Panel_V2::mActivePage->GetControl(b);
				return btn;
			}
		}
		btn = nullptr;
		return btn;
	}

	//Control* LCD_Panel_V2::GetByPoint(SeeedTouchScreen::Point aPoint)
	//{
	//	//Serial.println("Looking for Point X: " + (String)aPoint.x + ", Y: " + aPoint.y);
	//	Control* btn;
	//	for (int b = 0; b < LCD_Panel_V2::mActivePage->NumControls(); b++)
	//	{
	//		//Serial.println("Checking Button Lower Left: X: "
	//		//	+ (String)mActivePage->GetControl(b)->Left()
	//		//	+ ", Y: " + (String)mActivePage->GetControl(b)->Bottom()
	//		//	+ ".  Upper Right: X: " + (String)mActivePage->GetControl(b)->Right()
	//		//	+ ", Y: " + (String)mActivePage->GetControl(b)->Top());

	//		if (LCD_Panel_V2::mActivePage->GetControl(b)->Contains(aPoint))
	//		{
	//			Serial.println (" --- Match: Control '" + (String)(mActivePage->GetControl(b)->Name()) + "'");
	//			btn = LCD_Panel_V2::mActivePage->GetControl(b);
	//			return btn;
	//		}
	//		else
	//		{
	//			//Serial.println(" --- No Match");
	//		}
	//	}
	//	//Serial.println();
	//	btn = nullptr;
	//	return btn;
	//}
}