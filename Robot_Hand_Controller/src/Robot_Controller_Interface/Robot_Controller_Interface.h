// Robot_Controller_Interface.h

#ifndef _Robot_Controller_Interface_h
#define _Robot_Controller_Interface_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

//#include "../JML_TFT_Library/JML_TFT_Library.h"
#ifndef __ARRAY__
#include <array>
#endif
#ifndef __STD_HEADER_VECTOR
#include <vector>
#endif
#ifndef _ALIGNED_JOY_h
#include <AlignedJoy.h>
#endif
#ifndef _JML_ROBOT_MOTION_LIBRARY_h
#include <JML_Robot_Motion_Library.h>
#endif
#ifndef TFTv2_h
#include <TFTv2.h>
#endif
#ifndef SeeedTouchScreen
#include <SeeedTouchScreen.h>
#endif
#ifndef _JML_TFT_LIBRARY_h
#include "../JML_TFT_Library_V2/JML_TFT_Library_V2.h"
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

using namespace JML_TFT_Library_V2;

class Robot_Controller_Interface
{
public:
	Robot_Controller_Interface();	/*\brief Constructor */
	~Robot_Controller_Interface();	/*\brief Destructor */
	// char array to print to the screen
	char sensorPrintout[6];

	// Properties
	//AlignedJoy MainJoystick();		/**< Access to the Joystick on the Controller */
	LCD_Panel_V2& MainScreen();		/**< Access to the Display on the Controller */
	//JML_Robot_XBee_Radio_Library::Robot_XBee_Base MainRadio();
	//Robot_Motion_Library::Robot_Motion Motion();

	/* Fuctions for Core Arduino Code */
	void ControllerSetup();	/**< Called from controller.ino setup() */
	void ControllerLoop();  /**< Called from controller.ino loop() */

	//bool CalibrateJoystick(); /**< Calibrates center and X/Y extremes */
	//bool DispCal();  /**< Outputs calibration to the computer via serial */
	//bool Switch_X_Y(); /**< \todo Switch the X and Y Axis */
	//bool Reverse_X();  /**< \todo Switch the positive and negative direction of the X Axis */
	//bool Reverse_Y();  /**< \todo Switch the positive and negative direction of the Y Axis */

	Page* JoystickPage;			/**< Page to hold Joystick calibration and status */

	//Button* CalStatus;			/**< Display current calibration status */
	//Button* Cal_JS_Button;		/**< Start joystick calibration */
	//Button* Disp_JS_Cal_Button; /**< Outputs calibration to the computer via serial */
	//TextBox Joystick_X;			/**< Display current joystick X Postion */
	//TextBox Joystick_Y;			/**< Display current joystick Y Postion */
//	JoystickDisplayControl* JS_Disp;  /**< Graphic showing vector to current joystick X,Y Postion */

	JML_TFT_Library_V2::Page* ConsolePage;				/**< Page to hold console output */
	//TextPanel* ConsoleOut;		/**< Text Panel to display console output */

protected:
	// Fields
	/// These EventHandlerFunctions help connect local function pointers to the function pointers in JML_TFT_Library
	//EventHandlerFunction calJS_EHF = (EventHandlerFunction)&Robot_Controller_Interface::CalibrateJoystick;
	//EventHandlerFunction disp_JS_Cal_EHF = (EventHandlerFunction)&Robot_Controller_Interface::DispCal;

	//AlignedJoy mJoystick;								/**< Joystick Object reference  */
	LCD_Panel_V2 mScreen = LCD_Panel_V2(); //  = LCD_Panel_V2();				/**< Display Object reference  */

	//bool mJoystickCalibrated = false;
	//Robot_Motion_Library::Robot_Motion mMotion;			/**< Robot_Motion Object reference  */

	static const INT16U _SerialSpeed = 14400;
	unsigned long _nextRedraw = 0;
	static const unsigned long _redrawInterval = 500;

	// Methods
	void Setup_Serial_Interface();
	void Setup_Main_Screen();
	void CreateJoystickPage();
	void CreateConsolePage();
	void Respond_to_Touch_Inputs();
	//void Read_Joystick_Input();
	double mapRange(double a1, double a2, double b1, double b2, double s);
	//bool Check_for_XBee_Data();

	//void Send_Robot_Commands();
};

#endif
