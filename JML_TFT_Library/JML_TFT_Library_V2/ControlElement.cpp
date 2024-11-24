//
//
//

#include "ControlElement.h"

namespace stsn = SeeedTouchScreenNamespace;
using namespace stsn;
//class stsn::Point;

namespace JML_TFT_Library_V2
{
	//#ifndef _JML_SUPPORT_TYPES
	//#define _JML_SUPPORT_TYPES
	//	//using SeeedPt = SeeedTouchScreenNamespace::Point;
	//	enum class PushOptions :uint8_t { none, select, unselect, toggle };
	//	typedef bool (*EventHandlerFunction)();
	//	enum class ControlTypes :uint8_t { TextBox, TextPanel, Button, JSD };
	//	class IControlType;
	//	class ControlElement;
	//#endif
#pragma region ControlElement
	ControlElement::ControlElement(DrawParameters& aDP,
		IControlType* aParent,
		EventHandlerFunction aEHF,
		PushOptions aPush) : mDP{ aDP },
		mParent{ aParent },
		OnClickEventHandler{ aEHF },
		mPush{ aPush },
		mName{ F("Generic CE") }
	{
		mHasEHF = { aEHF ? true : false };
	}

	String ControlElement::ToString() const
	{
		String out = "Control Element (";
		out.concat(SubClass());
		out.concat(") : ");
		out.concat(Name());
		return out;
	}
	void ControlElement::RollCall() const
	{
		Serial.print(F("\t\t\t"));
		Serial.println(ToString());
		mDP.RollCall();
		Serial.print(F("\n\t\t\tFinished "));
		Serial.println(ToString());
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
	BoundingBox::BoundingBox(DrawParameters& aDP, IControlType* aParent,
		EventHandlerFunction aEHF,
		PushOptions aPush) :
		ControlElement{ aDP, aParent, aEHF, aPush }
	{
		mName = F("A Bounding Box");
		SetSubClass();
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
		DrawParameters& aDP, IControlType* aParent,
		EventHandlerFunction aEHF,
		PushOptions aPush) :
		ControlElement{ aDP, aParent, aEHF, aPush }
	{
		mName = F("A Text Element");
		SetSubClass();
	}

	TextElement::TextElement(const __FlashStringHelper* aTxt, DrawParameters& aDP, IControlType* aParent,
		EventHandlerFunction aEHF, PushOptions aPush) :
		ControlElement{ aDP, aParent, aEHF, aPush }
	{
		mName = F("A Text Element");
		SetSubClass();
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
		String out = ControlElement::ToString();
		out.concat(" Txt: ");
		out.concat(GetText());
		return out;
	}
	void TextElement::RollCall() const
	{
		Serial.print(F("\t\t\t"));
		Serial.println(ToString());
		Serial.println(F("\t\t\t\twith DrawParameters"));
		mDP.RollCall();
		Serial.print(F("\n\t\t\tFinished "));
		Serial.println(ToString());
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