
#include "Robot_Controller.h"
using namespace JML_TFT_Library;
#define NO_DEBUG
namespace controller_namespace
{
	Robot_Controller::Robot_Controller() :
		mJoystick(PIN_JOY1_X, PIN_JOY1_Y), 
		mScreen(JML_TFT_Library::LCD_Panel_V2()),
		MainScreen(&mScreen),
		mTouch(MainScreen->myTouchPanel()),
		//mXBee(JML_Robot_XBee_Radio_Library::Robot_XBee_Base()),
		mMotion(Robot_Motion_Library::Robot_Motion())
	{ 
	}
	Robot_Controller::~Robot_Controller() {}

	// Property Accessors
	AlignedJoy Robot_Controller::MainJoystick()								{return mJoystick;}
	//JML_TFT_Library::LCD_Panel_V2 Robot_Controller::MainScreen()			{return mScreen;}
	SeeedTouchScreen::TouchScreen Robot_Controller::MainTouchScreen()		{return mTouch;}
	//JML_Robot_XBee_Radio_Library::Robot_XBee_Base Robot_Controller::MainRadio()	{return mXBee;}
	Robot_Motion_Library::Robot_Motion Robot_Controller::Motion()			{return mMotion;}

	void Robot_Controller::ControllerSetup()
	{

		Setup_Serial();
		Serial.println("\nStarting Robot Controller");
		
		Serial.println("\nAbout to call Screen constructor");
		mScreen = JML_TFT_Library::LCD_Panel_V2();

		Setup_Main_Screen();
		Send_Robot_Commands();

	}

	void Robot_Controller::Setup_Serial()
	{
		Serial.begin(14400);
		while (!Serial);    // wait for the serial port to open
		delay(1000);
		Serial.println("Communication with Computer Established");
	}

	void Robot_Controller::Setup_Main_Screen()
	{
		TFT_BL_ON;                                  // turn on the background light
		//Tft.TFTinit();                              //init TFT library
		TFT().TFTinit();
		Serial.println("\nAbout to call Screen constructor");
		mScreen = JML_TFT_Library::LCD_Panel_V2();

		CreateJoystickPage();
		CreateConsolePage();

		MainScreen->SetActivePage(&JoystickPage);

		Serial.println("\n\n\n ---------- Summary of LCD Panel Pages and Controls -----------");
		Serial.println(MainScreen->ToString());
	}

	void Robot_Controller::CreateJoystickPage()
	{
		int xPos = 35;
		int xInc = 35;

		Serial.println("\n\n[Screen Object constructed]\n\nStarting Page Setup.\n\t- TFT has [" +
			MainScreen->PageCount() + (String)"].\n\t- About to add Joystick Page");
		MainScreen->AddPage("Joystick");
		JoystickPage = MainScreen->GetPage(0);
		Serial.println("\t- Added " + (String)JoystickPage.Name() + " Page.  TFT has [" + MainScreen->PageCount() + "] pages");

		//Top, Left, Height, Width
		CalStatus = JoystickPage.AddButton("CalStatus", xPos, 10, 30, 50, "Cal", WHITE, CRIMSON, PushOptions::none);
		xPos += xInc;
		Cal_JS_Button = JoystickPage.AddButton("Calibrate Joystick", xPos, 10, 30, 230, "Calibrate Joystick", WHEAT, MIDNIGHT_BLUE, PushOptions::toggle, calJS_EHF);
		xPos += xInc;
		Disp_JS_Cal_Button = JoystickPage.AddButton("List Calibration", xPos, 10, 30, 230, "List Calibration", CORN_SILK, DARK_SLATE_GRAY, PushOptions::toggle, disp_JS_Cal_EHF);
		xPos += xInc;
		JoystickPage.AddButton("Switch X/Y", xPos, 10, 30, 230, "Switch X/Y", KHAKI, SADDLE_BROWN, PushOptions::select);
		xPos += xInc + 10;
		JS_Disp = JoystickPage.AddJoystickDisplay("JSD", xPos, 90, "", WHITE, NAVY);

		JoystickPage.AddToAutoRefreshList(&JS_Disp);

#ifdef DEBUG
		Serial.println("\t- All Controls added to Joystick Page.  TFT has [" 
			+ (String)MainScreen->PageCount() 
			+ (String)"] pages.  " +
			"Joystick Page has [" + 
			(String)JoystickPage.NumControls() + 
			"] controls");
		Serial.println(JoystickPage.ToString());
#endif // DEBUG

	}
	void Robot_Controller::CreateConsolePage()
	{
#ifdef DEBUG
		Serial.println("\n\n\t- TFT has [" 
			+ (String)MainScreen->PageCount() 
			+ (String)"] pages.\n\t- About to add Console Page");
#endif // DEBUG

		ConsolePage = MainScreen->AddPage("Console");
#ifdef DEBUG
		Serial.println("\t- Added Console Page.  TFT has [" 
			+ (String)MainScreen->PageCount() 
			+ (String)"] pages");
#endif // DEBUG

		ConsoleOut = ConsolePage.AddTextPanel("Console", 55, 50, 5, 5, "C", YELLOW, WHITE); 
#ifdef DEBUG
		Serial.println("\t- All Controls added to Console Page.  TFT has [" 
			+ (String)MainScreen->PageCount() 
			+ (String)"] pages.  " 
			+ "Console Page has [" 
			+ (String)JoystickPage.NumControls() 
			+ "] controls");
		Serial.println(ConsolePage.ToString());
#endif // DEBUG

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
		long now = millis();
		String sNow = (String)now;

#ifdef DEBUG
		//Serial.print("Check Touch " + sNow);
#endif // DEBUG

		Respond_to_Touch_Inputs();
		
		now = millis();
		sNow = (String)now;
#ifdef DEBUG
		Serial.println("Check Joystick " + sNow + (String)" Next Draw: " + _nextRedraw);
#endif // DEBUG

		Read_Joystick_Input();

		//Check_for_XBee_Data();
		if (millis() > _nextRedraw)
		{
			now = millis();
			sNow = (String)now;
			//Serial.print("Redraw " + sNow);
			MainScreen->ReDraw();
			//JS_Disp.DrawJS();
			_nextRedraw = millis() + _redrawInterval;
			long duration = millis() - now;
			now = millis();
			sNow = (String)now;
			//Serial.println(" Done at " + sNow + " duration " + (String)duration + "\n");
			//MainScreen->NextPage();
		}
	}

	void Robot_Controller::Respond_to_Touch_Inputs()
	{
		if (mTouch.isTouching())
		{
			//Serial.println(" Touching");

			SeeedTouchScreen::Point p = mTouch.getPoint();
			p.x = map(p.x, TS_MINX, TS_MAXX, 0, 240);
			p.y = map(p.y, TS_MINY, TS_MAXY, 0, 320);

			// we have some minimum pressure we consider 'valid'
			// pressure of 0 means no pressing!
			if (p.z > __PRESSURE / 3) {
				//Serial.println(+"X = " + (String)p.x + "\tY = " + (String)p.y + "\tPressure = " + (String)p.z);
				Tft.fillCircle(p.x, p.y, map(p.z, 1, 500, 5, 10), WHITE);
				MainScreen->Toggle(p);
			}
		}
		else
		{
			//Serial.println(" Not Touching");
		}
	}

	void Robot_Controller::Read_Joystick_Input()
	{
		//CalStatus.Draw();
		uint16_t x = mJoystick.read(X);
		uint16_t y = mJoystick.read(Y);
		JS_Disp.Update(x, y);
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
