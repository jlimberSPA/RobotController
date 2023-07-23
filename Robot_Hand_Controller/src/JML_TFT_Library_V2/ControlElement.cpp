//
//
//

#include "ControlElement.h"

namespace stsn = SeeedTouchScreenNamespace;
using namespace stsn;
class stsn::Point;

namespace JML_TFT_Library_V2
{
#ifndef _JML_SUPPORT_TYPES
#define _JML_SUPPORT_TYPES
	//using SeeedPt = SeeedTouchScreenNamespace::Point;
	enum class PushOptions :uint8_t { none, select, unselect, toggle };
	typedef bool (*EventHandlerFunction)();
	enum class ControlTypes :uint8_t { TextBox, TextPanel, Button, JSD };
	class ControlType;
	class ControlElement;
#endif
#pragma region ControlElement
	ControlElement::ControlElement(DrawParameters& aDP,
		ControlType& aParent,
		EventHandlerFunction aEHF = nullptr,
		PushOptions aPush = (PushOptions)0U) : mDP{ aDP },
		mParent{ aParent },
		OnClickEventHandler{ aEHF },
		mPush{ aPush }
	{
		mHasEHF = { aEHF ? true : false };
	}
	String ControlElement::ToString() const
	{
		String result;
		//result += "\t Text: " + (String)Title();
		result += "\t Left, Top: (" + (String)mDP.Left() + ", " + mDP.Top() + ")";
		result += "\t Right, Bottom: (" + (String)mDP.Right() + ", " + mDP.Bottom() + ")";
		result += "\t Width, Height: (" + (String)mDP.Width() + ", " + mDP.Height() + ")";
		return result;
	}
	bool ControlElement::IsSelectable() const
	{
		return mSelectable;
	}
	bool ControlElement::IsSelected() const
	{
		return mSelected;
	}
	void ControlElement::SetSelectable(bool aValue)
	{
		mSelectable = aValue;
	}
	void ControlElement::SetSelected(bool aValue)
	{
		mSelected = aValue;
	}
	void ControlElement::Select()
	{
		mSelected = true;
	}
	void ControlElement::UnSelect()
	{
		mSelected = false;
	}
	void ControlElement::Toggle()
	{
		mSelected = !mSelected;
		mParent.Toggle();
		if (mHasEHF) {
			OnClickEventHandler();
		}
	}
#pragma endregion ControlElement

#pragma region BoundingBox
	BoundingBox::BoundingBox(DrawParameters& aDP, ControlType aParent,
		EventHandlerFunction aEHF = nullptr,
		PushOptions aPush = (PushOptions)0U) :
		ControlElement{ aDP, aParent, aEHF, aPush }
	{
	}
	void BoundingBox::Draw() const
	{
		if (mDP.IsValid())
		{
			Tft.fillRectangle(mDP.Left(), mDP.Top(),
				mDP.Width(), mDP.Height(),
				mDP.Background());
			if (mSelected)
			{
				Tft.drawRectangle(mDP.Left(), mDP.Top(), mDP.Width(), mDP.Height(), YELLOW);
				Tft.drawRectangle(mDP.Left() + 2, mDP.Top() + 2, mDP.Width() - 4, mDP.Height() - 4, YELLOW);
			}
		}
	}

	String BoundingBox::ToString() const
	{
		return mDP.ToString();;
	}

#pragma endregion BoundingBox

#pragma region TextElement Class
#pragma region TextElement Constructor
	TextElement::TextElement(const char* aTxt,
		DrawParameters& aDP, ControlType aParent,
		EventHandlerFunction aEHF = nullptr,
		PushOptions aPush = (PushOptions)0U) :
		ControlElement{ aDP, aParent, aEHF, aPush }
	{
	}
#pragma endregion TextElement Constructor
#pragma region TextElementPropertyGetters
	void TextElement::Draw() const
	{
		if (mDP.IsValid())
		{
			Tft.fillRectangle(mDP.Left(), mDP.Top(),
				mDP.Width(), mDP.Height(),
				mDP.Background());
			Tft.drawString(GetText(),
				(unsigned short)(mDP.Left() + 2),
				(unsigned short)(mDP.Top() + 4),
				(unsigned short)2,
				mDP.Foreground(), PORTRAIT);
		}
	}
	String TextElement::ToString() const
	{
		String result = (String)GetText() + "\t" + mDP.ToString();
		return result;
	}
	char* TextElement::GetText() const
	{
		return mParent.GetString(mTxtKey);
	}
	void TextElement::SetText(char* aTxt)
	{
		mParent.SetString(mTxtKey, aTxt);
	}

#pragma endregion TextElement PropertyGetters
}