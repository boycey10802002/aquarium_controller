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


	int update_count;

};

#endif

