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
#include "Time.h"
#include <LiquidCrystal_I2C/LiquidCrystal_I2C.h>
#include "NtpClient.h"

class AquariumController; // forward dec

class Display : public Process {
public:
	Display();
	virtual void Init(AquariumController* ac);
	virtual void Update();
	virtual void Log() {}
	//virtual void Alarm(){}
	
	//void DisplayMessage(String msg);


private:
	String MillisToTime();
	String GetFileSizesAsString();
	String GetAlarms();
	
	void MakeCustomCharacters();	
	

	LiquidCrystal_I2C* lcd_;
	NtpClientClass ntp_client_;


	void DisplayTime(byte col, byte row);
	void DisplayTemp(byte col, byte row);
	void DisplayFans(byte col, byte row);

	void DisplayStorageStats(byte col, byte row);
	void DisplayAlarm(byte col, byte row);
	void ClearSection(uint8_t col, uint8_t row_start, uint8_t row_end);



	const long utc_offset = -4UL;
	const unsigned short screen_reset_interval_in_seconds = 10;	
	unsigned long update_count_;
	unsigned updates_before_full_refresh;

	unsigned millis_accumulator_;
	const unsigned millis_per_second = 1000;
	static const byte LCD_WIDTH = 20;
	const unsigned screen_refresh_interval = 29;
	time_t prev_time_;
};

#endif

