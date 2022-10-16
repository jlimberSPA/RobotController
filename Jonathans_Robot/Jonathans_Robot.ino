#include <LimberBots.h>

LimberBots MyBot;

unsigned int remote_value;

#define LEFT_SIDE 1
#define RIGHT_SIDE 2
#define LEFT_MOTOR_PIN_1 8 // signal output of DC geared motor
#define LEFT_MOTOR_PIN_2 9
#define RIGHT_MOTOR_PIN_1 6
#define RIGHT_MOTOR_PIN_2 7   
#define LED_PIN 13
#define ECHO_PIN 2       // Ultrasonic signal input
#define TRIGGER_PIN 3       // Ultrasonic signal output
#define SPEED_PIN_A 10//enable motor A
#define SPEED_PIN_B 5//enable motor B
#define STEERING_RATIO 0.75
  
int currDist = 0;    // distance   
void setup() {   
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);   
  for (int pinindex = 3; pinindex < 11; pinindex++) {
    pinMode(pinindex, OUTPUT); // set pins 3 to 10 as outputs   
    }

  int speed = 255;//define the speed of motor
  analogWrite(SPEED_PIN_A,speed);//AnalogWrite to Generate PWM to control the motor speed
  analogWrite(SPEED_PIN_B,speed);   
  MyBot.remote_setup();
}

void loop() {
  MyBot.remote_scan();
  remote_value = MyBot.remote_value_read();
  Serial.println(millis());
  Serial.println(remote_value, HEX);
  Serial.println(MyBot.irDataHigh);
  Serial.println(MyBot.irDataLow);
  Serial.println(MyBot.irBits);
  Serial.println(MyBot.irRxFlag); 
  Serial.println(MyBot.interrupt_count); 

  Serial.println();
  if(remote_value = SW1){
    blink(0);
    //moveForward(255);
  } else if (remote_value = SW2){
    blink(2);
    //moveBackwards(255);
  } else if (remote_value = SW3){
    blink(3);
    //rotate_left(255);
  } else if (remote_value = SW4){
    blink(4);
    //rotate_right(255);
  } else if (remote_value = SW5){
    blink(5);
    //totalhalt();
  }
//  //Left Wheels Backwards
//  blink(1);
//  digitalWrite(LEFT_MOTOR_PIN_1, LOW);
//  digitalWrite(LEFT_MOTOR_PIN_2, HIGH);
//
//  //Left Wheels Forward
//  blink(2);
//  digitalWrite(LEFT_MOTOR_PIN_1, HIGH);
//  digitalWrite(LEFT_MOTOR_PIN_2, LOW);
//
//  //Right Wheels Backwards
//  blink(3);
//  digitalWrite(RIGHT_MOTOR_PIN_1, LOW);
//  digitalWrite(RIGHT_MOTOR_PIN_2, HIGH);
//
//  //Right Wheels Forward
//  blink(4);
//  digitalWrite(RIGHT_MOTOR_PIN_1, HIGH);
//  digitalWrite(RIGHT_MOTOR_PIN_2, LOW);  
}

void motorAction(int side, int speed){
  //This method sets the wheels on either side of the bot in motion
  //the compiler definitions LEFT_SIDE or RIGHT_SIDE should be passed as "side" to indicate which
  //side of the robot is being directed to move
  //The desired speed should be passed as "speed"
  //Positive Values make the motors on that side go forward, while negative ones make them go back
  
  int speedpin;
  int motorpin1;
  int motorpin2;
  if(side == LEFT_SIDE){
    speedpin = SPEED_PIN_A;
    motorpin1 = LEFT_MOTOR_PIN_1;
    motorpin2 = LEFT_MOTOR_PIN_2;
  } else if (side == RIGHT_SIDE){
    speedpin = SPEED_PIN_B;
    motorpin1 = RIGHT_MOTOR_PIN_1;
    motorpin2 = RIGHT_MOTOR_PIN_2;
  }
  
  //Set the speed.  Notice that abs() takes the absolute value, ensuring only positive numbers are passed
  analogWrite(speedpin,abs(speed));//AnalogWrite to Generate PWM to control the motor speed
  
  //Now set the direct based on if speed is positive (>0) or not
  if (speed>0) {                  //Move forwards
    digitalWrite(motorpin1, LOW);
    digitalWrite(motorpin2, HIGH);
  } else if (speed<0) {           //Move in reverse
    digitalWrite(motorpin1, HIGH);
    digitalWrite(motorpin2, LOW);    
  } else {                        //Stop wheels
    digitalWrite(motorpin1, HIGH);
    digitalWrite(motorpin2, HIGH);  
  }
}


  void blink(int num) {

    for (int i = 0; i < num; i++) {
      digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(200);  
      digitalWrite(13, LOW);   // turn the LED on (HIGH is the voltage level)
      delay(200);  
      
      }
    delay(200);
  }
  
   //measure distance, unit:cm  
   long MeasuringDistance() {   
    long duration;   
    //pinMode(TRIGGER_PIN, OUTPUT);
    digitalWrite(TRIGGER_PIN, LOW);   
    delayMicroseconds(2);   
    digitalWrite(TRIGGER_PIN, HIGH);   
    delayMicroseconds(10);   
    digitalWrite(TRIGGER_PIN, LOW);     
    //pinMode(ECHO_PIN, INPUT);   
    duration = pulseIn(ECHO_PIN, HIGH);     
    return duration / 29 / 2; 
    }   
    
  // forward 
  void moveForward(int speed) {   
    motorAction(LEFT_SIDE,speed); 
    motorAction(RIGHT_SIDE,speed);
    return; 
    }

  void moveBackwards(int speed) {   //pass speed as a positive number
    motorAction(LEFT_SIDE,  -1 * speed); 
    motorAction(RIGHT_SIDE, -1 * speed);
  }

      
  void totalhalt() {
    motorAction(LEFT_SIDE,0); 
    motorAction(RIGHT_SIDE,0);
  }

  //turn left  
  void rotate_left(int speed) {   
    motorAction(LEFT_SIDE,-1 * speed); 
    motorAction(RIGHT_SIDE,speed);
    }     
  void steer_left(int speed) {   
    motorAction(LEFT_SIDE, STEERING_RATIO * speed); 
    motorAction(RIGHT_SIDE,speed);
    }   
  //turn right  
  void rotate_right(int speed) {
    motorAction(LEFT_SIDE, speed); 
    motorAction(RIGHT_SIDE,-1 * speed);
    }
    
  void steer_right(int speed) {
    motorAction(LEFT_SIDE, speed); 
    motorAction(RIGHT_SIDE, STEERING_RATIO * speed);
    }
    
  void randTurn(){   
    long randNumber;   
    randomSeed(analogRead(0));   
    randNumber = random(0, 10);   
    if(randNumber > 5) {     
      rotate_right(255);   
      }   
      else   {     
        rotate_left(255);
        } 
    }


    //  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
//  moveBackwards();
////  delay(2000);                       // wait for two second
//  
//  digitalWrite(13, LOW);    // turn the LED off
//  moveForward();
//  delay(2000);                       // wait for two second

//    randomSeed(analogRead(0));   
//    currDist = random(0, 30);   
//  //currDist =  //MeasuringDistance(); //measure front distance     
//  if(currDist >20) {     
//    moveForward(255);
//  }
//  else if (currDist < 10) {
//  moveBackwards(255);      //backward  
//  randTurn();
//  }   else {     
//    //whichway()
//    randTurn();
//    }
