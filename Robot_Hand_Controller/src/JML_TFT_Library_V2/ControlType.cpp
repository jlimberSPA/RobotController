//
//
//

#include "ControlType.h"

namespace JML_TFT_Library_V2
{
	//using BoundingBox;
	class BoundingBox;
	class ControlType;

	ControlType& ControlTypeFactory::Build(ControlTypes aCT, DrawParameters& aDP,
		EventHandlerFunction aEHF = nullptr)
	{
		if (aCT == ControlTypes::TextBox)
		{
			// Create the ControlType Object
			ControlType& newCT = ControlType::ControlTypeRef(aDP);
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
			ControlType& newCT = ControlType::ControlTypeRef(aDP);
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
	ControlType::ControlType(const DrawParameters& aDP) : mDP{ aDP }
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
		String StringOut = "";
		for (auto ce : myControlElements)
		{
			StringOut += ce.ToString();
		}
		return StringOut;
	}
	bool ControlType::IsValid()
	{
		bool valid = mDP.IsValid();
		if (valid)
		{
			for (auto ce : myControlElements)
			{
				valid &= ce.IsValid();
			}
		}
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
		myControlElements.push_back(aCE);
	}
}