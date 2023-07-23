//
//
//

#include "ControlType.h"

namespace JML_TFT_Library_V2
{
	//using BoundingBox;
	class BoundingBox;
	class ControlType;

	ControlType& ControlTypeFactory::Build(char* aName, ControlTypes aCT, DrawParameters& aDP,
		EventHandlerFunction aEHF = nullptr)
	{
		if (aCT == ControlTypes::TextBox)
		{
			// Create the ControlType Object
			ControlType& newCT = ControlType::ControlTypeRef(aName, aDP);
			newCT.myType = ControlTypes::TextBox;

			// Add the Bounding Box
			BoundingBox mBB = BoundingBox(aDP, newCT);
			newCT.AddControlElement(mBB);

			// Add the Text Element
			TextElement mTE = TextElement((char*)' ', aDP, newCT);
			newCT.AddControlElement(mTE);
			mTE.SetKey('Text' + (String)newCT.StringListSize());
			newCT.SetString('Text' + (String)newCT.StringListSize(), "");
		}
		else if (aCT == ControlTypes::Button)
		{
			// Create the ControlType Object
			ControlType& newCT = ControlType::ControlTypeRef(aName, aDP);
			newCT.myType = ControlTypes::TextBox;

			// Add the Bounding Box
			BoundingBox mBB = BoundingBox(aDP, newCT, aEHF);
			newCT.AddControlElement(mBB);

			// Add the Text Element
			TextElement mTE = TextElement((char*)' ', aDP, newCT);
			newCT.AddControlElement(mTE);
			mTE.SetKey('Btn' + (String)newCT.StringListSize());
			newCT.SetString('Btn' + (String)newCT.StringListSize(), "");
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
		for (auto ce : myControlElements)
		{
			ce.Draw();
		}
	}
	String ControlType::ToString() const
	{
		String StringOut = (String)mName + " with :";
		for (auto ce : myControlElements)
		{
			StringOut += ce.ToString();
		}
		return StringOut;
	}
	bool ControlType::IsValid()
	{
		Serial.println((String)mName);
		Serial.print("[(ControlType:" + (String)Name() + " " +
			(String)myControlElements.size() + ") DP:");
		bool valid = mDP.IsValid();
		String out = " (Invalid DP)]";
		if (valid)
		{
			out = "(Valid DP, ";
			for (auto ce : myControlElements)
			{
				valid &= ce.IsValid();
			}
			out = valid + (valid ? "Ctls Valid)]" : "Ctls Invalid)]#");
		}
		if (!valid) { Serial.print(out); }
		return valid;
	}
	char* ControlType::GetString(String key)
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
	void ControlType::AddControlElement(ControlElement& aCE)
	{
		Serial.print("Adding CE to ");
		Serial.println((String)mName);
		myControlElements.push_back(aCE);
	}
}