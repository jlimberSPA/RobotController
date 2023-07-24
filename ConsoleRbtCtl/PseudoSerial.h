#ifndef _PSEUDOSERIAL_H
#define _PSEUDOSERIAL_H

#include <iostream>

const char* F(const char* aTxt) { return aTxt; }

class PseudoSerial
{
public:
	static void print(const char* aTxt);
	static void println(const char* aTxt);

	static void print(int aInt);
	static void println(int aInt);
};
#endif