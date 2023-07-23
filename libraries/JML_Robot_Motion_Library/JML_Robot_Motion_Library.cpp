// 
// 
// 

#include "JML_Robot_Motion_Library.h"

namespace Robot_Motion_Library
{
    Robot_Motion::Robot_Motion()
    {
    }

    Robot_Motion::~Robot_Motion()
    {
    }

    void Robot_Motion::Setup_Motors()
    {
        pinMode(LED_PIN, OUTPUT);
        for (int pinindex = 5; pinindex < 11; pinindex++) {
            pinMode(pinindex, OUTPUT); // set pins 3 to 10 as outputs
        }
        analogWrite(SPEED_PIN_A, speed); //AnalogWrite to Generate PWM to control the motor speed
        analogWrite(SPEED_PIN_B, speed);
    }
    void Robot_Motion::ExecuteMotorCommands(int leftRightInput, int upDownInput)
    {
        getMotorCommands(leftRightInput, upDownInput);
        motorAction(LEFT_MOTOR, leftMotorSpeed);
        motorAction(RIGHT_MOTOR, rightMotorSpeed);
    }
    void Robot_Motion::getMotorCommands(int lrInput, int udInput)
    {

        float LR = 0;
        float UD = 0;
        float RM = 255;
        float LM = 255;
        int lrIndex = NEUTRAL;
        int udIndex = NEUTRAL;

        //Convert input range from 0 - 1023 to -1 to 1
        LR = float(lrInput - leftRightCenter) / 512;
        UD = float(udInput - upDownCenter) / 512;

        if (LR > JOYSTICK_TRANSITION) {
            lrIndex = RIGHT_TURN;
        }
        else if (LR < -JOYSTICK_TRANSITION) {
            lrIndex = LEFT_TURN;
        }

        if (UD > JOYSTICK_TRANSITION) {
            udIndex = FORWARD;
        }
        else if (UD < -JOYSTICK_TRANSITION) {
            udIndex = BACK;
        }


        leftMotorSpeed = motorSpeed[LEFT_MOTOR][udIndex][lrIndex];
        rightMotorSpeed = motorSpeed[RIGHT_MOTOR][udIndex][lrIndex];
        //terminalSerial.print("\t UDidx: ");
        //terminalSerial.print(udIndex);
        //terminalSerial.print("\t LRidx: ");
        //terminalSerial.print(lrIndex);
        //terminalSerial.print("\t LM: ");
        //terminalSerial.print(leftMotorSpeed);
        //terminalSerial.print(" RM: ");
        //terminalSerial.println(rightMotorSpeed);

    }

    void Robot_Motion::getFullMotorCommands(int lrInput, int udInput)
    {
        float LR = 0;
        float UD = 0;
        float RM = 0;
        float LM = 0;

        //Eliminate responses in the dead zone around joystick center
        lrInput = (abs(lrInput - leftRightCenter)) <= DEAD_ZONE ? leftRightCenter : lrInput;
        udInput = (abs(udInput - upDownCenter)) <= DEAD_ZONE ? upDownCenter : udInput;

        //Convert input range from 0 - 1023 to -1 to 1
        LR = float(lrInput - leftRightCenter) / 512;
        UD = float(udInput - upDownCenter) / 512;

        if (LR * UD < 0) {
            LM = (LR + UD);
        }
        else {
            if (UD > 0) {
                if (UD > LR) {
                    LM = UD;
                }
                else {
                    LM = LR;
                }
            }
            else {
                if (UD < LR) {
                    LM = UD;
                }
                else {
                    LM = LR;
                }
            }
        }
        LR = (LR * -1);
        if (LR * UD < 0) {
            RM = (LR + UD);
        }
        else {
            if (UD > 0) {
                if (UD > LR) {
                    RM = UD;
                }
                else {
                    RM = LR;
                }
            }
            else {
                if (UD < LR) {
                    RM = UD;
                }
                else {
                    RM = LR;
                }
            }
        }
        leftMotorSpeed = constrain(LM * 255, -255, 255);
        rightMotorSpeed = constrain(RM * 255, -255, 255);
        //terminalSerial.print("\t LM: ");
        //terminalSerial.print(leftMotorSpeed);
        //terminalSerial.print(" RM: ");
        //terminalSerial.println(rightMotorSpeed);
    }

    void Robot_Motion::motorAction(int side, int speed) {
        //This method sets the wheels on either side of the bot in motion
        //the compiler definitions LEFT_MOTOR or RIGHT_MOTOR should be passed as "side" to indicate which
        //side of the robot is being directed to move
        //The desired speed should be passed as "speed"
        //Positive Values make the motors on that side go forward, while negative ones make them go back

        int speedpin;
        int motorpin1;
        int motorpin2;
        if (side == LEFT_MOTOR) {
            speedpin = SPEED_PIN_A;
            motorpin1 = LEFT_MOTOR_PIN_1;
            motorpin2 = LEFT_MOTOR_PIN_2;
        }
        else {
            speedpin = SPEED_PIN_B;
            motorpin1 = RIGHT_MOTOR_PIN_1;
            motorpin2 = RIGHT_MOTOR_PIN_2;
        }

        //Set the speed.  Notice that abs() takes the absolute value, ensuring only positive numbers are passed
        analogWrite(speedpin, abs(speed)); //AnalogWrite to Generate PWM to control the motor speed

        //Now set the direct based on if speed is positive (>0) or not
        if (speed > 0) {                //Move forwards
            digitalWrite(motorpin1, LOW);
            digitalWrite(motorpin2, HIGH);
        }
        else if (speed < 0) {         //Move in reverse
            digitalWrite(motorpin1, HIGH);
            digitalWrite(motorpin2, LOW);
        }
        else {                        //Stop wheels
            digitalWrite(motorpin1, HIGH);
            digitalWrite(motorpin2, HIGH);
        }
    }



    // forward
    void Robot_Motion::moveForward(int speed) {
        motorAction(LEFT_MOTOR, speed);
        motorAction(RIGHT_MOTOR, speed);
        return;
    }

    void Robot_Motion::moveBackwards(int speed) {   //pass speed as a positive number
        motorAction(LEFT_MOTOR, -1 * speed);
        motorAction(RIGHT_MOTOR, -1 * speed);
    }


    void Robot_Motion::fullstop() {
        motorAction(LEFT_MOTOR, 0);
        motorAction(RIGHT_MOTOR, 0);
    }

    //turn left
    void Robot_Motion::rotate_left(int speed) {
        motorAction(LEFT_MOTOR, -1 * speed);
        motorAction(RIGHT_MOTOR, speed);
    }
    void Robot_Motion::steer_left(int speed) {
        motorAction(LEFT_MOTOR, STEERING_RATIO * speed);
        motorAction(RIGHT_MOTOR, speed);
    }
    //turn right
    void Robot_Motion::rotate_right(int speed) {
        motorAction(LEFT_MOTOR, speed);
        motorAction(RIGHT_MOTOR, -1 * speed);
    }

    void Robot_Motion::steer_right(int speed) {
        motorAction(LEFT_MOTOR, speed);
        motorAction(RIGHT_MOTOR, STEERING_RATIO * speed);
    }

    void Robot_Motion::randTurn() {
        long randNumber;
        randomSeed(analogRead(0));
        randNumber = random(0, 10);
        if (randNumber > 5) {
            rotate_right(255);
        }
        else {
            rotate_left(255);
        }
    }
}
