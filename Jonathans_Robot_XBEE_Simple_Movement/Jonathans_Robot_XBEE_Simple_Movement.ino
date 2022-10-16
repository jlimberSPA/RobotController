//#include <LimberBots.h>
//LimberBots MyBot;

#include <XBee.h>

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

#define terminalSerial Serial
#define xbeeSerial1 Serial1

//Setup Motor Command Matrix
int motorSpeed[2][3][3] = { { {32, 255, 255}, {-255, 0, 255}, {-255, -255, -32} },
                            { {255, 255, 32}, {255, 0, -255}, {-32, -255, -255} } }; //[L/R Motor][Joystick Fwd/Mid/Back][Joystick L/Mid/R]

XBee myXbee = XBee();
ZBRxIoSampleResponse myIoSample = ZBRxIoSampleResponse();
XBeeAddress64 myTest = XBeeAddress64();


int currDist = 0;    // distance
int speed = 255;//define the speed of motor
bool buttonPushed = false;
bool validXbeeResponse = false;
int upDownInput;
int leftRightInput;
int upDownCenter;
int leftRightCenter;
int leftMotorSpeed = 0;
int rightMotorSpeed = 0;

void setup() {
  terminalSerial.begin(9600);  //Debug Data
  while (!terminalSerial);    // wait for the serial port to open
  terminalSerial.println("Communication with Computer Established");

  xbeeSerial1.begin(9600); // initialize Serial communication with XBee
  while (!xbeeSerial1);    // wait for the serial port to open
  terminalSerial.println("Communication with XBee Established");
  myXbee.setSerial(xbeeSerial1);

  pinMode(LED_PIN, OUTPUT);
  for (int pinindex = 5; pinindex < 11; pinindex++) {
    pinMode(pinindex, OUTPUT); // set pins 3 to 10 as outputs
  }
  analogWrite(SPEED_PIN_A, speed); //AnalogWrite to Generate PWM to control the motor speed
  analogWrite(SPEED_PIN_B, speed);

  ///Get neutral position reading for the two joystick axis

  while(!readXbee());  
  upDownCenter = upDownInput;
  leftRightCenter = leftRightInput;
}

void loop() {
  bool valid = readXbee();
  if (valid) {
    getMotorCommands(leftRightInput, upDownInput);
    motorAction(LEFT_MOTOR, leftMotorSpeed);
    motorAction(RIGHT_MOTOR, rightMotorSpeed);
  }
  
}
bool readXbee(){
  bool gotResponse = false;
  myXbee.readPacket();
  if (myXbee.getResponse().isAvailable()) {  // got something
    if (myXbee.getResponse().getApiId() == ZB_IO_SAMPLE_RESPONSE) {
      gotResponse = true;
      
      myXbee.getResponse().getZBRxIoSampleResponse(myIoSample);

      // read analog inputs
      if (myIoSample.isAnalogEnabled(0) & myIoSample.isAnalogEnabled(1)){
        upDownInput = myIoSample.getAnalog(0);
        leftRightInput = myIoSample.getAnalog(1);
        terminalSerial.print("UpDown:  ");
        terminalSerial.print(upDownInput);
        terminalSerial.print("\tLeftRight:  ");
        terminalSerial.print(leftRightInput);
      } else {
        gotResponse = false;          
        terminalSerial.print("Bad Analog Data\t");
      }
      
      // check digital inputs
      if (myIoSample.isDigitalEnabled(2)) {
        buttonPushed = !myIoSample.isDigitalOn(2);
        terminalSerial.print("\tButton pushed:  ");
        terminalSerial.print(buttonPushed);
      } else {
        gotResponse = false;                  
        terminalSerial.print("Bad Digital Data\t");
      }
    } else {
      terminalSerial.print("Expected I/O Sample, but got ");
      terminalSerial.print(myXbee.getResponse().getApiId(), HEX);
    }
  } else {
    if (myXbee.getResponse().isError()) {
      terminalSerial.print("Error reading packet.  Error code: ");  
      terminalSerial.println(myXbee.getResponse().getErrorCode());
    } else {
//      terminalSerial.println("XBee is not available");      
    }
  }
  return gotResponse;
}

void getMotorCommands(int lrInput, int udInput)
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

    if (LR > JOYSTICK_TRANSITION){
      lrIndex = RIGHT_TURN;      
    } else if (LR < -JOYSTICK_TRANSITION){
      lrIndex = LEFT_TURN;      
    }

    if (UD > JOYSTICK_TRANSITION){
      udIndex = FORWARD;      
    } else if (UD < -JOYSTICK_TRANSITION){
      udIndex = BACK;      
    }


  leftMotorSpeed = motorSpeed[LEFT_MOTOR][udIndex][lrIndex];
  rightMotorSpeed = motorSpeed[RIGHT_MOTOR][udIndex][lrIndex];
  terminalSerial.print("\t UDidx: ");
  terminalSerial.print(udIndex);
  terminalSerial.print("\t LRidx: ");
  terminalSerial.print(lrIndex);
  terminalSerial.print("\t LM: ");
  terminalSerial.print(leftMotorSpeed);
  terminalSerial.print(" RM: ");
  terminalSerial.println(rightMotorSpeed);

} 


void getFullMotorCommands(int lrInput, int udInput)
{
  float LR = 0;
  float UD = 0;
  float RM = 0;
  float LM = 0;

  //Eliminate responses in the dead zone around joystick center
  lrInput = (abs(lrInput - leftRightCenter)) <= DEAD_ZONE ?  leftRightCenter : lrInput;
  udInput = (abs(udInput - upDownCenter))    <= DEAD_ZONE ?  upDownCenter : udInput;
  
  //Convert input range from 0 - 1023 to -1 to 1
  LR = float(lrInput - leftRightCenter) / 512;
  UD = float(udInput - upDownCenter) / 512;

  if (LR * UD < 0) {
    LM = (LR + UD);
  } else {
    if (UD > 0) {
      if (UD > LR) {
        LM = UD;
      } else {
        LM = LR;
      }
    } else {
      if (UD < LR) {
        LM = UD;
      } else {
        LM = LR;
      }
    }
  }
  LR = (LR * -1);
  if (LR * UD < 0) {
    RM = (LR + UD);
  } else {
    if (UD > 0) {
      if (UD > LR) {
        RM = UD;
      } else {
        RM = LR;
      }
    } else {
      if (UD < LR) {
        RM = UD;
      } else {
        RM = LR;
      }
    }
  }
  leftMotorSpeed = constrain(LM * 255, -255, 255);
  rightMotorSpeed = constrain(RM * 255, -255, 255);
  terminalSerial.print("\t LM: ");
  terminalSerial.print(leftMotorSpeed);
  terminalSerial.print(" RM: ");
  terminalSerial.println(rightMotorSpeed);

} 

bool readFullXbee(){
  bool gotResponse = false;
  myXbee.readPacket();

  if (myXbee.getResponse().isAvailable()) {
    // got something

    if (myXbee.getResponse().getApiId() == ZB_IO_SAMPLE_RESPONSE) {
      gotResponse = true;
      myXbee.getResponse().getZBRxIoSampleResponse(myIoSample);

      terminalSerial.print("Received I/O Sample from: ");
      
      terminalSerial.print(myIoSample.getRemoteAddress64().getMsb(), HEX);  
      terminalSerial.print(myIoSample.getRemoteAddress64().getLsb(), HEX);  
      terminalSerial.println("");
      
      if (myIoSample.containsAnalog()) {
        terminalSerial.println("Sample contains analog data");
      }

      if (myIoSample.containsDigital()) {
        terminalSerial.println("Sample contains digtal data");
      }      

      // read analog inputs
      for (int i = 0; i <= 4; i++) {
        if (myIoSample.isAnalogEnabled(i)) {
          terminalSerial.print("Analog (AI");
          terminalSerial.print(i, DEC);
          terminalSerial.print(") is ");
          terminalSerial.println(myIoSample.getAnalog(i), DEC);
        }
      }

      if (myIoSample.isAnalogEnabled(0) & myIoSample.isAnalogEnabled(1)){
        upDownInput = myIoSample.getAnalog(0);
        leftRightInput = myIoSample.getAnalog(1);
        } else {
          gotResponse = false;          
        }
      
      // check digital inputs
      for (int i = 0; i <= 12; i++) {
        if (myIoSample.isDigitalEnabled(i)) {
          terminalSerial.print("Digital (DI");
          terminalSerial.print(i, DEC);
          terminalSerial.print(") is ");
          terminalSerial.println(myIoSample.isDigitalOn(i), DEC);
        }
      }
      buttonPushed = !myIoSample.isDigitalOn(2);

      
      // method for printing the entire frame data
      //for (int i = 0; i < myXbee.getResponse().getFrameDataLength(); i++) {
      //  terminalSerial.print("byte [");
      //  terminalSerial.print(i, DEC);
      //  terminalSerial.print("] is ");
      //  terminalSerial.println(myXbee.getResponse().getFrameData()[i], HEX);
      //}
    } 
    else {
      terminalSerial.print("Expected I/O Sample, but got ");
      terminalSerial.print(myXbee.getResponse().getApiId(), HEX);
    }    
  } else if (myXbee.getResponse().isError()) {
    terminalSerial.print("Error reading packet.  Error code: ");  
    terminalSerial.println(myXbee.getResponse().getErrorCode());
  }
  return gotResponse;
}


void blink(int num) {

  for (int i = 0; i < num; i++) {
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);
    digitalWrite(13, LOW);   // turn the LED on (HIGH is the voltage level)
    delay(50);

  }
  delay(500);
  fullstop();
  delay(1000);
}

void motorAction(int side, int speed) {
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
  } else {
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
  } else if (speed < 0) {         //Move in reverse
    digitalWrite(motorpin1, HIGH);
    digitalWrite(motorpin2, LOW);
  } else {                        //Stop wheels
    digitalWrite(motorpin1, HIGH);
    digitalWrite(motorpin2, HIGH);
  }
}



// forward
void moveForward(int speed) {
  motorAction(LEFT_MOTOR, speed);
  motorAction(RIGHT_MOTOR, speed);
  return;
}

void moveBackwards(int speed) {   //pass speed as a positive number
  motorAction(LEFT_MOTOR,  -1 * speed);
  motorAction(RIGHT_MOTOR, -1 * speed);
}


void fullstop() {
  motorAction(LEFT_MOTOR, 0);
  motorAction(RIGHT_MOTOR, 0);
}

//turn left
void rotate_left(int speed) {
  motorAction(LEFT_MOTOR, -1 * speed);
  motorAction(RIGHT_MOTOR, speed);
}
void steer_left(int speed) {
  motorAction(LEFT_MOTOR, STEERING_RATIO * speed);
  motorAction(RIGHT_MOTOR, speed);
}
//turn right
void rotate_right(int speed) {
  motorAction(LEFT_MOTOR, speed);
  motorAction(RIGHT_MOTOR, -1 * speed);
}

void steer_right(int speed) {
  motorAction(LEFT_MOTOR, speed);
  motorAction(RIGHT_MOTOR, STEERING_RATIO * speed);
}

void randTurn() {
  long randNumber;
  randomSeed(analogRead(0));
  randNumber = random(0, 10);
  if (randNumber > 5) {
    rotate_right(255);
  }
  else   {
    rotate_left(255);
  }
}
