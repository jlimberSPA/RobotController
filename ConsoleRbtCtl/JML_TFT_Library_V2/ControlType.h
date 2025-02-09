// ControlType.h

#ifndef _CONTROLTYPE_h
#define _CONTROLTYPE_h

//#if defined(ARDUINO) && ARDUINO >= 100
//#include "arduino.h"
//#else
//#include "WProgram.h"
//#endif

#ifndef __STD_HEADER_MAP
#include <map>
#endif

#ifndef __STD_HEADER_VECTOR
#include <vector>
#endif

#ifndef _DRAWPARAMETERS_h
#include "DrawParameters.h"
#endif

#ifndef _CONTROLELEMENT_h
#include "ControlElement.h"
#endif
//namespace stsn = SeeedTouchScreenNamespace;
//using namespace stsn;
//class stsn::Point;

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

	class BoundingBox;
	class TextElement;
	class ControlElement;
	using std::vector;
	using std::map;

#pragma region Control Types
	/*
	CONTROL TYPES:
	- These are the implementation of the different types of controls
	- They will each include different control elements common to that control
	- They will derive from a common abstract class that invokes standard virtual functions
	*/
	class ControlType;

	static class ControlTypeFactory
	{
	public:
		static ControlType* Build(const char* aName, const ControlTypes aCT, const DrawParameters& aDP,
			EventHandlerFunction aEHF);
	};

	class ControlType
	{
	public:
		ControlType() = default;
		ControlType(const char* mName,
			const ControlTypes myType,
			const DrawParameters mDP)
			: myType(myType),
			mDP(mDP), myCE_BB(myCE_BB), mName(mName)
		{
		}
		ControlType(const ControlTypes& myType,
			const const DrawParameters&& mDP,
			const vector<BoundingBox>& myCE_BB,
			const vector<TextElement>& myCE_TE,
			const char* mName)
			: myType(myType),
			mDP(mDP), myCE_BB(myCE_BB), myCE_TE(myCE_TE), mName(mName)
		{
		}
		~ControlType() = default;

		// Property Getters
		ControlTypes getType() const { return myType; }
		char* GetString(char* key) const;
		int GetInt(char* key);

		bool IsDynamic() const { return mIsDynamic; } // IsDynamic indicates if this control changes it's display
		const char* Name() const { return mName; }

		// Property Setters
		void putType(ControlTypes val) { myType = val; }
		void SetString(char* key, const char* value);
		void SetInt(char* key, int value);

		__declspec(property(get = getType, put = putType)) int MyType;
		__declspec(property(get = GetString, put = SetString)) char* StringVal;
		__declspec(property(get = GetInt, put = SetInt)) int IntVal;

		//Methods
		char* ToString() const;
		void RollCall() const;
		bool IsValid() const;
		//bool Contains(stsn::Point& aPoint) const { return mDP.Contains(&aPoint); }

		size_t StringListSize() const { return txtData.size(); }
		size_t IntListSize() const { return intData.size(); }

		void Draw() const;
		void AddBoundingBox(BoundingBox const& aBB);
		void AddTextElement(TextElement const& TE);
		void Toggle() { mIsSelected = !mIsSelected; }
		void MakeDynamic(bool val) { mIsDynamic = val; };

	private:
		ControlTypes myType;
		bool mIsDynamic = false;
		bool mIsSelected = false;
		//Private Constructor
		ControlType(const char* aName, const DrawParameters& aDP);

		const DrawParameters& mDP;
		vector<BoundingBox> myCE_BB = vector<BoundingBox>();
		vector<TextElement> myCE_TE = vector<TextElement>();
		map<char*, const char*> txtData = map<char*, const char*>();
		map<char*, int>   intData = map<char*, int>();
		const char* mName;

	public:
	};

	//class TextBox : ControlType
	//{
	//public:
	//	TextBox() = delete;
	//	TextBox(ControlElement& aControl, char* aCaption = "", char* aValue = "");
	//	~TextBox() = default;
	//	//Property Getters
	//	char* ToString() const override;
	//	const bool IsDynamic() const override;
	//	char* const GetText();
	//	//ControlTypes const ControlType() { return ControlTypes::TextBox; };
	//	//Property Setters
	//	void SetCaption(char* aCaption);
	//	void SetValue(char* aVal);
	//	//Methods
	//	void Draw() const override;
	//private:
	//	void SetText(char* aTxt) {};
	//	void SetControlText();
	//	char* mVal;
	//	char* mCaption;
	//	char* mTitle;
	//	ControlElement& mControl;
	//};
#pragma endregion Control Types

	//class Button
	//{
	//public:
	//	Button() = delete;
	//	Button(ControlElement& aControl);
	//	~Button() = default;
	//	//Property Getters
	//	char* const ToString() { return mControl.ToString(); };
	//	char* const GetText() { return mControl.Title(); };
	//	ControlTypes const ControlType() { return ControlTypes::Button; };
	//	//Property Setters
	//	//void SetText(char* aTxt)
	//	//Methods
	//	void Draw();
	//	//Put Event Handler's here not in control!
	//private:
	//	char* mTxt;
	//	ControlElement& mControl;
	//};
	//class TextPanel
	//{
	//};
	//class JoystickDisplayControl
}
#endif