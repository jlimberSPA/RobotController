#include "PseudoSerial.h"

void PseudoSerial::print(const char* aTxt)
{
	std::cout << aTxt;
}

void PseudoSerial::println(const char* aTxt)
{
	std::cout << aTxt << std::endl;
}

void PseudoSerial::print(int aInt)
{
	char* str;
	_itoa_s(aInt, str, 10, 10);
	print(str);
}

void PseudoSerial::println(int aInt)
{
	char* str;
	_itoa_s(aInt, str, 10, 10);
	println(str);
}