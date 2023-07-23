// JML_Robot_Motion_Library.h

#ifndef _JML_ROBOT_MOTION_LIBRARY_h
#define _JML_ROBOT_MOTION_LIBRARY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif

#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1
#define LEFT_TURN 0
#define NEUTRAL 1
#define RIGHT_TURN 2
#define FORWARD 0
#define BACK 2
#define LEFT_MOTOR_PIN_1 8 // signal output of DC geared motor
#define LEFT_MOTOR_PIN_2 9
#define RIGHT_MOTOR_PIN_1 6
#define RIGHT_MOTOR_PIN_2 7
#define LED_PIN 13
#define SPEED_PIN_A 10//enable motor A
#define SPEED_PIN_B 5//enable motor B
#define STEERING_RATIO 0.5
#define DEAD_ZONE 5     //Range of values around joystick center that should be ignored (scale: 1023)
#define JOYSTICK_TRANSITION 0.33
#define PUSHED = true;
#define NOT_PUSHED = false;



namespace Robot_Motion_Library
{
	class Robot_Motion
	{
	public:
		Robot_Motion();
		~Robot_Motion();

		void Setup_Motors();
		void ExecuteMotorCommands(int leftRightInput, int upDownInput);
		//void ExecuteMotorCommands();
		void getMotorCommands(int lrInput, int udInput);
		void getFullMotorCommands(int lrInput, int udInput);

		void motorAction(int side, int speed);

	private:
		int motorSpeed[2][3][3] = { { {32, 255, 255}, {-255, 0, 255}, {-255, -255, -32} },
									{ {255, 255, 32}, {255, 0, -255}, {-32, -255, -255} } }; //[L/R Motor][Joystick Fwd/Mid/Back][Joystick L/Mid/R]

		int currDist = 0;    // distance
		int speed = 255;
		void moveForward(int speed);
		void moveBackwards(int speed);
		void fullstop();
		void rotate_left(int speed);
		void steer_left(int speed);
		void rotate_right(int speed);
		void steer_right(int speed);
		void randTurn();
		//define the speed of motor

		bool buttonPushed = false;
		bool validXbeeResponse = false;
		int upDownInput;
		int leftRightInput;
		int upDownCenter;
		int leftRightCenter;
		int leftMotorSpeed = 0;
		int rightMotorSpeed = 0;

	};
}

