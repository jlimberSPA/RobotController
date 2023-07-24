// ControlElement.h

#ifndef _CONTROLELEMENT_h
#define _CONTROLELEMENT_h

#ifndef _PSEUDOSERIAL_H
#include "../PseudoSerial.h"
#endif

#ifndef _DRAWPARAMETERS_h
#include "DrawParameters.h"
#endif

#ifndef _CONTROLTYPE_h
#include "ControlType.h"
#endif

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
	class ControlType;
#pragma region ControlElements
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
			ControlType* aParent,
			EventHandlerFunction aEHF = nullptr,
			PushOptions aPush = (PushOptions)0U);
		~ControlElement() = default;

#pragma region Properties and Methods of Control Element
		//PropertyGetters
		virtual char* ToString() const;
		virtual void RollCall() const;
		char* Name() const { return char* (mName); }
		DrawParameters& DP() { return mDP; }
		char* SubClass() const { return mSubClass; }

		bool IsSelectable() const;
		bool IsSelected() const;
		bool IsValid() const { mDP.IsValid(); };

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
		ControlType* mParent;
		TFT& mScreen = Tft;
		DrawParameters& mDP;
		bool mSelectable;
		bool mSelected;
		char* mSubClass = "X";

		// Defines a variable of type EventHandlerFunction (a function pointer)
		// to hold a reference to the function for the OnClick event
		EventHandlerFunction OnClickEventHandler;
		bool mHasEHF = false;
		PushOptions	mPush;
		const char* mName = "Generic CE";
#pragma endregion
	};
#pragma endregion ControlElements

#pragma region BoundingBox
	class BoundingBox : public ControlElement
	{
	public:
		BoundingBox() = delete;
		BoundingBox(DrawParameters& aDP, ControlType* aParent,
			EventHandlerFunction aEHF = nullptr, PushOptions aPush = (PushOptions)0U);
		void Draw() const override;
		char* ToString() const override;
		void RollCall() const;
	private:
		void SetSubClass() { mSubClass = "BB"; }
	};
#pragma endregion BoundingBox

#pragma region TextElement
	class TextElement : public ControlElement
	{
	public:
		TextElement() = delete;
		TextElement(const char* aTxt, DrawParameters& aDP, ControlType* aParent,
			EventHandlerFunction aEHF = nullptr, PushOptions aPush = (PushOptions)0U);
		void Draw() const override;
		char* ToString() const override;
		void RollCall() const;
		char* GetText() const;
		void SetText(char* aTxt);
		void SetKey(char* aKey) { mTxtKey = aKey; }
	private:
		char* mTxtKey;
		void SetSubClass() { mSubClass = "TE"; }
	};
#pragma endregion TextElement
#pragma region ListElement

#pragma endregion ListElement
#pragma region JSD
#pragma endregion JSD
}
#endif
