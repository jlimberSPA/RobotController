
#include <Arduino_AVRSTL.h>
#include "TFT_Interface_JML.h"

#define ShowSerial Serial


// char array to print to the screen
char sensorPrintout[6];

TFT_Interface_JML::LCD_Panel_V2 screen = TFT_Interface_JML::LCD_Panel_V2();

auto myTouch = screen.myTouchPanel();
TFT_Interface_JML::Button btn = TFT_Interface_JML::Button();

void setup() {

  Serial.begin(9600);

  TFT_BL_ON;                                  // turn on the background light
  Tft.TFTinit();                              //init TFT library
  screen.AddButton("Test", 50, 90, 30, 150, "Test Button", WHITE, BLUE);
  //btn.SetName("Test");
  //btn.SetColor(WHITE, BLUE);
  //btn.SetPos(50, 90);
  //btn.SetSize(30, 150);
  //btn.SetText("Test Button");
  //btn.Draw();
  
}

void loop() {

// myScreen.setCursor(50, 50);
// myScreen.drawCircle(20, 20, 20, 128);
// myScreen.circle(100, 100, 10);  

  // Read the value of the sensor on A0
  // String sensorVal1 = String(analogRead(A9));
  // String sensorVal2 = String(analogRead(A10));
  
  auto p = myTouch.getPoint();
  
   if (p.z > __PRESSURE) {
        ShowSerial.print("Raw X = "); ShowSerial.print(p.x);
        ShowSerial.print("\tRaw Y = "); ShowSerial.print(p.y);
        ShowSerial.print("\tPressure = "); ShowSerial.println(p.z);
    }

  
  p.x = map(p.x, TS_MINX, TS_MAXX, 0, 240);
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, 320);

  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  if (p.z > __PRESSURE) {
      ShowSerial.print("X = "); ShowSerial.print(p.x);
      ShowSerial.print("\tY = "); ShowSerial.print(p.y);
      ShowSerial.print("\tPressure = "); ShowSerial.println(p.z);
    Tft.fillCircle(p.x, p.y, 2000/p.z, WHITE);
    screen.Select(p);
  }
  
  //delay(50);
}
