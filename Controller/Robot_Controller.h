// Robot_Controller.h
/*****************************************************************//**
 * \file   $FILENAME
 * \brief  $BRIEF$END
 *
 * \author $USERNAME
 * \date   $MONTHNAME_EN $YEAR
 *********************************************************************/

#ifndef _CONTROLLER_h
#define _CONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
		#ifndef Arduino_h
			#include "arduino.h"
		#endif // !Arduino_h
	#else
		#include "WProgram.h"
	#endif
#endif

#include <AlignedJoy.h>
#include <JML_TFT_Library.h>
#include <JML_Robot_Motion_Library.h>
//#include <JML_Robot_XBee_Radio_Library.h>

using namespace JML_TFT_Library;

 /// SETUP AlignedJoy Joystick

 // PINs DEFINITION
 // joystick 1
#define PIN_JOY1_X   8  //(up  down)
#define PIN_JOY1_Y   9  //(left  right)
// TIMERs DEFINITION
// joystick calibration
#define TIME_CAL_1 2000
#define TIME_CAL_2 10000


#define ShowSerial Serial

namespace controller_namespace
{

	/**
	 * \brief Robot Robot_Controller Class.
	 */
	class Robot_Controller
	{
	public:
		Robot_Controller();	/*\brief Constructor */
		~Robot_Controller();	/*\brief Destructor */
		// char array to print to the screen
		char sensorPrintout[6];

		// Properties
		AlignedJoy MainJoystick();							/**< Access to the Joystick on the Controller */
		JML_TFT_Library::LCD_Panel_V2 MainScreen();			/**< Access to the Display on the Controller */
		SeeedTouchScreen::TouchScreen MainTouchScreen();	/**< Access to the Touch Screen on the Controller */
		//JML_Robot_XBee_Radio_Library::Robot_XBee_Base MainRadio();
		Robot_Motion_Library::Robot_Motion Motion();

		/* Fuctions for Core Arduino Code */
		void ControllerSetup();	/**< Called from controller.ino setup() */
		void ControllerLoop();  /**< Called from controller.ino loop() */
		
		bool CalibrateJoystick(); /**< Calibrates center and X/Y extremes */
		bool DispCal();  /**< Outputs calibration to the computer via serial */
		bool Switch_X_Y(); /**< \todo Switch the X and Y Axis */
		bool Reverse_X();  /**< \todo Switch the positive and negative direction of the X Axis */
		bool Reverse_Y();  /**< \todo Switch the positive and negative direction of the Y Axis */

		JML_TFT_Library::Page* JoystickPage;			/**< Page to hold Joystick calibration and status */
		JML_TFT_Library::Button CalStatus;			/**< Display current calibration status */
		JML_TFT_Library::Button Cal_JS_Button;		/**< Start joystick calibration */
		JML_TFT_Library::Button Disp_JS_Cal_Button; /**< Outputs calibration to the computer via serial */
		JML_TFT_Library::Button Joystick_X;			/**< Display current joystick X Postion */
		JML_TFT_Library::Button Joystick_Y;			/**< Display current joystick Y Postion */
		JML_TFT_Library::JoystickDisplayControl JS_Disp;  /**< Graphic showing vector to current joystick X,Y Postion */

		JML_TFT_Library::Page* ConsolePage;				/**< Page to hold console output */
		JML_TFT_Library::TextPanel ConsoleOut;		/**< Text Panel to display console output */

	private:
		// Fields
		/// These EventHandlerFunctions help connect local function pointers to the function pointers in JML_TFT_Library
		EventHandlerFunction calJS_EHF = (EventHandlerFunction)&CalibrateJoystick;
		EventHandlerFunction disp_JS_Cal_EHF = (EventHandlerFunction)&DispCal;
		AlignedJoy mJoystick;								/**< Joystick Object reference  */
		JML_TFT_Library::LCD_Panel_V2 mScreen;				/**< Display Object reference  */
		SeeedTouchScreen::TouchScreen mTouch;				/**< Touch Screen Object reference  */
		bool mJoystickCalibrated = false;
		//JML_Robot_XBee_Radio_Library::Robot_XBee_Base mXBee;		/**< XBee Object reference  */
		Robot_Motion_Library::Robot_Motion mMotion;			/**< Robot_Motion Object reference  */
		// Methods
		void Respond_to_Touch_Inputs();
		//bool Check_for_XBee_Data();
		void Setup_Serial();
		void Setup_Main_Screen();
		void Send_Robot_Commands();
	};
}
