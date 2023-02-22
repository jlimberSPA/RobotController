// 
// 
// 

#include "TFT_Interface_JML.h"
namespace TFT_Interface_JML
{
	LCD_Panel_V2::LCD_Panel_V2()
	{

	}

	LCD_Panel_V2::~LCD_Panel_V2()
	{
	}

	TouchScreen LCD_Panel_V2::myTouchPanel()
	{
		return mTouch;
	}

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
		Button btn;
		for (int b = 0; b < mBtns.size(); b++)
		{
			if (mBtns[b].Contains(aPoint))
			{
				btn = mBtns[b];
				return btn;
			}
		}
		btn = Button();
		return btn;
	}

	void LCD_Panel_V2::Select(Point aPoint)
	{
		Button btn = GetByPoint(aPoint);
		btn.Select();
	}
	void LCD_Panel_V2::Toggle(Point aPoint)
	{
		Button btn = GetByPoint(aPoint);
		btn.Toggle();
	}
	void LCD_Panel_V2::Select(String aName)
	{
		Button btn = GetByName(aName);
		btn.Select();
	}
	void LCD_Panel_V2::Toggle(String aName)
	{
		Button btn = GetByName(aName);
		btn.Toggle();
	}

	Button::Button()
	{
	}

	//Button::Button(LCD_Panel_V2 aTs)
	//{
	//	mTs = aTs;
	//}

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

	void Button::Draw()
	{
		TFT().fillRectangle(mLeft,mTop-mHeight,mHeight, mWidth, mBackground);
		TFT().drawString(mTxt, 
								   (unsigned short)(mTop - mHeight + 2), 
								   (unsigned short)(mLeft + 2),
								   (unsigned short)2, 
									mForeground, LANDSCAPE);
		if (mSelected)
		{
			TFT().drawRectangle(mLeft, mTop - mHeight, mHeight, mWidth, YELLOW);
			TFT().drawRectangle(mLeft+2, mTop - mHeight-2, mHeight-4, mWidth+4, YELLOW);
		}
		else
		{

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

	bool Button::IsValid()
	{
		bool validX = (mLeft > 0) && (mLeft<=320);
		bool validY = (mTop > 0) && (mTop <= 240);
		bool validName = (mName.length() > 0);
		return validName && validX && validY;
	}

	bool Button::Contains(Point aPoint)
	{
		if (IsValid())
		{
			if (aPoint.x >= mLeft && aPoint.x <= mLeft + mWidth)
			{
				if (aPoint.y >= mTop - mHeight && aPoint.x <= mTop)
				{
					return true;
				}
			}
		}
		return false;
	}

	String Button::Name()
	{
		return String();
	}

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
}