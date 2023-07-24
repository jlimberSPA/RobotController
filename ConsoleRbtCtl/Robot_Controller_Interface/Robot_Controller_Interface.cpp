//
//
//

#include "Robot_Controller_Interface.h"
using namespace JML_TFT_Library_V2;

Robot_Controller_Interface::Robot_Controller_Interface()
{
	PseudoSerial::print(F("RESTARTING - "));
	//	PseudoSerial::println("\n---Constructed Robot Controller Interface: LCD Panel and Touch Panel Objects");
}
Robot_Controller_Interface::~Robot_Controller_Interface() = default;

// Property Accessors
JML_TFT_Library_V2::LCD_Panel_V2& Robot_Controller_Interface::MainScreen() { return mScreen; };

void Robot_Controller_Interface::ControllerSetup()
{
	Setup_Serial_Interface();
	PseudoSerial::println(F("\nSerial Started, About to initialize LCD"));
	Setup_Main_Screen();
}

void Robot_Controller_Interface::Setup_Serial_Interface()
{
}

void Robot_Controller_Interface::Setup_Main_Screen()
{
	PseudoSerial::println(F("\nLCD initialized, about to create pages"));
	auto mPage1 = MainScreen().AddPage("Page1");
}
void Robot_Controller_Interface::CreateJoystickPage()
{
	uint8_t yPos = 35;
	uint8_t yInc = 35;
	uint8_t yPad = 2;

	JoystickPage = MainScreen().AddPage("Joystick");

	//Top, Left, Height, Width
	auto CalibrateBtnDP = DrawParameters(yPos, 10, yInc - yPad, 50, WHITE, CRIMSON);
	ControlType* cal = JoystickPage->AddButton("Calibrate", CalibrateBtnDP, "Calibrate", nullptr); //, PushOptions::none);
	yPos += yInc;

	auto CalibrateBtnDP2 = DrawParameters(yPos, 10, yInc - yPad, 50, WHITE, CRIMSON);
	ControlType* cal2 = JoystickPage->AddButton("Calibrate2", CalibrateBtnDP, "Calibrate2", nullptr); //, PushOptions::none);
}
void Robot_Controller_Interface::CreateConsolePage()
{
	uint8_t yPos = 35;
	uint8_t yInc = 35;
	uint8_t yPad = 2;

	ConsolePage = MainScreen().AddPage("Console");

	auto ConsoleTxtDP = DrawParameters(yPos, 10, yInc - yPad, 50, WHITE, CRIMSON);
	//ConsoleOut =
	ControlType* cal2 = ConsolePage->AddTextBox("Console", ConsoleTxtDP, "Console");
}

/**
 *  Main Arduino Loop for Robot Hand Robot_Controller_Interface.
 *
 */
void Robot_Controller_Interface::ControllerLoop()
{
	Respond_to_Touch_Inputs();
	auto now = std::chrono::system_clock::now();;
	std::chrono::duration<double, std::milli> elapsed_seconds = now - start;
	if (elapsed_seconds.count() > _redrawInterval.count())
	{
		now = std::chrono::system_clock::now();
		PseudoSerial::print("%%Redraw:");  // + sNow
		MainScreen().ReDraw();
		start = std::chrono::system_clock::now();
	}
}

// Arduino's Map function is ambiguous with C++ map library, so just replicating it here
double Robot_Controller_Interface::mapRange(double a1, double a2, double b1, double b2, double s) {
	return b1 + (s - a1) * (b2 - b1) / (a2 - a1);
}

void Robot_Controller_Interface::Respond_to_Touch_Inputs()
{
	//if (MainScreen().GetTouchPanel().isTouching())
	//{
	//	//PseudoSerial::println(" Touching");

	//	stsn::Point p = MainScreen().GetTouchPanel().getPoint();
	//	p.x = mapRange(p.x, TS_MINX, TS_MAXX, 0, 240);
	//	p.y = mapRange(p.y, TS_MINY, TS_MAXY, 0, 320);

	//	// we have some minimum pressure we consider 'valid'
	//	// pressure of 0 means no pressing!
	//	if (p.z > __PRESSURE / 3) {
	//		//PseudoSerial::println(+"X = " + (char*)p.x + "\tY = " + (char*)p.y + "\tPressure = " + (char*)p.z);
	//		Tft.fillCircle(p.x, p.y, mapRange(p.z, 1, 500, 5, 10), WHITE);
	//		MainScreen().Toggle(p);
	//	}
	//}
	//else
	//{
	//	//PseudoSerial::println(" Not Touching");
	//}
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
 //	PseudoSerial::print("Center Joystick Calibration \n\nLeave the joystick in the centre position during the calibration\ntime which is set to ");
 //	PseudoSerial::print(TIME_CAL_1);
 //	PseudoSerial::println(" milliseconds.");
 //	delay(2000);
 //	PseudoSerial::println("Center Calibration started!");
 //	delay(500);
 //	/*
 //	 * To calibrate the joystick center point use "centerCalibration" method;
 //	 * objectname.middleCalibration(uint16_t timeOfCal).
 //	 * "timeOfCal" is the calibration time in milliseconds
 //	 */
 //	mJoystick.middleCalibration(TIME_CAL_1);
 //	PseudoSerial::println("Joystick Centered!\n\n\n");
 //	delay(2000);
 //
 //	// JOYSTICK CALIBRATION Phase 2
 //	/*
 //	* Calibration of the axes at the extreme points (min end max for each axis).
 //	* It is recommended to rotate the joystick in a circular way along its circumference throughout
 //	* the calibration time.
 //	*/
 //	PseudoSerial::print("About to start axes Calibration... \n - Continually rotate the joystick in a circle around its circumference\nthroughout the calibration time (");
 //	PseudoSerial::print(TIME_CAL_2);
 //	PseudoSerial::println(" milliseconds).");
 //	delay(1000);
 //	PseudoSerial::println("Calibration started!");
 //	delay(250);
 //	/*
 //	 * To calibrate the joystick axes points use "axesCalibration" method (bool type);
 //	 * objectname.axesCalibration(uint16_t timeOfCal).
 //	 * "timeOfCal" is the calibration time in milliseconds.
 //	 */
 //	if (mJoystick.axesCalibration(TIME_CAL_2))
 //	{
 //		PseudoSerial::println("Calibration succesfully!!");
 //		//DispCal();
 //	}
 //	else
 //	{
 //		PseudoSerial::println("Calibration failed!!");
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
 //		PseudoSerial::print("X min -> ");
 //		PseudoSerial::print(mJoystick.getCalibratedPoint(X, MIN));
 //		PseudoSerial::print(" | center ->  ");
 //		PseudoSerial::print(mJoystick.getCalibratedPoint(X, MID));
 //		PseudoSerial::print(" | max -> ");
 //		PseudoSerial::println(mJoystick.getCalibratedPoint(X, MAX));
 //		PseudoSerial::print("Y min -> ");
 //		PseudoSerial::print(mJoystick.getCalibratedPoint(Y, MIN));
 //		PseudoSerial::print(" | center ->  ");
 //		PseudoSerial::print(mJoystick.getCalibratedPoint(Y, MID));
 //		PseudoSerial::print(" | max -> ");
 //		PseudoSerial::println(mJoystick.getCalibratedPoint(Y, MAX));
 //	}
 //	else
 //	{
 //		PseudoSerial::println(" *** Joystick NOT calibrated yet ***");
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