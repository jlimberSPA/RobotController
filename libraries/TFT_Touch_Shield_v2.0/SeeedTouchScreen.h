/*
	SeeedTouchScreen.h - Library for 4-line resistance touch screen.
	Modified by loovee Aug 12, 2012.
	(c) ladyada / adafruit
	Code under MIT License.
*/
#define __PRESSURE 10
#define __PRESURE __PRESSURE    // Previous misspelled macro left for backwards compatibility

#ifndef SeeedTouchScreen
#define SeeedTouchScreen

#if defined(PORT_IOBUS)
// On SAMD21, redefine digitalPinToPort() to use the slightly-faster
// PORT_IOBUS rather than PORT (not needed on SAMD51).
#undef  digitalPinToPort
#define digitalPinToPort(P) (&(PORT_IOBUS->Group[g_APinDescription[P].ulPort]))
#endif // end PORT_IOBUS

namespace SeeedTouchScreenNamespace
{
	class Point {
	public:
		int x, y, z;

	public:
		Point(void);
		Point(int x, int y, int z);
		bool operator==(Point);
		bool operator!=(Point);
	};

	class TouchScreen {
	private:
		unsigned char _xp;
		unsigned char _yp;
		unsigned char _xm;
		unsigned char _ym;

	public:
		TouchScreen(unsigned char xp, unsigned char yp, unsigned char xm, unsigned char ym) : _xp(xp), _yp(yp), _xm(xm), _ym(ym) {};
		bool isTouching(void);
		Point getPoint();
	};
}
#endif // !SeeedTouchScreen
