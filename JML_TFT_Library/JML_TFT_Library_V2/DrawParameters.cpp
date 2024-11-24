//
//
//

#include "DrawParameters.h"

#include <algorithm>

namespace stsn = SeeedTouchScreenNamespace;
using namespace stsn;
class stsn::Point;

namespace JML_TFT_Library_V2
{
#pragma region Constructor
	DrawParameters::DrawParameters(
		const unsigned short aTop, const unsigned short aLeft,
		const unsigned short aHeight = defaultHeight, const unsigned short aWidth = defaultWidth,
		const unsigned short aForeGround = BLACK, const unsigned short  aBackground = WHITE) :
		mTop{ aTop }, mLeft{ aLeft }, mHeight{ aHeight }, mWidth{ aWidth },
		mForeground{ aForeGround }, mBackground{ aBackground }
	{
		Serial.print(F("Added DP: "));
		Serial.println(ToString());
	}
#pragma endregion Constructor
	/* COORDINATES ON PANEL

		(0,0) x ->			119		Max X (239,0)
	y	-----------------------------------------
	|	|										|
	v	|										|
		|				TOP						|
		|		.................				|
		| LEFT	:				: RIGHT			|
		|		:				:				|
		|		.................				|
		|			  BOTTOM					|
		|										|
		|										|
		|										|
	159	|										|
		|										|
		|										|
		|										|
		|										|
		|										|
		|										|
		|										|
		|										|
		|										|
		|										|
		-----------------------------------------
		(0,319) Max Y					(239,319)

	*/
#pragma region PropertyGetters
	int DrawParameters::Left() const { return mLeft; }
	int DrawParameters::Top() const { return mTop; }
	int DrawParameters::Width() const { return mWidth; }
	int DrawParameters::Height() const { return mHeight; }
	int DrawParameters::Right() const { return mLeft + mWidth; }
	int DrawParameters::Bottom() const { return mTop + mHeight; }
	int DrawParameters::Foreground() const { return mForeground; }
	int DrawParameters::Background() const { return mBackground; }
	const bool DrawParameters::IsValid() const
	{
		bool validX = (mLeft > 0) && (mLeft <= 240);
		bool validY = (mTop > 0) && (mTop <= 320);
		bool allValid = validX && validY;
		if (!allValid)
		{
			Serial.print(F("{Invalid left:"));
			Serial.print(mLeft);
			Serial.print(F("\ttop:"));
			Serial.print(mTop);
			Serial.println(F("}"));
		}
		else { Serial.print(F("v")); }
		return allValid;
	}
	bool DrawParameters::Contains(stsn::Point* aPoint) const
	{
		if (IsValid())
		{
			//Serial.print("Checking if point (" + (String)aPoint->x + ", " + (String)aPoint->y + ") is inside box. ");
			//"Left/Right: " + Left() + " <-> " + Right());

			//std::vector<int> x = std::minmax(Left(), Right());
			if (aPoint->x >= std::min(Left(), Right()) && aPoint->x <= std::max(Left(), Right()))
			{
				//Serial.println("  -- Yes, inside L/R Checking if point.y (" + (String)aPoint->y + ") is inside box. Bottom/Top: " + Bottom() + " <-> " + Top());

				if (aPoint->y >= std::min(Bottom(), Top()) && aPoint->y <= std::max(Bottom(), Top()))
				{
					//Serial.println(" -- Yes, inside Box.");

					return true;
				}
				else
				{
					//Serial.println(" -- No, NOT inside B/T.");
				}
			}
			else
			{
				//Serial.println("  -- No, NOT inside L/R.  Not testing B/T.");
			}
		}
		return false;
	}
	void DrawParameters::SetColor(unsigned short  aForeground, unsigned short  aBackground)
	{
		mForeground = aForeground;
		mBackground = aBackground;
	}
	String DrawParameters::ToString() const
	{
		String out = F("DrawParameters:");
		out.concat(F("\tL,R: ("));
		out.concat((String)Left());
		out.concat(F(", "));
		out.concat((String)Right());
		out.concat(F(")\tT,B ("));
		out.concat((String)Top());
		out.concat(F(", "));
		out.concat((String)Bottom());
		out.concat(F(")\tU,D ("));
		out.concat((String)Height());
		out.concat(F(", "));
		out.concat((String)Width());
		out.concat(F(")"));
		return out;
	}
	void DrawParameters::RollCall() const
	{
		Serial.print("\t\t\t\t");
		Serial.print(ToString());
	}
}