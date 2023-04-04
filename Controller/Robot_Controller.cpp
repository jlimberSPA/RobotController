
#include "Robot_Controller.h"
using namespace JML_TFT_Library;

namespace controller_namespace
{
	Robot_Controller::Robot_Controller() :
		mJoystick(PIN_JOY1_X, PIN_JOY1_Y), 
		mScreen(JML_TFT_Library::LCD_Panel_V2()), 
		mTouch(MainScreen().myTouchPanel()),
		//mXBee(JML_Robot_XBee_Radio_Library::Robot_XBee_Base()),
		mMotion(Robot_Motion_Library::Robot_Motion())
	{ 
	}

	// Property Accessors
	Robot_Controller::~Robot_Controller()									{}
	AlignedJoy Robot_Controller::MainJoystick()								{return mJoystick;}
	JML_TFT_Library::LCD_Panel_V2 Robot_Controller::MainScreen()			{return mScreen;}
	SeeedTouchScreen::TouchScreen Robot_Controller::MainTouchScreen()		{return mTouch;}
	//JML_Robot_XBee_Radio_Library::Robot_XBee_Base Robot_Controller::MainRadio()	{return mXBee;}
	Robot_Motion_Library::Robot_Motion Robot_Controller::Motion()			{return mMotion;}

	void Robot_Controller::ControllerSetup()
	{

		Setup_Serial();
		Setup_Main_Screen();
		Send_Robot_Commands();

	}

	void Robot_Controller::Setup_Serial()
	{
		Serial.begin(115200);
		while (!Serial);    // wait for the serial port to open
		Serial.println("Communication with Computer Established");
	}

	void Robot_Controller::Setup_Main_Screen()
	{
		TFT_BL_ON;                                  // turn on the background light
		Tft.TFTinit();                              //init TFT library

		int xPos = 35;
		int xInc = 35;

		JoystickPage = MainScreen().AddPage("Joystick");


											//Bottom, Left, Height, Width
		CalStatus = JoystickPage.AddButton("CalStatus", xPos, 10, 30, 50, "Cal", WHITE, CRIMSON, PushOptions::none);
		xPos += xInc;
		Cal_JS_Button = JoystickPage.AddButton("Calibrate Joystick", xPos, 10, 30, 230, "Calibrate Joystick", WHEAT, MIDNIGHT_BLUE, PushOptions::toggle, calJS_EHF);
		xPos += xInc;
		Disp_JS_Cal_Button = JoystickPage.AddButton("List Calibration", xPos, 10, 30, 230, "List Calibration", CORN_SILK, DARK_SLATE_GRAY, PushOptions::toggle, disp_JS_Cal_EHF);
		xPos += xInc;
		JoystickPage.AddButton("Switch X/Y", xPos, 10, 30, 230, "Switch X/Y", KHAKI, SADDLE_BROWN, PushOptions::select);
		xPos += xInc;
		Joystick_X = JoystickPage.AddButton("X: ", xPos, 20, 30, 100, "X: ", WHITE, MIDNIGHT_BLUE, PushOptions::none);
		Joystick_Y = JoystickPage.AddButton("Y: ", xPos, 130, 30, 100, "Y: ", WHITE, MAROON, PushOptions::none);
		xPos += xInc + 20;
		JS_Disp = JoystickPage.AddJoystickDisplay("JSD", xPos + 20, 90, "", WHITE, NAVY);

		Serial.println(JS_Disp.ToString());
	}

	void Robot_Controller::Send_Robot_Commands()
	{
		/**< \TODO Build Send_Robot_Commands */
	}

	/**
	 *  Main Arduino Loop for Robot Hand Robot_Controller.
	 * 
	 */
	void Robot_Controller::ControllerLoop()
	{
		Respond_to_Touch_Inputs();
		//Check_for_XBee_Data();
	}

	void Robot_Controller::Respond_to_Touch_Inputs()
	{
		SeeedTouchScreen::Point p = mTouch.getPoint();
		p.x = map(p.x, TS_MINX, TS_MAXX, 0, 240);
		p.y = map(p.y, TS_MINY, TS_MAXY, 0, 320);

		// we have some minimum pressure we consider 'valid'
		// pressure of 0 means no pressing!
		if (p.z > __PRESSURE) {
			ShowSerial.println(+"X = " + (String)p.x + "\tY = " + (String)p.y + "\tPressure = " + (String)p.z);
			Tft.fillCircle(p.x, p.y, 2000 / p.z, WHITE);
			MainScreen().Toggle(p);
		}

		uint16_t x = mJoystick.read(X);
		String xLbl = Joystick_X.Name();
		String xVal = String(x);
		xLbl.concat(xVal);
		Joystick_X.SetText(&xLbl[0]);
		Joystick_X.Draw();

		uint16_t y = mJoystick.read(Y);
		String yLbl = Joystick_Y.Name();
		String yVal = String(y);
		yLbl.concat(yVal);
		Joystick_Y.SetText(&yLbl[0]);
		Joystick_Y.Draw();

		float fX = (float)x;
		float fY = (float)y;
		JS_Disp.Draw();
		JS_Disp.DrawJS(fX, fY);
		delay(10);
	}

	//bool Robot_Controller::Check_for_XBee_Data()
	//{
	//	bool valid = MainRadio().readXbee();
	//	if (valid) {
	//		// TODO:  Read and Pass Motor Commands here
	//	}
	//	return false;
	//}

	/******************************************************************************
	 * EventHandler to Calibrate Joystick. Phase 1:  Start the joystick calibration in the center position. Leave the joystick centered.
	 * 
	 * Phase 2: Calibration of the axes at the extreme points (min end max for each axis).  Move the Joystick to its extreme travel in all directions.
	 * @returns bool indicating success of calibration
	 ******************************************************************************/
	bool Robot_Controller::CalibrateJoystick()
	{
		bool result = true;

		// JOYSTICK CALIBRATION Phase 1
		// Start the joystick calibration in the center position. Use this method only if the calibration of the axles is desired (axesCalibration).
		Serial.print("Center Joystick Calibration \n\nLeave the joystick in the centre position during the calibration\ntime which is set to ");
		Serial.print(TIME_CAL_1);
		Serial.println(" milliseconds.");
		delay(2000);
		Serial.println("Center Calibration started!");
		delay(500);
		/*
		 * To calibrate the joystick center point use "centerCalibration" method;
		 * objectname.middleCalibration(uint16_t timeOfCal).
		 * "timeOfCal" is the calibration time in milliseconds
		 */
		mJoystick.middleCalibration(TIME_CAL_1);
		Serial.println("Joystick Centered!\n\n\n");
		delay(2000);

		// JOYSTICK CALIBRATION Phase 2
		/*
		* Calibration of the axes at the extreme points (min end max for each axis).
		* It is recommended to rotate the joystick in a circular way along its circumference throughout
		* the calibration time.
		*/
		Serial.print("About to start axes Calibration... \n - Continually rotate the joystick in a circle around its circumference\nthroughout the calibration time (");
		Serial.print(TIME_CAL_2);
		Serial.println(" milliseconds).");
		delay(1000);
		Serial.println("Calibration started!");
		delay(250);
		/*
		 * To calibrate the joystick axes points use "axesCalibration" method (bool type);
		 * objectname.axesCalibration(uint16_t timeOfCal).
		 * "timeOfCal" is the calibration time in milliseconds.
		 */
		if (mJoystick.axesCalibration(TIME_CAL_2))
		{
			Serial.println("Calibration succesfully!!");
			//DispCal();
		}
		else
		{
			Serial.println("Calibration failed!!");
			result = false;
		}
		mJoystickCalibrated = result;
		Cal_JS_Button.UnSelect();

		if (result)
		{CalStatus.Select();}
		else
		{CalStatus.UnSelect();}
		return result;
	}
	bool Robot_Controller::DispCal()
	{
		if (mJoystickCalibrated)
		{
			// Print all points calibrated
    		/*
			 * You can use these values to save them to eeprom memory. In this way you will avoid requiring the joystick calibration at each boot time.
			 * To set the parameters read by eeprom you have to use the "setCalibratedPoint" method.
			 * If your project does not require the re-calibration of the joystick then you can make a sketch like this only to display the calibrated
			 * values to set them in the final project using the "setCalibratedPoint" method.
			 * To get the calibrated point values use getCalibratedPoint(axis_t axis, point_t point).
			 * The parameters: the labels of the "axis_t" shall be X and Y; the labels of "point_t" is MIN, MID and MAX.
			 */
			Serial.print("X min -> ");
			Serial.print(mJoystick.getCalibratedPoint(X, MIN));
			Serial.print(" | center ->  ");
			Serial.print(mJoystick.getCalibratedPoint(X, MID));
			Serial.print(" | max -> ");
			Serial.println(mJoystick.getCalibratedPoint(X, MAX));
			Serial.print("Y min -> ");
			Serial.print(mJoystick.getCalibratedPoint(Y, MIN));
			Serial.print(" | center ->  ");
			Serial.print(mJoystick.getCalibratedPoint(Y, MID));
			Serial.print(" | max -> ");
			Serial.println(mJoystick.getCalibratedPoint(Y, MAX));
		}
		else
		{
			Serial.println(" *** Joystick NOT calibrated yet ***");
		}
	}

	bool Robot_Controller::Switch_X_Y()
	{
		mJoystick.Switch_X_Y();
	}
	bool Robot_Controller::Reverse_X()
	{
		mJoystick.Reverse_X();
	}
	bool Robot_Controller::Reverse_Y()
	{
		mJoystick.Reverse_Y();
	}
}
