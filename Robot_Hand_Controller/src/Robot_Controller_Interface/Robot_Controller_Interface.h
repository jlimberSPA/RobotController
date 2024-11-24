// Robot_Controller_Interface.h

#ifndef _Robot_Controller_Interface_h
#define _Robot_Controller_Interface_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#ifndef _RAMCHECK_h
#include "../../JML_TFT_Library/JML_TFT_Library_V2/RAMCheck.h"
#endif

#ifndef __ARRAY__
#include <array>
#endif

/// Restore when ready to use joystick
//#ifndef _ALIGNED_JOY_h
//#include <AlignedJoy.h>
//#endif

/// Restore when ready to move robot
//#ifndef _JML_ROBOT_MOTION_LIBRARY_h
//#include <JML_Robot_Motion_Library.h>
//#endif

/// If the ScreenTemplate is done correctly it should
/// Encapsulate the next two libraries
//#ifndef TFTv2_h
//#include <TFTv2.h>
//#endif
//#ifndef SeeedTouchScreen
//#include <SeeedTouchScreen.h>
//#endif

#ifndef _JML_TFT_LIBRARY_h
#include "../../JML_TFT_Library/JML_TFT_Library_V2/JML_TFT_Library_V2.h"
using namespace JML_TFT_Library_V2;
#endif

/// SETUP AlignedJoy Joystick

// PINs DEFINITION
// joystick 1
#define PIN_JOY1_X   8  //(up  down)
#define PIN_JOY1_Y   9  //(left  right)
// TIMERs DEFINITION
// joystick calibration
#define TIME_CAL_1 2000
#define TIME_CAL_2 10000

namespace Robot_Controller_Interface
{
	class Robot_Controller_Interface
	{
	public:
		Robot_Controller_Interface();	/*\brief Constructor */
		~Robot_Controller_Interface();	/*\brief Destructor */
		// char array to print to the screen
		char sensorPrintout[6];

		// Properties
		LCD_Panel_V2* MainScreen();		/**< Access to the Display on the Controller */
		TFT_Screen* myTFT = new TFT_Screen();
		/* functions for Core Arduino Code */
		void ControllerSetup();	/**< Called from controller.ino setup() */
		void ControllerLoop();  /**< Called from controller.ino loop() */

	protected:
		LCD_Panel_V2* mScreen = LCD_Panel_V2::GetInstance();	/**< Display Object reference  */

		static const INT16U _SerialSpeed = 57600;
		unsigned long _nextRedraw = 0;
		static const unsigned long _redrawInterval = 50;

		// Methods
		void Setup_Serial_Interface();
		void Setup_Main_Screen();
		void CreateJoystickPage();
		void CreateConsolePage();
		void Respond_to_Touch_Inputs();
		double mapRange(double a1, double a2, double b1, double b2, double s);
	};
}

#endif
