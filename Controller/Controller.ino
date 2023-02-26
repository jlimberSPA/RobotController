
#include <JML_TFT_Interface.h>
#include <TFTv2.h>
#include <SeeedTouchScreen.h>

//#include "TFT_Interface_JML.h"

#define ShowSerial Serial


// char array to print to the screen
char sensorPrintout[6];

TFT_Interface_JML::LCD_Panel_V2 screen = TFT_Interface_JML::LCD_Panel_V2();

auto myTouch = screen.myTouchPanel();
TFT_Interface_JML::Button btn = TFT_Interface_JML::Button();

void setup() {

  Serial.begin(115200);

  TFT_BL_ON;                                  // turn on the background light
  Tft.TFTinit();                              //init TFT library
                          //Bottom, Left, Height, Width
  screen.AddButton("Test 1", 40, 10, 30, 170, "Test Button 1", WHITE, BLUE);
  screen.AddButton("Test 2", 80, 10, 30, 170, "Test Button 2", WHITE, BLUE);
  screen.AddButton("Test 3", 120, 10, 30, 170, "Test Button 3", WHITE, BLUE);
  screen.AddButton("Test 4", 160, 10, 30, 170, "Test Button 4", WHITE, BLUE);

  //screen.AddButton("Test 1", 40, 10, 30, 170, "Test Button 1", WHITE, BLUE, ButtonPressed);
  //screen.AddButton("Test 2", 80, 10, 30, 170, "Test Button 2", WHITE, BLUE, ButtonPressed);
  //screen.AddButton("Test 3", 120, 10, 30, 170, "Test Button 3", WHITE, BLUE, ButtonPressed);
  //screen.AddButton("Test 4", 160, 10, 30, 170, "Test Button 4", WHITE, BLUE, ButtonPressed);


}

void loop() {

// myScreen.setCursor(50, 50);
// myScreen.drawCircle(20, 20, 20, 128);
// myScreen.circle(100, 100, 10);  

  // Read the value of the sensor on A0
  // String sensorVal1 = String(analogRead(A9));
  // String sensorVal2 = String(analogRead(A10));
  
  auto p = myTouch.getPoint();
  
   //if (p.z > __PRESSURE) {
   //     ShowSerial.print("Raw X = "); ShowSerial.print(p.x);
   //     ShowSerial.print("\tRaw Y = "); ShowSerial.print(p.y);
   //     ShowSerial.print("\tPressure = "); ShowSerial.println(p.z);
   // }

  
  p.x = map(p.x, TS_MINX, TS_MAXX, 0, 240);
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, 320);

  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  if (p.z > __PRESSURE) {
      ShowSerial.println();
      ShowSerial.println("X = "); ShowSerial.println(p.x);
      ShowSerial.println("\tY = "); ShowSerial.println(p.y);
      ShowSerial.println("\tPressure = "); ShowSerial.println(p.z);
    Tft.fillCircle(p.x, p.y, 2000/p.z, WHITE);
    screen.Toggle(p);
  }
  
  //delay(50);
}

bool ButtonPressed()
{
    ShowSerial.println("A Button was just pressed");
}