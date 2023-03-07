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

		AlignedJoy joystick_1 = AlignedJoy(PIN_JOY1_X, PIN_JOY1_Y); /*! Class Constructor for New Joystick Object*/
		JML_TFT_Library::LCD_Panel_V2 screen;

		SeeedTouchScreen::TouchScreen myTouch = (SeeedTouchScreen::TouchScreen)screen.myTouchPanel();
		JML_TFT_Library::Button btn = JML_TFT_Library::Button();

		/* Fuctions for Core Arduino Code */
		void ControllerSetup();	/**< Called from controller.ino setup() */
		void ControllerLoop();  /**< Called from controller.ino loop() */
		
		bool CalibrateJoystick(); /**< Calibrates center and X/Y extremes */
		bool DispCal();  /**< Outputs calibration to the computer via serial */
		bool Switch_X_Y(); /**< \todo Switch the X and Y Axis */
		bool Reverse_X();  /**< \todo Switch the positive and negative direction of the X Axis */
		bool Reverse_Y();  /**< \todo Switch the positive and negative direction of the Y Axis */

		JML_TFT_Library::Button CalStatus;			/**< Display current calibration status */
		JML_TFT_Library::Button Cal_JS_Button;		/**< Start joystick calibration */
		JML_TFT_Library::Button Disp_JS_Cal_Button;  /**< Outputs calibration to the computer via serial */
		JML_TFT_Library::Button Joystick_X;			/**< Display current joystick X Postion */
		JML_TFT_Library::Button Joystick_Y;			/**< Display current joystick Y Postion */
		JML_TFT_Library::JoystickDisplayControl JS_Disp;  /**< Graphic showing vector to current joystick X,Y Postion */

	private:
		/// These typedef helps connect local function pointers to the function pointers
		/// in JML_TFT_Library
		EventHandlerFunction calJS_EHF = (EventHandlerFunction)&CalibrateJoystick;
		EventHandlerFunction disp_JS_Cal_EHF = (EventHandlerFunction)&DispCal;

		bool mJoystickCalibrated = false;
	};
}
