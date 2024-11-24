// Visual Micro is in vMicro>General>Tutorial Mode
//
/*
	Name:       Robot_Hand_Controller.ino
	Created:	5/21/2023 2:26:36 PM
	Author:     JOE-HP-LAPTOP\jmlma
*/

#ifndef _Robot_Controller_Interface_h
//#include <SPI.h>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated"
#include <Arduino_AVRSTL.h>
#include <TFTv2.h>
#include <SeeedTouchScreen.h>
#include "../../RobotScreenSharedProject/ScreenTemplate.h"
#include "src/Robot_Controller_Interface/Robot_Controller_Interface.h"
#pragma GCC diagnostic pop
#endif

long robot_controller_ino_loop_counter = 0;
Robot_Controller_Interface robot_controller_interface_instance = Robot_Controller_Interface();

// The setup() function runs once each time the micro-controller starts
void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
	//robot_controller_interface_instance = Robot_Controller_Interface();
	robot_controller_interface_instance.ControllerSetup();
}

// Add the main program code into the continuous loop() function
void loop() {
	long y = fmod(robot_controller_ino_loop_counter++, 100);

	if (y == 0) {
		Serial.print("|");
		digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
		delay(100);                       // wait for a second
		digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
		delay(100);                       // wait for a second
		digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
		delay(100);                       // wait for a second
		digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
		delay(100);                       // wait for a second
		Serial.println(robot_controller_ino_loop_counter);
		Serial.print("/");
	}
	robot_controller_interface_instance.ControllerLoop();
}