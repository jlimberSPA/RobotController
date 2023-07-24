//
//
//
#ifndef _RAMCHECK_h
#include "../JML_TFT_Library_V2/RAMCheck.h"
#endif
#include "ControlType.h"

namespace JML_TFT_Library_V2
{
	//class RAMCheck;
	class BoundingBox;
	class ControlType;

	ControlType* ControlTypeFactory::Build(char* aName, ControlTypes aCT, DrawParameters& aDP,
		EventHandlerFunction aEHF = nullptr)
	{
		if (aCT == ControlTypes::TextBox)
		{
			// Create the ControlType Object
			ControlType* newCT = ControlType::ControlTypePtr(aName, aDP);
			newCT->myType = ControlTypes::TextBox;

			// Add the Bounding Box
			BoundingBox mBB = BoundingBox(aDP, newCT);
			newCT->AddBoundingBox(mBB);

			// Add the Text Element
			TextElement mTE = TextElement((char*)' ', aDP, newCT);
			newCT->AddTextElement(mTE);
			String key = "Text";
			auto keyNum = newCT->StringListSize();
			key.concat(keyNum);
			mTE.SetKey(key);
			newCT->SetString(key, "Default Text");

			Serial.print(F("Created new CT in Factory. name param: "));
			Serial.print(aName);
			Serial.print(F(" has name: "));
			Serial.println(newCT->Name());
			Serial.print(F("\tDP Param:"));
			Serial.println(aDP.ToString());
			Serial.print(F("\tBounding Box:"));
			Serial.print(mBB.ToString());
			Serial.print(F(" DP: "));
			Serial.println(mBB.DP().ToString());
			Serial.print(F("\tText Element:"));
			Serial.print(mTE.ToString());
			Serial.print(F(" DP: "));
			Serial.println(mTE.DP().ToString());

			Serial.println(F("\tFactory Roll Call:"));
			newCT->RollCall();
			Serial.print(F("\t"));
			RAMCheck::display_freeram();
			Serial.println(F("\t---------"));
			return newCT;
		}
		else if (aCT == ControlTypes::Button)
		{
			// Create the ControlType Object
			ControlType* newCT = ControlType::ControlTypePtr(aName, aDP);
			newCT->myType = ControlTypes::TextBox;

			// Add the Bounding Box
			BoundingBox mBB = BoundingBox(aDP, newCT, aEHF);
			newCT->AddBoundingBox(mBB);

			// Add the Text Element
			TextElement mTE = TextElement((char*)' ', aDP, newCT);
			newCT->AddTextElement(mTE);
			mTE.SetKey('Btn' + (String)newCT->StringListSize());
			newCT->SetString('Btn' + (String)newCT->StringListSize(), "");
			return newCT;
		}
		else if (aCT == ControlTypes::TextPanel)
		{
		}
		else if (aCT == ControlTypes::JSD)
		{
		}
	}
	ControlType::ControlType(char* aName, const DrawParameters& aDP) : mDP{ aDP }, mName{ aName }
	{
	}
	void ControlType::Draw() const
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
	String ControlType::ToString() const
	{
		return "Control Type: " + (String)(uint8_t)myType + " " + Name();
	}
	void ControlType::RollCall() const
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
	bool ControlType::IsValid() const
	{
		//Serial.println((String)mName);
		//Serial.print("[(ControlType:" + (String)Name() + " " +
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
	char* ControlType::GetString(String key) const
	{
		if (txtData.find(key) != txtData.end())
		{
			return txtData[key];
		}
		else
		{
			return "";
		}
	}
	int ControlType::GetInt(String key)
	{
		if (intData.find(key) != intData.end())
		{
			return intData[key];
		}
		else
		{
			return -1;
		}
	}
	void ControlType::SetString(String key, char* value)
	{
		txtData[key] = value;
	}
	void ControlType::SetInt(String key, int value)
	{
		intData[key] = value;
	}
	void ControlType::AddBoundingBox(BoundingBox aBB)
	{
		Serial.print(F("\tAdding BB named "));
		Serial.print(aBB.Name());
		Serial.print(F(" to CT: "));
		Serial.print(Name());
		myCE_BB.push_back(aBB);

		Serial.print(F(" Now there are "));
		Serial.print(myCE_BB.size());
		Serial.println(F(" BBs."));
	}
	void ControlType::AddTextElement(TextElement aTE)
	{
		Serial.print(F("\tAdding TE named "));
		Serial.print(aTE.Name());
		Serial.print(F(" to CT: "));
		Serial.print(Name());
		myCE_TE.push_back(aTE);

		Serial.print(F(" Now there are "));
		Serial.print(myCE_TE.size());
		Serial.println(F(" TEs."));
	}
}