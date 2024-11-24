#pragma once
#include "DrawParameters.h"
#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else

#endif
class __FlashStringHelper;
#include "JML_TFT_Library_V2.h"
class String;

namespace JML_TFT_Library_V2
{   // Forward declaration of LCD_Panel_V2for use in Page Class
	class LCD_Panel_V2;
	class Page
	{
	public:
		Page() = delete;
		Page(char* aName, LCD_Panel_V2* aPanel);
		Page(const __FlashStringHelper* aName, LCD_Panel_V2* aPanel);
		~Page() = default;

		// Property Accessors
		const __FlashStringHelper* Name() const { return mName; }

		// Methods:
		void AddTextBox(const char* aName, const DrawParameters& aDP, const char* aTxt);
		void AddTextBox(const __FlashStringHelper* aName, const DrawParameters& aDP, const __FlashStringHelper* aTxt);

		void AddButton(const char* aName, const DrawParameters& aDP, const char* aTxt, EventHandlerFunction aEHF);
		void AddButton(const __FlashStringHelper* aName, const DrawParameters& aDP, const __FlashStringHelper* aTxt, EventHandlerFunction aEHF);

		String ToString() const;
		void RollCall();

		//		void AddToAutoRefreshList(IControlType& aCtl);
		void Refresh() const;
		void DrawAll() const;
		void SetActive() const;
		void HandleTouch(stsn::Point& aPoint);

	private:

		// Backing Fields
		int mControlCt;

		const __FlashStringHelper* mName;
		LCD_Panel_V2* mParentLCD;
		int mHeaderHt = 10;
		int mFooterHt = 30;

		// explanation of template at https://stackoverflow.com/questions/11843369/how-to-solve-the-error-expression-must-be-a-modifiable-lvalue-in-c

		template <typename T, int N>
		struct ControlArray {
			T controls[N];
			int sz = N;
		};
		ControlArray<IControlType*, 10>* mPageControls = new ControlArray<IControlType*, 10>();

		// std::vector<IControlType*>();
		//Map<String, IControlType*> mapControls = CMap<String, IControlType*>();

		IControlType* GetByPoint(stsn::Point& aPoint);
		//void Page::Update(std::vector<ControlElement&>& aControlList);
	};
}
