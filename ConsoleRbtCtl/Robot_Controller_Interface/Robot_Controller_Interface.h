// Robot_Controller_Interface.h

#ifndef _Robot_Controller_Interface_h
#define _Robot_Controller_Interface_h

#include <iostream>
#include <chrono>
#include <ctime>

#ifndef __STD_HEADER_VECTOR
#include <vector>
#endif

#include "../PseudoSerial.h"

#ifndef _JML_TFT_LIBRARY_h
#include "../JML_TFT_Library_V2/JML_TFT_Library_V2.h"
#endif

using namespace JML_TFT_Library_V2;

class Robot_Controller_Interface
{
public:
	Robot_Controller_Interface();	/*\brief Constructor */
	~Robot_Controller_Interface();	/*\brief Destructor */

	// char array to print to the screen
	LCD_Panel_V2& MainScreen();		/**< Access to the Display on the Controller */

	// Properties
	/* Fuctions for Core Arduino Code */
	void ControllerSetup();	/**< Called from controller.ino setup() */
	void ControllerLoop();  /**< Called from controller.ino loop() */

	//bool CalibrateJoystick(); /**< Calibrates center and X/Y extremes */
	//bool DispCal();  /**< Outputs calibration to the computer via serial */
	//bool Switch_X_Y(); /**< \todo Switch the X and Y Axis */
	//bool Reverse_X();  /**< \todo Switch the positive and negative direction of the X Axis */
	//bool Reverse_Y();  /**< \todo Switch the positive and negative direction of the Y Axis */

	Page* JoystickPage;			/**< Page to hold Joystick calibration and status */
	JML_TFT_Library_V2::Page* ConsolePage;				/**< Page to hold console output */

protected:
	// Fields

	std::chrono::milliseconds _redrawInterval = std::chrono::milliseconds(50);

	// Methods
	void Setup_Serial_Interface();
	void Setup_Main_Screen();
	void CreateJoystickPage();
	void CreateConsolePage();
	void Respond_to_Touch_Inputs();
	double mapRange(double a1, double a2, double b1, double b2, double s);
	// These EventHandlerFunctions help connect local function pointers to the function pointers in JML_TFT_Library
	//EventHandlerFunction calJS_EHF = (EventHandlerFunction)&Robot_Controller_Interface::CalibrateJoystick;
	//EventHandlerFunction disp_JS_Cal_EHF = (EventHandlerFunction)&Robot_Controller_Interface::DispCal;
	//AlignedJoy mJoystick;								/**< Joystick Object reference  */
	//bool mJoystickCalibrated = false;
	//Robot_Motion_Library::Robot_Motion mMotion;			/**< Robot_Motion Object reference  */
	//void Read_Joystick_Input();
	//bool Check_for_XBee_Data();
	//void Send_Robot_Commands();
private:
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
	LCD_Panel_V2 mScreen = LCD_Panel_V2(); //  = LCD_Panel_V2();				/**< Display Object reference  */
};

#endif
