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

#ifndef JML_TFT_INTERFACE_h
	#include <JML_TFT_Interface.h>
#endif // !JML_TFT_INTERFACE_h


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
/**
 * \brief Namespace for the Robot Robot_Controller Class.
 */
using namespace JML_TFT_Interface;
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
		LCD_Panel_V2 screen;

		SeeedTouchScreen::TouchScreen myTouch = (SeeedTouchScreen::TouchScreen)screen.myTouchPanel();;
		Button btn = JML_TFT_Interface::Button();

		/* Fuctions for Core Arduino Code */
		void ControllerSetup();
		void ControllerLoop();
		
		/**
		 * \brief Button Callback Functions.
		 * 
		 * \return 
		 */
		bool CalibrateJoystick();
		bool DisplayJoysticCalibration();
		bool Switch_X_Y();
		bool Reverse_X();
		bool Reverse_Y();

		/**
		 * \brief Button Declarations.
		 */
		Button CalStatus;
		Button Cal_JS_Button;
		Button Disp_JS_Cal_Button;
		Button Joystick_X;
		Button Joystick_Y;
		JoystickDisplayControl JS_Disp;

	private:
		// This typedef helps connect local function pointers to the function pointers
		// in JML_TFT_Interface
		EventHandlerFunction calJS_EHF = (EventHandlerFunction)&CalibrateJoystick;
		EventHandlerFunction disp_JS_Cal_EHF = (EventHandlerFunction)&DisplayJoysticCalibration;

		bool mJoystickCalibrated = false;
	};
}
