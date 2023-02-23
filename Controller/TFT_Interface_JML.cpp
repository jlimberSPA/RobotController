// 
// 
// 

#include "TFT_Interface_JML.h"

namespace TFT_Interface_JML
{
#pragma region Button

#pragma region Button_constructors
	Button::Button()
	{
	}

	Button::Button(String aName,
		unsigned short  aTop, unsigned short  aLeft,
		unsigned short  aHeight, unsigned short  aWidth,
		char* aTxt,
		unsigned short  aForeGround, unsigned short  aBackground)
	{
		//Button(aTS);
		SetName(aName);
		SetPos(aTop, aLeft);
		SetSize(aHeight, aWidth);
		SetText(aTxt);
		SetColor(aForeGround, aBackground);
	}

	Button::~Button()
	{
	}
#pragma endregion

#pragma region Button_Methods

	void Button::Draw()
	{
		if (IsValid())
		{
			TFT().fillRectangle(Left(), Bottom(), Width(), Height(), mBackground);
			TFT().drawString(mTxt,
				(unsigned short)(Left() + 2),
				(unsigned short)(Bottom() + 4),
				(unsigned short)2,
				mForeground, PORTRAIT);
			if (mSelected)
			{
				TFT().drawRectangle(Left(), Bottom(), Width(), Height(), YELLOW);
				TFT().drawRectangle(Left() + 2, Bottom() + 2, Width() - 4, Height() - 4, YELLOW);
			}
			else
			{

			}
		}
	}

	void Button::Flash()
	{
	}

	void Button::Select()
	{
		mSelected = true;
		Draw();
	}

	void Button::UnSelect()
	{
		mSelected = false;
		Draw();
	}

	void Button::Toggle()
	{
		mSelected != mSelected;
		Draw();
	}
#pragma endregion

#pragma region Button_Property_Setters
	void Button::SetName(String aName)
	{
		mName = aName;
	}
	void Button::SetPos(unsigned short  aTop, unsigned short  aLeft)
	{
		mTop = aTop;
		mLeft = aLeft;
	}

	void Button::SetSize(unsigned short  aHeight, unsigned short  aWidth)
	{
		mHeight = aHeight;
		mWidth = aWidth;
	}

	void Button::SetText(char* aTxt)
	{
		mTxt = aTxt;
	}

	void Button::SetColor(unsigned short  aForeground, unsigned short  aBackground)
	{
		mForeground = aForeground;
		mBackground = aBackground;
	}
#pragma endregion

#pragma region Button_Property_Getters

	int Button::Left()
	{
		return mLeft;
	}
	int Button::Top()
	{
		return mTop;
	}
	int Button::Width()
	{
		return mWidth;
	}
	int Button::Height()
	{
		return mHeight;
	}
	int Button::Right()
	{
		return mLeft + mWidth;
	}
	int Button::Bottom()
	{
		return mTop - mHeight;
	}


	bool Button::IsValid()
	{
		bool validX = (mLeft > 0) && (mLeft <= 320);
		bool validY = (mTop > 0) && (mTop <= 240);
		bool validName = (mName.length() > 0);
		return validName && validX && validY;
	}

	bool Button::Contains(Point aPoint)
	{
		if (IsValid())
		{
			Serial.print("Checking if point.x (");
			Serial.print(aPoint.x);
			Serial.print(") is inside box. Left/Right: ");
			Serial.print(Left());
			Serial.print(" <-> ");
			Serial.println(Right());

			if (aPoint.x >= Left() && aPoint.x <= Right())
			{
				Serial.println(". Inside L/R");
				Serial.print("Checking if point.y (");
				Serial.print(aPoint.y);
				Serial.print(") is inside box. Bottom/Top: ");
				Serial.print(Bottom());
				Serial.print(" <-> ");
				Serial.print(Top());

				if (aPoint.y >= Bottom() && aPoint.y <= Top())
				{
					Serial.println(". Inside T/B and inside Box.");

					return true;
				}
				else
				{
					Serial.println(". NOT inside B/T and NOT inside Box.");
				}
			}
			else
			{
				Serial.println(". NOT inside L/R.  Not testing B/T.");
			}
		}
		return false;
	}

	String Button::Name()
	{
		return String();
	}
#pragma endregion

#pragma endregion

#pragma region LCD_Panel_V2

#pragma region LCD_Constructors

	LCD_Panel_V2::LCD_Panel_V2()
	{

	}

	LCD_Panel_V2::~LCD_Panel_V2()
	{
	}

#pragma endregion

#pragma region LCD_Methods
	void LCD_Panel_V2::AddButton(String aName,
		unsigned short  aTop, unsigned short  aLeft,
		unsigned short  aHeight, unsigned short  aWidth,
		char* aTxt,
		unsigned short  aForeGround, unsigned short  aBackground)
	{
		Button btn = Button(aName,
			aTop, aLeft,
			aHeight, aWidth,
			aTxt,
			aForeGround, aBackground);
		mBtns.push_back(btn);
		btn.Draw();
	}

	void LCD_Panel_V2::Select(Point aPoint)
	{
		Button btn = GetByPoint(aPoint);
		btn.Select();
		ReDraw();
	}
	void LCD_Panel_V2::Toggle(Point aPoint)
	{
		Button btn = GetByPoint(aPoint);
		btn.Toggle();
		ReDraw();
	}
	void LCD_Panel_V2::Select(String aName)
	{
		Button btn = GetByName(aName);
		btn.Select();
		ReDraw();
	}
	void LCD_Panel_V2::Toggle(String aName)
	{
		Button btn = GetByName(aName);
		btn.Toggle();
		ReDraw();
	}

	void LCD_Panel_V2::ReDraw()
	{
		for (int b = 0; b < mBtns.size(); b++)
		{
			if (mBtns[b].IsValid())
			{
				mBtns[b].Draw();
			}
		}
	}
#pragma endregion

#pragma region LCD_Property_Setters
#pragma endregion

#pragma region LCD_Property_Getters
	TouchScreen LCD_Panel_V2::myTouchPanel()
	{
		return mTouch;
	}
	Button LCD_Panel_V2::GetByName(String aName)
	{
		Button btn;
		for (int b = 0; b < mBtns.size(); b++)
		{
			if (mBtns[b].Name() == aName)
			{
				btn = mBtns[b];
				return btn;
			}
		}
		btn = Button();
		return btn;
	}

	Button LCD_Panel_V2::GetByPoint(Point aPoint)
	{
		Serial.print("Looking for Point X: ");
		Serial.print(aPoint.x);
		Serial.print(", Y: ");
		Serial.println(aPoint.y);
		Button btn;
		for (int b = 0; b < mBtns.size(); b++)
		{
			Serial.print("Checking Button Lower Left: X: ");
			Serial.print(mBtns[b].Left());
			Serial.print(", Y: ");
			Serial.print(mBtns[b].Bottom());
			Serial.print(".  Upper Right: X: ");
			Serial.print(mBtns[b].Right());
			Serial.print(", Y: ");
			Serial.println(mBtns[b].Top());

			if (mBtns[b].Contains(aPoint))
			{
				Serial.println (" --- Match");
				btn = mBtns[b];
				return btn;
			}
			else
			{
				Serial.println(" --- No Match");
			}
		}
		btn = Button();
		return btn;
	}

#pragma endregion







#pragma endregion
}