#ifndef _RAMCHECK_h
#include "../JML_TFT_Library_V2/RAMCheck.h"
#endif
#include "ControlType.h"

namespace JML_TFT_Library_V2
{
	//class RAMCheck;
	class BoundingBox;
	class IControlType;

	IControlType::IControlType(const char* aName, const DrawParameters& aDP) : mDP{ aDP }, mName{ (const __FlashStringHelper*)aName }
	{
	}
	IControlType::IControlType(const __FlashStringHelper* aName, const DrawParameters& aDP) : mDP{ aDP }, mName{ aName }
	{
	}
	void IControlType::Draw() const
	{
		for (BoundingBox bb : myCE_BB)
		{
			bb.Draw();
		}
		for (TextElement te : myCE_TE)
		{
			te.Draw();
		}
	}

	void IControlType::RollCall() const
	{
		auto sz = myCE_BB.size();
		sz += myCE_TE.size();
		Serial.print(F("\t\t-"));
		Serial.print(ToString());
		Serial.print(F(" with "));
		Serial.print(sz);
		Serial.println(F(" ControlElements"));
		for (BoundingBox bb : myCE_BB)
		{
			bb.RollCall();
		}
		for (TextElement te : myCE_TE)
		{
			te.RollCall();
		}
		Serial.print(F("\t\t Finished "));
		Serial.println(ToString());
	}
	bool IControlType::IsValid() const
	{
		//Serial.println((String)mName);
		//Serial.print("[(IControlType:" + (String)Name() + " " +
		//	(String)myControlElements.size() + ") DP:");
		bool valid = mDP.IsValid();
		//String out = " (Invalid DP)]";
		if (valid)
		{
			//out = "(Valid DP, ";
			for (BoundingBox bb : myCE_BB)
			{
				valid &= bb.IsValid();
			}
			for (TextElement te : myCE_TE)
			{
				valid &= te.IsValid();
			}
			//out = valid + (valid ? "Ctls Valid)]" : "Ctls Invalid)]#");
		}
		//if (!valid) { Serial.print(out); }
		return valid;
	}
	char* IControlType::GetString(int idx) const
	{
		if (txtData.size() > idx)
		{
			return txtData[idx];
		}
		else
		{
			return "-";
		}
	}
	int IControlType::GetInt(int idx) const
	{
		if (intData.size() > idx)
		{
			return intData[idx];
		}
		else
		{
			return -1;
		}
	}
	void IControlType::AddBoundingBox(BoundingBox aBB)
	{
		Serial.print(F("\tAdding BB named "));
		Serial.print(aBB.Name());
		Serial.print(F(" to CT: "));
		Serial.print(GetName());
		myCE_BB.push_back(aBB);

		Serial.print(F(" Now there are "));
		Serial.print(myCE_BB.size());
		Serial.println(F(" BBs."));
	}
	void IControlType::AddTextElement(TextElement aTE)
	{
		Serial.print(F("\tAdding TE named "));
		Serial.print(aTE.Name());
		Serial.print(F(" to CT: "));
		Serial.print(GetName());
		myCE_TE.push_back(aTE);

		Serial.print(F(" Now there are "));
		Serial.print(myCE_TE.size());
		Serial.println(F(" TEs."));
	}
	TextBox::TextBox(const char* aName, const DrawParameters& aDP, const char* aTxt) :
		IControlType((const __FlashStringHelper*)aName, aDP),
		mCaption((const __FlashStringHelper*)aTxt) {
	}
	TextBox::TextBox(const __FlashStringHelper* aName, const DrawParameters& aDP,
		const __FlashStringHelper* aTxt)
		: IControlType(aName, aDP), mCaption((const __FlashStringHelper*)aTxt) {
	}
	Button::Button(const char* aName, const DrawParameters& aDP,
		const char* aTxt, EventHandlerFunction aEHF) :
		IControlType(aName, aDP), mTxt((const __FlashStringHelper*)aTxt), mOnClick(aEHF) {
	}
	Button::Button(const __FlashStringHelper* aName, const DrawParameters& aDP,
		const __FlashStringHelper* aTxt, EventHandlerFunction aEHF) :
		IControlType(aName, aDP), mTxt(aTxt), mOnClick(aEHF) {
	}
}