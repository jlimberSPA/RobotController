// IControlType.h

#ifndef _CONTROLTYPE_h
#define _CONTROLTYPE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#ifndef __STD_HEADER_VECTOR
#include <..\Arduino_AVRSTL\src\vector>
#endif

#ifndef _DRAWPARAMETERS_h
#include "DrawParameters.h"
#endif

#ifndef _CONTROLELEMENT_h
#include "ControlElement.h"
#endif
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

	class BoundingBox;
	class TextElement;
	class ControlElement;
	using std::vector;

#pragma region Control Types
	/*
	CONTROL TYPES:
	- These are the implementation of the different types of controls
	- They will each include different control elements common to that control
	- They will derive from a common abstract class that invokes standard virtual functions
	*/

	class IControlType
	{
	public:
		IControlType(const char* aName, const DrawParameters& aDP);
		IControlType(const __FlashStringHelper* aName, const DrawParameters& aDP);
		~IControlType() {};
		// Property Getter Only
		virtual ControlTypes mMyType() const = 0;
		bool IsValid() const;
		bool Contains(stsn::Point& aPoint) const { return mDP.Contains(&aPoint); }
		int StringListSize() const { return txtData.size(); }
		int IntListSize() const { return intData.size(); }

		// Property Getter and Setters
		const __FlashStringHelper* GetName() const { return mName; }
		void SetName(const __FlashStringHelper* aName) { mName = aName; }

		char* GetString(int idx) const;
		void SetString(int idx, char* value) { txtData[idx] = value; }

		int GetInt(int idx) const;
		void SetInt(int idx, int value) { intData[idx] = value; }

		// IsDynamic indicates if this control changes it's display
		bool IsDynamic() const { return mIsDynamic; }
		void MakeDynamic(bool val) { mIsDynamic = val; }

		//Methods
		virtual void Draw() const; // Can be overridden, but not mandatory
		void AddBoundingBox(BoundingBox aBB);
		void AddTextElement(TextElement TE);
		void Toggle() { mIsSelected = !mIsSelected; }
		virtual void RollCall() const = 0;
		virtual String ToString() const = 0;

	protected:
		bool mIsDynamic = false;
		bool mIsSelected = false;

	private:
		//Private Constructor

		const DrawParameters& mDP;
		// The Control Type Object is made up of multiple
		// BoundingBox and TextElement ControlElements
		vector<BoundingBox> myCE_BB = vector<BoundingBox>();
		vector<TextElement> myCE_TE = vector<TextElement>();
		vector<char*> txtData = vector<char*>();
		vector<int> intData = vector<int>();
		const __FlashStringHelper* mName;
	};

	class TextBox : public IControlType
	{
	public:
		TextBox() = delete;
		TextBox(const char* aName, const DrawParameters& aDP, const char* aTxt);
		TextBox(const __FlashStringHelper* aName, const DrawParameters& aDP,
			const __FlashStringHelper* aTxt);

		~TextBox() = default;

		//Property Getters
		ControlTypes mMyType() const override { return ControlTypes::TextBox; }

		//Property Setters
		//
		//Methods
		void Draw() const override {};
		void RollCall() const override {};
		String ToString() const override { return GetName(); }

	private:
		void SetText(const char* aTxt) { mCaption = (const __FlashStringHelper*)aTxt; }
		void SetText(const __FlashStringHelper* aTxt) { mCaption = aTxt; }
		const __FlashStringHelper* mCaption;
	};
#pragma endregion Control Types

	class Button : public IControlType
	{
	public:
		Button() = delete;
		Button(const char* aName, const DrawParameters& aDP,
			const char* aTxt, EventHandlerFunction aEHF);
		Button(const __FlashStringHelper* aName, const DrawParameters& aDP,
			const __FlashStringHelper* aTxt, EventHandlerFunction aEHF);

		~Button() = default;

		//Property Getters
		ControlTypes mMyType() const override { return ControlTypes::Button; }

		//Property Setters

		//Methods
		void Draw() const override {};
		void RollCall() const override {};
		String ToString() const override { return GetName(); }

	private:
		const __FlashStringHelper* mTxt;
		EventHandlerFunction mOnClick;
	};
}
#endif
