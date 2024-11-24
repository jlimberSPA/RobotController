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

	ControlType* ControlTypeFactory::Build(const char* aName, const ControlTypes aCT, const DrawParameters& aDP,
		EventHandlerFunction aEHF = nullptr)
	{
		if (aCT == ControlTypes::TextBox)
		{
			// Create the ControlType Object
			ControlType* newCT = &ControlType(aName, aCT, aDP);

			// Add the Bounding Box
			auto mBB = BoundingBox(aDP, newCT);
			newCT->AddBoundingBox(mBB);

			// Add the Text Element
			auto mTE = TextElement((char*)' ', aDP, newCT);
			newCT->AddTextElement(mTE);
			char key[128];
			strcat_s(key, "Text");
			int keyNum = newCT->StringListSize();
			char keyStr[128];
			_itoa_s(keyNum, keyStr, 128, 10);
			strcat_s(key, keyStr);
			mTE.SetKey(key);
			newCT->SetString(key, "Default Text");

			PseudoSerial::print(F("Created new CT in Factory. name param: "));
			PseudoSerial::print(aName);
			PseudoSerial::print(F(" has name: "));
			PseudoSerial::println(newCT->Name());
			PseudoSerial::print(F("\tDP Param:"));
			PseudoSerial::println(aDP.ToString());
			PseudoSerial::print(F("\tBounding Box:"));
			PseudoSerial::print(mBB.ToString());
			PseudoSerial::print(F(" DP: "));
			PseudoSerial::println(mBB.DP().ToString());
			PseudoSerial::print(F("\tText Element:"));
			PseudoSerial::print(mTE.ToString());
			PseudoSerial::print(F(" DP: "));
			PseudoSerial::println(mTE.DP().ToString());

			PseudoSerial::println(F("\tFactory Roll Call:"));
			newCT->RollCall();
			PseudoSerial::print(F("\t"));
			RAMCheck::display_freeram();
			PseudoSerial::println(F("\t---------"));
			return newCT;
		}
		else if (aCT == ControlTypes::Button)
		{
			// Create the ControlType Object
			ControlType* newCT = ControlType::ControlTypePtr(aName, aDP);
			newCT->myType = ControlTypes::TextBox;

			// Add the Bounding Box
			auto mBB = BoundingBox(aDP, newCT, aEHF);
			newCT->AddBoundingBox(mBB);

			// Add the Text Element
			auto mTE = TextElement((char*)' ', aDP, newCT);
			newCT->AddTextElement(mTE);
			mTE.SetKey('Btn' + (char*)newCT->StringListSize());
			newCT->SetString('Btn' + (char*)newCT->StringListSize(), "");
			return newCT;
		}
		else if (aCT == ControlTypes::TextPanel)
		{ // TODO
		}
		else if (aCT == ControlTypes::JSD)
		{ // TODO
		}
	}
	ControlType::ControlType(const char* aName, const DrawParameters& aDP) :
		mDP{ aDP }, mName{ aName }
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
	char* ControlType::ToString() const
	{
		char out[128] = "Control Type: ";
		strcat_s(out, (const char*)(uint8_t)myType);
		strcat_s(out, " ");
		strcat_s(out, Name());
		return out;
	}
	void ControlType::RollCall() const
	{
		auto sz = myCE_BB.size();
		sz += myCE_TE.size();
		PseudoSerial::print(F("\t\t-"));
		PseudoSerial::print(ToString());
		PseudoSerial::print(F(" with "));
		PseudoSerial::print(sz);
		PseudoSerial::println(F(" ControlElements"));
		for (BoundingBox bb : myCE_BB)
		{
			bb.RollCall();
		}
		for (TextElement te : myCE_TE)
		{
			te.RollCall();
		}
		PseudoSerial::print(F("\t\t Finished "));
		PseudoSerial::println(ToString());
	}
	bool ControlType::IsValid() const
	{
		//PseudoSerial::println((char*)mName);
		//PseudoSerial::print("[(ControlType:" + (char*)Name() + " " +
		//	(char*)myControlElements.size() + ") DP:");
		bool valid = mDP.IsValid();
		//char* out = " (Invalid DP)]";
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
		//if (!valid) { PseudoSerial::print(out); }
		return valid;
	}
	char* ControlType::GetString(char* key) const
	{
		if (txtData.find(key) != txtData.end())
		{
			return txtData[key];
		}
		else
		{
			return '\0';
		}
	}
	int ControlType::GetInt(char* key)
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
	void ControlType::SetString(char* key, const char* value)
	{
		txtData[key] = value;
	}
	void ControlType::SetInt(char* key, int value)
	{
		intData[key] = value;
	}
	void ControlType::AddBoundingBox(BoundingBox const& aBB)
	{
		PseudoSerial::print(F("\tAdding BB named "));
		PseudoSerial::print(aBB.Name());
		PseudoSerial::print(F(" to CT: "));
		PseudoSerial::print(Name());
		myCE_BB.push_back(aBB);

		PseudoSerial::print(F(" Now there are "));
		PseudoSerial::print(myCE_BB.size());
		PseudoSerial::println(F(" BBs."));
	}
	void ControlType::AddTextElement(TextElement const& aTE)
	{
		PseudoSerial::print(F("\tAdding TE named "));
		PseudoSerial::print(aTE.Name());
		PseudoSerial::print(F(" to CT: "));
		PseudoSerial::print(Name());
		myCE_TE.push_back(aTE);

		PseudoSerial::print(F(" Now there are "));
		PseudoSerial::print(myCE_TE.size());
		PseudoSerial::println(F(" TEs."));
	}
}