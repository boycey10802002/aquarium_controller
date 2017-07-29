// 
// 
// 
#include "Utils.h"

#include <Time.h>
#include "TimeAlarms.h"
#include "Clock.h"




//void AquariumClock::init(){}
	


void AquariumClock::SetTime(DateTime n)
{	
	Serial.print(n.year());
	Serial.print("-");
	Serial.print(n.month());
	Serial.print("-");
	Serial.print(n.day());
	Serial.print(" ");
	Serial.print(n.hour());
	Serial.print(":");
	Serial.print(n.minute());
	Serial.print(":");
	Serial.println(n.second());

	/*


	Serial.println("Initializing time to roughly:");
	Serial.println(__DATE__);
	String ts = __TIME__;
	int split1 = ts.indexOf(':');
	int split2 = ts.indexOf(':', split1 + 1);
	Serial.println(split1);
	Serial.println(split2);


	int h = atoi(ts.substring(0, split1).c_str());
	int m = atoi(ts.substring(split1 + 1, split2).c_str());
	int s = atoi(ts.substring(split2 + 1).c_str());
	


	Serial.println(__TIME__);
	*/
	//setTime(h, m, s, 9, 4, 2016);	
	setTime(n.hour(), n.minute(), n.second(), n.day(), n.month(), n.year());

	timeStatus_t time_status = timeStatus();
	switch (time_status)	{
	case timeNotSet:
		Serial.println("NOT SET");
		break;
	case timeNeedsSync:
		Serial.println("NEED SYNC");
		break;
	case timeSet:
		Serial.println("ALL GOOD");
		break;
	}
}


void AquariumClock::MonthIncrease() {
	Serial.println("Month Increase");
	setTime(hour(), minute(), second(), day(), month() + 1, year());
}

void AquariumClock::MonthDecrease() {
	Serial.println("Month Decrease");
	setTime(hour(), minute(), second(), day(), month() - 1, year());
}


void AquariumClock::DayIncrease() {
	Serial.println("Day Increase");
	setTime(hour(), minute(), second(), day() + 1, month(), year());
}

void AquariumClock::DayDecrease() {
	Serial.println("Day Decrease");
	setTime(hour(), minute(), second(), day() - 1, month(), year());
}


void AquariumClock::HourIncrease() {
	Serial.println("Hour Increase");
	setTime(hour() + 1, minute(), second(), day(), month(), year());
}
void AquariumClock::HourDecrease() {
	Serial.println("Hour Decrease");
	setTime(hour() - 1, minute(), second(), day(), month(), year());
}


void AquariumClock::MinuteIncrease() {
	Serial.println("Minute Increase");
	setTime(hour(), minute() + 1, second(), day(), month(), year());
}
void AquariumClock::MinuteDecrease() {
	Serial.println("Minute Decrease");
	setTime(hour(), minute() - 1, second(), day(), month(), year());
}


String AquariumClock::DateString()
{
	String msg = "";
	if (timeStatus() == timeSet)
	{
		msg += year();
		msg += "/";
		msg += month();
		msg += "/";
		msg += day();
	}
	else
	{
		msg = "NoSync";
	}
	return msg;
}

String AquariumClock::TimeString()
{
	String msg;

	if (true /*timeStatus() == timeSet*/)
	{
		msg += UtilsClass::PadIntWithZeros(hour());
		msg += ":";
		msg += UtilsClass::PadIntWithZeros(minute());
		msg += ":";
		msg += UtilsClass::PadIntWithZeros(second());
	}

	else
	{
		//msg = "No Sync";
		//EthernetUDP udp;
		//setTime(ntp_client_.GetTime());
	}

	return String(msg);
}

