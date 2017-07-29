#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Time.h"
#include "TimeAlarms.h"
#include "RTClib.h"

class AquariumClock
{
protected:
	
	//RTC_DS3231 _rtc;
	

public:
	//void init();
	void SetTime(DateTime time);
	
	static String TimeString();
	static String DateString();
	
	static void MonthIncrease();
	static void MonthDecrease();
	
	static void DayIncrease();
	static void DayDecrease();
	
	static void HourIncrease();
	static void HourDecrease();

	static void MinuteIncrease();
	static void MinuteDecrease();

	

	
};