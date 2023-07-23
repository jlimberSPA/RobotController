// Visual Micro is in vMicro>General>Tutorial Mode
//
/*
	Name:       TouchScreenTest.ino
	Created:	6/4/2023 9:02:26 PM
	Author:     JOE-HP-LAPTOP\jmlma
*/

// Define User Types below here or use a .h file
//

// Define Function Prototypes that use User Types below here or use a .h file
//

// Define Functions below here or use other .ino or cpp files
//

// The setup() function runs once each time the micro-controller starts
#include <TFTv2.h>
#include <SeeedTouchScreen.h>
//Basic Colors
#define RED		0xf800
#define GREEN	0x07e0
#define BLUE	0x001f
#define BLACK	0x0000
#define YELLOW	0xffe0
#define WHITE	0xffff

//Other Colors
constexpr auto CYAN = 0x07ff;
#define BRIGHT_RED	0xf810
#define GRAY1		0x8410
#define GRAY2		0x4208
int ColorPaletteHigh = 30;
int color = WHITE;  //Paint brush color
unsigned int colors[8] = { BLACK, RED, GREEN, BLUE, CYAN, YELLOW, WHITE, GRAY1 };
SeeedTouchScreenNamespace::TouchScreen ts = SeeedTouchScreenNamespace::TouchScreen(XP, YP, XM, YM); //init TouchScreen port pins
void setup()
{
	Tft.TFTinit();  //init TFT library
	Serial.begin(115200);
	//Draw the pallet
	for (int i = 0; i < 8; i++) {
		Tft.fillRectangle(i * 30, 0, 30, ColorPaletteHigh, colors[i]);
	}
}

// Add the main program code into the continuous loop() function
void loop()
{
	// a point object holds x y and z coordinates.
	SeeedTouchScreenNamespace::Point p = ts.getPoint();

	//map the ADC value read to into pixel co-ordinates

	p.x = map(p.x, TS_MINX, TS_MAXX, 0, 240);
	p.y = map(p.y, TS_MINY, TS_MAXY, 0, 320);

	// we have some minimum pressure we consider 'valid'
	// pressure of 0 means no pressing!

	if (p.z > __PRESURE) {
		// Detect  paint brush color change
		if (p.y < ColorPaletteHigh + 2) {
			color = colors[p.x / 30];
		}
		else {
			Tft.fillCircle(p.x, p.y, 2, color);
		}
	}
}