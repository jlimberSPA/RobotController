// ControlElement.h

#ifndef _CONTROLELEMENT_h
#define _CONTROLELEMENT_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#ifndef _DRAWPARAMETERS_h
#include "DrawParameters.h"
#endif

#ifndef _CONTROLTYPE_h
#include "ControlType.h"
#endif

#include <TFTv2.h>

namespace JML_TFT_Library_V2
{
	// Forward Declaration
	class IControlType;

	/*
	CONTROL ELEMENTS:
	- These are the basic visual elements of the different types of controls
	- Controls will be created by composition using different control elements common to that control

	*/
	class ControlElement
	{
	public:
		ControlElement() = delete;
		ControlElement(DrawParameters& aDP,
			IControlType* aParent,
			EventHandlerFunction aEHF = nullptr,
			PushOptions aPush = (PushOptions)0U);
		~ControlElement() = default;

		//PropertyGetters
		virtual String ToString() const;
		virtual void RollCall() const;
		const __FlashStringHelper* Name() const { return mName; }
		DrawParameters& DP() { return mDP; }
		const __FlashStringHelper* SubClass() const { return mSubClass; }

		bool IsSelectable() const;
		bool IsSelected() const;
		bool IsValid() const { return mDP.IsValid(); };

		// Property Setters
		void SetSelectable(bool aValue);
		void SetSelected(bool aValue);

		// Methods
		virtual void Draw() const {};
		virtual void Select();
		virtual void UnSelect();
		virtual void Toggle();
	protected:
		// Methods
		virtual void SetSubClass() = 0;

		// Backing Fields
		IControlType* mParent;
		TFT& mScreen = Tft;
		DrawParameters& mDP;
		bool mSelectable;
		bool mSelected;
		const __FlashStringHelper* mSubClass;

		// Defines a variable of type EventHandlerFunction (a function pointer)
		// to hold a reference to the function for the OnClick event
		EventHandlerFunction OnClickEventHandler;
		bool mHasEHF = false;
		PushOptions	mPush;
		const __FlashStringHelper* mName;
	};

#pragma region BoundingBox
	// A Bounding Box Defines a Clickable Area on a Control
	class BoundingBox : public ControlElement
	{
	public:
		BoundingBox() = delete;
		BoundingBox(DrawParameters& aDP, IControlType* aParent,
			EventHandlerFunction aEHF = nullptr, PushOptions aPush = (PushOptions)0U);
		void Draw() const override;
		String ToString() const override;
		void RollCall() const;
	private:
		void SetSubClass() { mSubClass = F("BB"); }
	};
#pragma endregion BoundingBox

#pragma region TextElement
	class TextElement : public ControlElement
	{
	public:
		TextElement() = delete;
		TextElement(const char* aTxt, DrawParameters& aDP, IControlType* aParent,
			EventHandlerFunction aEHF = nullptr, PushOptions aPush = (PushOptions)0U);
		TextElement(const __FlashStringHelper* aTxt, DrawParameters& aDP, IControlType* aParent,
			EventHandlerFunction aEHF = nullptr, PushOptions aPush = (PushOptions)0U);
		void Draw() const override;
		String ToString() const override;
		void RollCall() const;
		char* GetText() const;
		void SetText(char* aTxt);
		void SetKey(int aKey) { mTxtKey = aKey; }
	private:
		int mTxtKey;
		void SetSubClass() { mSubClass = F("TE"); }
	};
#pragma endregion TextElement
#pragma region ListElement

#pragma endregion ListElement
#pragma region JSD
#pragma endregion JSD
}
#endif
