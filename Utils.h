// Utils.h
#pragma once


#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class UtilsClass
{
protected:
public:
	//void init();
	static String PadIntWithZeros(int);
};

extern UtilsClass Utils;