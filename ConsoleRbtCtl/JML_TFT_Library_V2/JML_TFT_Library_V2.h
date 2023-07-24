#ifndef _JML_TFT_LIBRARY_h
#define _JML_TFT_LIBRARY_h

#ifndef __HEADER_CSTDLIB
#include <cstdlib>
#endif
#ifndef _STDLIB_H_
#include <stdlib.h>
#endif
#ifndef __HEADER_TYPE_TRAITS
#include <type_traits>
#endif
#ifndef _GCC_WRAP_STDINT_H
#include <stdint.h>
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
#ifndef _CONTROLTYPE_h
#include "ControlType.h"
#endif
#ifndef _TFT_COLORS_h
#include "JML_TFT_Colors.h"
#endif

namespace JML_TFT_Library_V2
{
	// EventHandlerFunction is a Generic function definition that will be used with function pointers
	// It will allow each button to be assigned a specific callback function to call when pressed

	class Page
	{
	public:
		Page() = delete;
		Page(char* aName);
		~Page() = default;

		// Property Accessors
		char* Name() const { return (char*)mName; }

		// Methods:
		ControlType* AddTextBox(const char* aName, DrawParameters& aDP, const char* aTxt);
		ControlType* AddButton(const char* aName, DrawParameters& aDP, const char* aTxt, EventHandlerFunction aEHF);

		char* ToString() const;
		void RollCall() const;

		void Refresh() const;
		void DrawAll() const;
		void SetActive();

		//void HandleTouch(stsn::Point& aPoint);

	private:

		// Backing Fields
		char* mName;
		int mHeaderHt = 10;
		int mFooterHt = 30;
		DrawParameters mDPtitle;
		DrawParameters mDPnext;
		DrawParameters mDPprevious;
		ControlType* mTitle;
		//ControlType& mNextPg;
		//ControlType& mPreviousPg;

		std::vector<ControlType*> mPageControls = std::vector<ControlType*>();
		ControlType* GetByPoint(stsn::Point& aPoint);
		//void Page::Update(std::vector<ControlElement&>& aControlList);
	};

	class LCD_Panel_V2
	{
	public:
		LCD_Panel_V2() {};
		~LCD_Panel_V2() = default;

		// Property Getters
		Page* GetActivePage() { return mActivePage; }
		Page* AddPage(const char* aName);

		//TFT* myScreen;
		//Page GetPage(int idx);
		//char* PageCount();
		//char* ToString();
		//static int _pageCount;

		// Methods
		void SetActivePage(Page* aPage);
		void RollCall() const;
		//void Select(stsn::Point aPoint);
		void Toggle(stsn::Point aPoint);
		//void Select(char* aName);
		//void Toggle(char* aName);
		//void Push(stsn::Point aPoint);

		//void FullRefresh();
		void ReDraw()
		{
			GetActivePage()->Refresh();
		};
		bool NextPage();
		bool LastPage();
	private:
		//void SetActivePage(Page* aPage);

		// Private Methods for EventHandlers

		EventHandlerFunction nextPg_EHF = (EventHandlerFunction)&JML_TFT_Library_V2::LCD_Panel_V2::NextPage;
		EventHandlerFunction lastPG_EHF = (EventHandlerFunction)&JML_TFT_Library_V2::LCD_Panel_V2::LastPage;

		// Backing Fields
		std::vector<Page*> mPages;
		std::vector<Page*>::iterator mPage_Iter;
		Page* mActivePage;

		stsn::TouchScreen myTouchPanel =
			stsn::TouchScreen(XP, YP, XM, YM);
	};
}
#endif