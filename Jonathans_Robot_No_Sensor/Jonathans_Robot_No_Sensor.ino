//#include <LimberBots.h>
//LimberBots MyBot;

#define LEFT_SIDE 1
#define RIGHT_SIDE 2
#define LEFT_MOTOR_PIN_1 8 // signal output of DC geared motor
#define LEFT_MOTOR_PIN_2 9
#define RIGHT_MOTOR_PIN_1 6
#define RIGHT_MOTOR_PIN_2 7
#define LED_PIN 13
#define SPEED_PIN_A 10//enable motor A
#define SPEED_PIN_B 5//enable motor B
#define STEERING_RATIO 0.5
#define PUSHED = true;
#define NOT_PUSHED = false;


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
  Serial.begin(9600);  //Debug Data
  while (!Serial);    // wait for the serial port to open
  Serial.println("Communication with Computer Established");

  Serial1.begin(9600); // initialize Serial communication with XBee
  while (!Serial1);    // wait for the serial port to open
  Serial.println("Communication with XBee Established");

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
  Serial.println(upDownCenter);
}

void loop() {
  bool valid = readXbee();
  if (valid) {
    getMotorCommands(leftRightInput, upDownInput);
    motorAction(LEFT_SIDE, leftMotorSpeed);
    motorAction(RIGHT_SIDE, rightMotorSpeed);
  }
  
}

bool readXbee() {
    int ct = 0;
    byte xbMSB = 0;
    byte xbLSB = 0;
    int analogReading = 0;
    upDownInput = -1;
    leftRightInput = -1;
    
    while(ct<26){
      if(Serial1.available()) {     // Make sure the frame is all there
        byte discardByte = Serial1.read();
        if (discardByte == 0x7E) {
          Serial.println();
          ct = 0;
          }
        ct++;
  
  //      if (ct>190){
  //      Serial.print(ct);
  //      Serial.print(":");
  //      Serial.print(discardByte, HEX);
  //      Serial.print("||");
  //      }
        switch (ct) {
          case 21:
            Serial.print(discardByte == 4 ? "Not Pushed-" : "Pushed-");
            buttonPushed = (discardByte == 4 ? false : true);
            
            break;
          case 22:
          case 24:
            xbMSB = discardByte;  // Read the first analog byte data
            break;
          case 23:
          case 25:
            xbLSB = discardByte;  // Read the second byte
            analogReading = xbLSB + (xbMSB * 256);
            ct == 23 ? upDownInput = analogReading : leftRightInput = analogReading;
            Serial.print(ct == 23 ? "<1:" : "<2:");
            Serial.print(analogReading);
            Serial.print(">");
            break;
          default: 
            Serial.print(".");
          break;
        }
      }
    }
    
    if (ct>25 & upDownInput >= 0 & leftRightInput >= 0){
      return true;
    } else {
      return false;
    }
    
}    

void getMotorCommands(int lrInput, int udInput)
{
  float LR = 0;
  float UD = 0;
  float RM = 0;
  float LM = 0;

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
  Serial.print(" LM: ");
  Serial.print(leftMotorSpeed);
  Serial.print(" RM: ");
  Serial.print(rightMotorSpeed);

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
  //the compiler definitions LEFT_SIDE or RIGHT_SIDE should be passed as "side" to indicate which
  //side of the robot is being directed to move
  //The desired speed should be passed as "speed"
  //Positive Values make the motors on that side go forward, while negative ones make them go back

  int speedpin;
  int motorpin1;
  int motorpin2;
  if (side == LEFT_SIDE) {
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
  motorAction(LEFT_SIDE, speed);
  motorAction(RIGHT_SIDE, speed);
  return;
}

void moveBackwards(int speed) {   //pass speed as a positive number
  motorAction(LEFT_SIDE,  -1 * speed);
  motorAction(RIGHT_SIDE, -1 * speed);
}


void fullstop() {
  motorAction(LEFT_SIDE, 0);
  motorAction(RIGHT_SIDE, 0);
}

//turn left
void rotate_left(int speed) {
  motorAction(LEFT_SIDE, -1 * speed);
  motorAction(RIGHT_SIDE, speed);
}
void steer_left(int speed) {
  motorAction(LEFT_SIDE, STEERING_RATIO * speed);
  motorAction(RIGHT_SIDE, speed);
}
//turn right
void rotate_right(int speed) {
  motorAction(LEFT_SIDE, speed);
  motorAction(RIGHT_SIDE, -1 * speed);
}

void steer_right(int speed) {
  motorAction(LEFT_SIDE, speed);
  motorAction(RIGHT_SIDE, STEERING_RATIO * speed);
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
