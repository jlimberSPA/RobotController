//
//
//

#include "Robot_Controller_Interface.h"
using namespace JML_TFT_Library_V2;

namespace stsn = SeeedTouchScreenNamespace;
using namespace stsn;
class stsn::Point;

Robot_Controller_Interface::Robot_Controller_Interface()
//mJoystick(PIN_JOY1_X, PIN_JOY1_Y),
//mScreen(&JML_TFT_Library_V2::LCD_Panel_V2()),
//mTouch(Tft.myTouchPanel()),
//mMotion(Robot_Motion_Library::Robot_Motion())
{
	Serial.println("\nConstructed Robot Controller Interface: LCD Panel and Touch Panel Objects");
}
Robot_Controller_Interface::~Robot_Controller_Interface() {}

// Property Accessors
//AlignedJoy Robot_Controller_Interface::MainJoystick() { return mJoystick; }
JML_TFT_Library_V2::LCD_Panel_V2& Robot_Controller_Interface::MainScreen() { return mScreen; };

//JML_Robot_XBee_Radio_Library::Robot_XBee_Base Robot_Controller_Interface::MainRadio()	{return mXBee;}
//Robot_Motion_Library::Robot_Motion Robot_Controller_Interface::Motion() { return mMotion; }

void Robot_Controller_Interface::ControllerSetup()
{
	Setup_Serial_Interface();
	Serial.println("\nSerial Started, About to initialize LCD");
	Setup_Main_Screen();
	//	Send_Robot_Commands();
}

void Robot_Controller_Interface::Setup_Serial_Interface()
{
	Serial.begin(_SerialSpeed);
	while (!Serial);    // wait for the serial port to open
	delay(3000);
	Serial.println("Communication with Computer Established");
	delay(500);
	Serial.println("Program Started");
}

void Robot_Controller_Interface::Setup_Main_Screen()
{
	Tft.TFTinit();
	delay(3000);
	TFT_BL_ON;                                  // turn on the background light

	Serial.println("\nLCD ## initialized, about to create pages");
	auto mPage1 = MainScreen().AddPage("Page1");
	//auto mPage2 = MainScreen()->AddPage("Page2");
	//auto mPage3 = MainScreen()->AddPage("Page3");
	//auto mPage4 = MainScreen()->AddPage("Page4");
	for (size_t i = 0; i < 50; i++)
	{
		Serial.println(i);
		delay(10);
	}

	Serial.println("\n\n\n ---------- Summary of LCD Panel Pages and Controls -----------");
	MainScreen().SetActivePage(mPage1);
	//Serial.println(MainScreen()->ToString());
}

void Robot_Controller_Interface::CreateJoystickPage()
{
	int yPos = 35;
	int yInc = 35;
	int yPad = 2;

	//Serial.println("\n\n[Screen Object constructed]\n\nStarting Page Setup.\n\t- TFT has [" +
	//	MainScreen->PageCount() + (String)"].\n\t- About to add Joystick Page");
	JoystickPage = MainScreen().AddPage("Joystick");
	//JoystickPage = MainScreen->GetPage(0);
	//Serial.println("\t- Added " + (String)JoystickPage->Name() + " Page.  TFT has [" + MainScreen->PageCount() + "] pages");

	//Top, Left, Height, Width
	DrawParameters CalibrateBtnDP = DrawParameters(yPos, 10, yInc - yPad, 50, WHITE, CRIMSON);
	ControlType& cal = JoystickPage->AddButton(CalibrateBtnDP, "Calibrate", nullptr); //, PushOptions::none);
	yPos += yInc;

	DrawParameters CalibrateBtnDP2 = DrawParameters(yPos, 10, yInc - yPad, 50, WHITE, CRIMSON);
	ControlType& cal2 = JoystickPage->AddButton(CalibrateBtnDP, "Calibrate", nullptr); //, PushOptions::none);

	//JoystickPage->AddButton("CalibrateJoystick", "Calibrate Joystick", xPos, 10, 30, 230, WHEAT, MIDNIGHT_BLUE, PushOptions::toggle, calJS_EHF);
	//xPos += xInc;
	//JoystickPage->AddButton("List Calibration", "List Calibration", xPos, 10, 30, 230, CORN_SILK, DARK_SLATE_GRAY, PushOptions::toggle, disp_JS_Cal_EHF);
	//xPos += xInc;
	//JS_Disp = new JML_TFT_Library::JoystickDisplayControl;
	//JoystickPage->AddJoystickDisplay("JSD", xPos, 90, "", WHITE, NAVY);  //JS_Disp =
	//auto btnCal_Status_Button = JoystickPage->GetControl("CalStatus");
	//auto btnCal_JS_Button = JoystickPage->GetControl("CalibrateJoystick");
	//auto btnList_Cal_Button = JoystickPage->GetControl("List Calibration");
	//{btnCal_Status_Button->Name()}, { btnCal_JS_Button->Name() }, { btnList_Cal_Button->Name()}
	//JoystickPage->AddToAutoRefreshList(JS_Disp);
}
void Robot_Controller_Interface::CreateConsolePage()
{
	int yPos = 35;
	int yInc = 35;
	int yPad = 2;

	ConsolePage = MainScreen().AddPage("Console");

	DrawParameters ConsoleTxtDP = DrawParameters(yPos, 10, yInc - yPad, 50, WHITE, CRIMSON);
	//ConsoleOut =
	ControlType& cal2 = JoystickPage->AddTextBox(ConsoleTxtDP, "Console");
}
//void Robot_Controller_Interface::Send_Robot_Commands()
//{
//	/**< \TODO Build Send_Robot_Commands */
//}

/**
 *  Main Arduino Loop for Robot Hand Robot_Controller_Interface.
 *
 */
void Robot_Controller_Interface::ControllerLoop()
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

	//Read_Joystick_Input();

	//Check_for_XBee_Data();
	if (millis() > _nextRedraw)
	{
		now = millis();
		sNow = (String)now;
		//Serial.print("Redraw " + sNow);
		MainScreen().ReDraw();
		//JS_Disp.DrawJS();
		_nextRedraw = millis() + _redrawInterval;
		long duration = millis() - now;
		now = millis();
		sNow = (String)now;
		//Serial.println(" Done at " + sNow + " duration " + (String)duration + "\n");
		//MainScreen->NextPage();
	}
}

// Arduino's Map function is ambiguous with C++ map library, so just replicating it here
double Robot_Controller_Interface::mapRange(double a1, double a2, double b1, double b2, double s) {
	return b1 + (s - a1) * (b2 - b1) / (a2 - a1);
}

void Robot_Controller_Interface::Respond_to_Touch_Inputs()
{
	if (MainScreen().GetTouchPanel().isTouching())
	{
		//Serial.println(" Touching");

		stsn::Point p = MainScreen().GetTouchPanel().getPoint();
		p.x = mapRange(p.x, TS_MINX, TS_MAXX, 0, 240);
		p.y = mapRange(p.y, TS_MINY, TS_MAXY, 0, 320);

		// we have some minimum pressure we consider 'valid'
		// pressure of 0 means no pressing!
		if (p.z > __PRESSURE / 3) {
			//Serial.println(+"X = " + (String)p.x + "\tY = " + (String)p.y + "\tPressure = " + (String)p.z);
			Tft.fillCircle(p.x, p.y, mapRange(p.z, 1, 500, 5, 10), WHITE);
			MainScreen().Toggle(p);
		}
	}
	else
	{
		//Serial.println(" Not Touching");
	}
}

//void Robot_Controller_Interface::Read_Joystick_Input()
//{
//	//CalStatus.Draw();
//	uint16_t x = mJoystick.read(X);
//	uint16_t y = mJoystick.read(Y);
//	JS_Disp->Update(x, y);
//}

//bool Robot_Controller_Interface::Check_for_XBee_Data()
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
 //bool Robot_Controller_Interface::CalibrateJoystick()
 //{
 //	bool result = true;
 //
 //	// JOYSTICK CALIBRATION Phase 1
 //	// Start the joystick calibration in the center position. Use this method only if the calibration of the axles is desired (axesCalibration).
 //	Serial.print("Center Joystick Calibration \n\nLeave the joystick in the centre position during the calibration\ntime which is set to ");
 //	Serial.print(TIME_CAL_1);
 //	Serial.println(" milliseconds.");
 //	delay(2000);
 //	Serial.println("Center Calibration started!");
 //	delay(500);
 //	/*
 //	 * To calibrate the joystick center point use "centerCalibration" method;
 //	 * objectname.middleCalibration(uint16_t timeOfCal).
 //	 * "timeOfCal" is the calibration time in milliseconds
 //	 */
 //	mJoystick.middleCalibration(TIME_CAL_1);
 //	Serial.println("Joystick Centered!\n\n\n");
 //	delay(2000);
 //
 //	// JOYSTICK CALIBRATION Phase 2
 //	/*
 //	* Calibration of the axes at the extreme points (min end max for each axis).
 //	* It is recommended to rotate the joystick in a circular way along its circumference throughout
 //	* the calibration time.
 //	*/
 //	Serial.print("About to start axes Calibration... \n - Continually rotate the joystick in a circle around its circumference\nthroughout the calibration time (");
 //	Serial.print(TIME_CAL_2);
 //	Serial.println(" milliseconds).");
 //	delay(1000);
 //	Serial.println("Calibration started!");
 //	delay(250);
 //	/*
 //	 * To calibrate the joystick axes points use "axesCalibration" method (bool type);
 //	 * objectname.axesCalibration(uint16_t timeOfCal).
 //	 * "timeOfCal" is the calibration time in milliseconds.
 //	 */
 //	if (mJoystick.axesCalibration(TIME_CAL_2))
 //	{
 //		Serial.println("Calibration succesfully!!");
 //		//DispCal();
 //	}
 //	else
 //	{
 //		Serial.println("Calibration failed!!");
 //		result = false;
 //	}
 //	auto btnCal_JS_Button = JoystickPage->GetControl("CalibrateJoystick");
 //
 //	mJoystickCalibrated = result;
 //	btnCal_JS_Button->UnSelect();
 //
 //	auto btnCalStatus = JoystickPage->GetControl("CalStatus");
 //	if (result)
 //	{
 //		btnCalStatus->Select();
 //	}
 //	else
 //	{
 //		btnCalStatus->UnSelect();
 //	}
 //	return result;
 //}
 //bool Robot_Controller_Interface::DispCal()
 //{
 //	if (mJoystickCalibrated)
 //	{
 //		// Print all points calibrated
 //		/*
 //		 * You can use these values to save them to eeprom memory. In this way you will avoid requiring the joystick calibration at each boot time.
 //		 * To set the parameters read by eeprom you have to use the "setCalibratedPoint" method.
 //		 * If your project does not require the re-calibration of the joystick then you can make a sketch like this only to display the calibrated
 //		 * values to set them in the final project using the "setCalibratedPoint" method.
 //		 * To get the calibrated point values use getCalibratedPoint(axis_t axis, point_t point).
 //		 * The parameters: the labels of the "axis_t" shall be X and Y; the labels of "point_t" is MIN, MID and MAX.
 //		 */
 //		Serial.print("X min -> ");
 //		Serial.print(mJoystick.getCalibratedPoint(X, MIN));
 //		Serial.print(" | center ->  ");
 //		Serial.print(mJoystick.getCalibratedPoint(X, MID));
 //		Serial.print(" | max -> ");
 //		Serial.println(mJoystick.getCalibratedPoint(X, MAX));
 //		Serial.print("Y min -> ");
 //		Serial.print(mJoystick.getCalibratedPoint(Y, MIN));
 //		Serial.print(" | center ->  ");
 //		Serial.print(mJoystick.getCalibratedPoint(Y, MID));
 //		Serial.print(" | max -> ");
 //		Serial.println(mJoystick.getCalibratedPoint(Y, MAX));
 //	}
 //	else
 //	{
 //		Serial.println(" *** Joystick NOT calibrated yet ***");
 //	}
 //}
 //
 //bool Robot_Controller_Interface::Switch_X_Y()
 //{
 //	mJoystick.Switch_X_Y();
 //}
 //bool Robot_Controller_Interface::Reverse_X()
 //{
 //	mJoystick.Reverse_X();
 //}
 //bool Robot_Controller_Interface::Reverse_Y()
 //{
 //	mJoystick.Reverse_Y();
 //}

 //Robot_Controller_Interface ;