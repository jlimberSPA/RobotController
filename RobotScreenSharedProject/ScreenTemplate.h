// ScreenTemplate.h

#ifndef _SCREENTEMPLATE_h
#define _SCREENTEMPLATE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#endif
#include <TFTv2.h>
template <class T>
struct IScreen
{
	void TFTinit(void)
	{
		static_cast<T*>(this)->TFTinit(void);
	}
	void setPixel(INT16U poX, INT16U poY, INT16U color)
	{
		static_cast<T*>(this)->setPixel(INT16U poX, INT16U poY, INT16U color);
	}

	void fillScreen(INT16U XL, INT16U XR, INT16U YU, INT16U YD, INT16U color)
	{
		static_cast<T*>(this)->fillScreen(INT16U XL, INT16U XR, INT16U YU, INT16U YD, INT16U color);
	}

	void fillScreen(void)
	{
		static_cast<T*>(this)->fillScreen(void);
	}

	void drawCharLandscape(INT8U ascii, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor)
	{
		static_cast<T*>(this)->drawCharLandscape(INT8U ascii, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor);
	}

	void drawCharLandscapeBackwards(INT8U ascii, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor)
	{
		static_cast<T*>(this)->drawCharLandscapeBackwards(INT8U ascii, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor);
	}

	void drawCharLandscapeUpsideDown(INT8U ascii, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor)
	{
		static_cast<T*>(this)->drawCharLandscapeUpsideDown(INT8U ascii, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor);
	}

	void drawCharLandscapeUpsideDownBackwards(INT8U ascii, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor)
	{
		static_cast<T*>(this)->drawCharLandscapeUpsideDownBackwards(INT8U ascii, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor);
	}

	void drawCharLandscapeVertical(INT8U ascii, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor)
	{
		static_cast<T*>(this)->drawCharLandscapeVertical(INT8U ascii, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor);
	}

	void drawCharPortrait(INT8U ascii, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor)
	{
		static_cast<T*>(this)->drawCharPortrait(INT8U ascii, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor);
	}

	void drawCharPortraitUpsideDown(INT8U ascii, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor)
	{
		static_cast<T*>(this)->drawCharPortraitUpsideDown(INT8U ascii, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor);
	}

	void drawCharPortraitVertical(INT8U ascii, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor)
	{
		static_cast<T*>(this)->drawCharPortraitVertical(INT8U ascii, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor);
	}

	void drawCharPortraitBackwards(INT8U ascii, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor)
	{
		static_cast<T*>(this)->drawCharPortraitBackwards(INT8U ascii, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor);
	}

	void drawCharPortraitUpsideDownBackwards(INT8U ascii, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor)
	{
		static_cast<T*>(this)->drawCharPortraitUpsideDownBackwards(INT8U ascii, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor);
	}

	void drawString(char* string, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor, TextOrientation orientation)
	{
		static_cast<T*>(this)->drawString(char* string, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor, TextOrientation orientation);
	}

	void drawString(char* string, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor) {
		TextOrientation orientation = PORTRAIT;
		static_cast<T*>(this)->drawString(string, poX, poY, size, fgcolor, orientation);
	}

	void fillRectangle(INT16U poX, INT16U poY, INT16U length, INT16U width, INT16U color)
	{
		static_cast<T*>(this)->fillRectangle(INT16U poX, INT16U poY, INT16U length, INT16U width, INT16U color);
	}

	void drawLine(INT16U x0, INT16U y0, INT16U x1, INT16U y1, INT16U color)
	{
		static_cast<T*>(this)->drawLine(INT16U x0, INT16U y0, INT16U x1, INT16U y1, INT16U color);
	}

	void drawVerticalLine(INT16U poX, INT16U poY, INT16U length, INT16U color)
	{
		static_cast<T*>(this)->drawVerticalLine(INT16U poX, INT16U poY, INT16U length, INT16U color);
	}

	void drawHorizontalLine(INT16U poX, INT16U poY, INT16U length, INT16U color)
	{
		static_cast<T*>(this)->drawHorizontalLine(INT16U poX, INT16U poY, INT16U length, INT16U color);
	}

	void drawRectangle(INT16U poX, INT16U poY, INT16U length, INT16U width, INT16U color)
	{
		static_cast<T*>(this)->drawRectangle(INT16U poX, INT16U poY, INT16U length, INT16U width, INT16U color);
	}

	void drawCircle(int poX, int poY, int r, INT16U color)
	{
		static_cast<T*>(this)->drawCircle(int poX, int poY, int r, INT16U color);
	}

	void fillCircle(int poX, int poY, int r, INT16U color)
	{
		static_cast<T*>(this)->fillCircle(int poX, int poY, int r, INT16U color);
	}

	void drawTriangle(int poX1, int poY1, int poX2, int poY2, int poX3, int poY3, INT16U color)
	{
		static_cast<T*>(this)->drawTriangle(int poX1, int poY1, int poX2, int poY2, int poX3, int poY3, INT16U color);
	}

	INT8U drawNumber(long long_num, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor)
	{
		static_cast<T*>(this)->drawNumber(long long_num, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor);
	}

	INT8U drawFloat(float floatNumber, INT8U decimal, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor)
	{
		static_cast<T*>(this)->drawFloat(float floatNumber, INT8U decimal, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor);
	}

	INT8U drawFloat(float floatNumber, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor)
	{
		static_cast<T*>(this)->drawFloat(float floatNumber, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor);
	}

	static void static_func()
	{
		// ...
		T::static_sub_func();
		// ...
	}
};

struct TFT_Screen : public IScreen<TFT>
{
};

class Test_Screen
{
	TFT_Screen* myTFT = new TFT_Screen();
	void TestCalls()
	{
		myTFT->drawCircle(1, 2, 3, 4);
	}
};

/*
class TFT : public Base<TFT> {
public:

	//inline void sendCMD(INT8U index) {
		TFT_DC_LOW;
		TFT_CS_LOW;
		SPI.transfer(index);
		TFT_CS_HIGH;
	}

	inline void WRITE_DATA(INT8U data) {
		TFT_DC_HIGH;
		TFT_CS_LOW;
		SPI.transfer(data);
		TFT_CS_HIGH;
	}

	inline void sendData(INT16U data) {
		INT8U data1 = data >> 8;
		INT8U data2 = data & 0xff;
		TFT_DC_HIGH;
		TFT_CS_LOW;
		SPI.transfer(data1);
		SPI.transfer(data2);
		TFT_CS_HIGH;
	}

	void WRITE_Package(INT16U* data, INT8U howmany) {
		INT16U  data1 = 0;
		INT8U   data2 = 0;

		TFT_DC_HIGH;
		TFT_CS_LOW;
		INT8U count = 0;
		for (count = 0; count < howmany; count++) {
			data1 = data[count] >> 8;
			data2 = data[count] & 0xff;
			SPI.transfer(data1);
			SPI.transfer(data2);
		}
		TFT_CS_HIGH;
	}

	INT8U Read_Register(INT8U Addr, INT8U xParameter) {
		INT8U data = 0;
		sendCMD(0xd9);                                                      // ext command
		WRITE_DATA(0x10 + xParameter);                                      // 0x11 is the first Parameter
		TFT_DC_LOW;
		TFT_CS_LOW;
		SPI.transfer(Addr);
		TFT_DC_HIGH;
		data = SPI.transfer(0);
		TFT_CS_HIGH;
		return data;
	}
	void setCol(INT16U StartCol, INT16U EndCol);
	void setPage(INT16U StartPage, INT16U EndPage);
	void setXY(INT16U poX, INT16U poY);
	void setPixel(INT16U poX, INT16U poY, INT16U color);

	void fillScreen(INT16U XL, INT16U XR, INT16U YU, INT16U YD, INT16U color);
	void fillScreen(void);
	INT8U readID(void);

	void drawCharLandscape(INT8U ascii, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor);
	void drawCharLandscapeBackwards(INT8U ascii, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor);
	void drawCharLandscapeUpsideDown(INT8U ascii, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor);
	void drawCharLandscapeUpsideDownBackwards(INT8U ascii, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor);
	void drawCharLandscapeVertical(INT8U ascii, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor);

	void drawCharPortrait(INT8U ascii, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor);
	void drawCharPortraitUpsideDown(INT8U ascii, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor);
	void drawCharPortraitVertical(INT8U ascii, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor);
	void drawCharPortraitBackwards(INT8U ascii, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor);
	void drawCharPortraitUpsideDownBackwards(INT8U ascii, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor);

	void drawString(char* string, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor, TextOrientation orientation);
	void drawString(char* string, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor) {
		TextOrientation orientation = PORTRAIT;
		drawString(string, poX, poY, size, fgcolor, orientation);
	}

	void fillRectangle(INT16U poX, INT16U poY, INT16U length, INT16U width, INT16U color);

	void drawLine(INT16U x0, INT16U y0, INT16U x1, INT16U y1, INT16U color);
	void drawVerticalLine(INT16U poX, INT16U poY, INT16U length, INT16U color);
	void drawHorizontalLine(INT16U poX, INT16U poY, INT16U length, INT16U color);
	void drawRectangle(INT16U poX, INT16U poY, INT16U length, INT16U width, INT16U color);

	void drawCircle(int poX, int poY, int r, INT16U color);
	void fillCircle(int poX, int poY, int r, INT16U color);

	void drawTriangle(int poX1, int poY1, int poX2, int poY2, int poX3, int poY3, INT16U color);
	INT8U drawNumber(long long_num, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor);
	INT8U drawFloat(float floatNumber, INT8U decimal, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor);
	INT8U drawFloat(float floatNumber, INT16U poX, INT16U poY, INT16U size, INT16U fgcolor);

private:

	void reverse(char* string);
};
*/
