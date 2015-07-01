// Display.h

#ifndef _DISPLAY_h
#define _DISPLAY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "SD.h"
#include "Process.h"
#include "LiquidCrystal_I2C.h"
#include "NtpClient.h"

class AquariumController; // forward dec

class Display : public Process
{
 protected:
public:
	virtual void Init(AquariumController* ac);
	virtual void Update();
	virtual void Log() {}
	virtual void Alarm(){}


private:
	String MillisToTime();
	String GetFileSizesAsString();
	String GetAlarms();
	String PadZeros(int);
	void MakeCustomCharacters();
	String NtpTime();
	
	LiquidCrystal_I2C* lcd_;
	NtpClientClass ntp_client_;


	const unsigned short screen_reset_interval_in_seconds = 10;	
	unsigned update_count_;
	unsigned updates_before_full_refresh;
	unsigned long seconds_;
	unsigned millis_accumulator_;
	unsigned long last_millis_;
	const unsigned millis_per_second = 1000;
};

#endif

