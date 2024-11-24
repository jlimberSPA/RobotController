//
//
//

#include "ControlElement.h"

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
		ControlType* aParent,
		EventHandlerFunction aEHF,
		PushOptions aPush = (PushOptions)0U) : mParent{ aParent },
		mDP{ aDP },
		OnClickEventHandler{ aEHF },
		mPush{ aPush },
		mHasEHF{ aEHF ? true : false }
	{
	}

	char* ControlElement::ToString() const
	{
		char out[128];
		strcat_s(out, "Control Element (");
		strcat_s(out, SubClass());
		strcat_s(out, ") : ");
		strcat_s(out, Name());
		return out;
	}
	void ControlElement::RollCall() const
	{
		PseudoSerial::print(F("\t\t\t"));
		PseudoSerial::println(ToString());
		mDP.RollCall();
		PseudoSerial::print(F("\n\t\t\tFinished "));
		PseudoSerial::println(ToString());
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
		mParent->Toggle();
		if (mHasEHF) {
			OnClickEventHandler();
		}
	}
#pragma endregion ControlElement

#pragma region BoundingBox
	BoundingBox::BoundingBox(DrawParameters& aDP, ControlType* aParent,
		EventHandlerFunction aEHF = nullptr,
		PushOptions aPush = (PushOptions)0U) :
		ControlElement{ aDP, aParent, aEHF, aPush }
	{
		mName = "A Bounding Box";
		SetSubClass();
	}
	void BoundingBox::Draw() const
	{
		if (mDP.IsValid())
		{
			//Tft.fillRectangle(mDP.Left(), mDP.Top(),
			//	mDP.Width(), mDP.Height(),
			//	mDP.Background());
			//if (mSelected)
			//{
			//	Tft.drawRectangle(mDP.Left(), mDP.Top(), mDP.Width(), mDP.Height(), YELLOW);
			//	Tft.drawRectangle(mDP.Left() + 2, mDP.Top() + 2, mDP.Width() - 4, mDP.Height() - 4, YELLOW);
			//}
		}
	}

	char* BoundingBox::ToString() const
	{
		return ControlElement::ToString();;
	}
	void BoundingBox::RollCall() const
	{
		ControlElement::RollCall();
	}
#pragma endregion BoundingBox

#pragma region TextElement Class
#pragma region TextElement Constructor
	TextElement::TextElement(const char* aTxt,
		DrawParameters& aDP, ControlType* aParent,
		EventHandlerFunction aEHF = nullptr,
		PushOptions aPush = (PushOptions)0U) :
		ControlElement{ aDP, aParent, aEHF, aPush }
	{
		mName = "A Text Element";
		SetSubClass();
	}
#pragma endregion TextElement Constructor
#pragma region TextElementPropertyGetters
	void TextElement::Draw() const
	{
		if (mDP.IsValid())
		{
			//Tft.fillRectangle(mDP.Left(), mDP.Top(),
			//	mDP.Width(), mDP.Height(),
			//	mDP.Background());
			//Tft.drawString(GetText(),
			//	(unsigned short)(mDP.Left() + 2),
			//	(unsigned short)(mDP.Top() + 4),
			//	(unsigned short)2,
			//	mDP.Foreground(), PORTRAIT);
		}
	}
	char* TextElement::ToString() const
	{
		char* out = ControlElement::ToString();
		strcat(out, " Txt: ");
		strcat(out, GetText());
		return out;
	}
	void TextElement::RollCall() const
	{
		PseudoSerial::print(F("\t\t\t"));
		PseudoSerial::println(ToString());
		PseudoSerial::println(F("\t\t\t\twith DrawParameters"));
		mDP.RollCall();
		PseudoSerial::print(F("\n\t\t\tFinished "));
		PseudoSerial::println(ToString());
	}
	char* TextElement::GetText() const
	{
		return mParent->GetString(mTxtKey);
	}
	void TextElement::SetText(char* aTxt)
	{
		mParent->SetString(mTxtKey, aTxt);
	}

#pragma endregion TextElement PropertyGetters
}