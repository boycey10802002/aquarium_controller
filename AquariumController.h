// AquariumController.h

#ifndef _AQUARIUMCONTROLLER_h
#define _AQUARIUMCONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

//#include "Alarm.h"
#include "TemperatureProcess.h"
#include "Display.h"
#include "PowerPlugs.h"
#include "AquariumKeypad.h"

//#define MAX_CALLBACKS 10

enum AlarmTypes
{
	alarm_Temperature = 0,
	ALARM_COUNT
};

const unsigned short processes_count = 4;

class AquariumController
{
 protected:


 public:
	 AquariumController();
	void Init();
	void Update();
	void Log();
	//CallbackInterface* OnUpdate[MAX_CALLBACKS];
	
	void DoingTheThings();


	float AsFahrenheit() { return temperature_.AsFahrenheit(); }
	float AsCelsius() { return temperature_.AsCelsius(); }
	String GetAlarms();

	void SetAlarm(AlarmTypes alarm_type);	
	void ClearAlarm(AlarmTypes alarm_type);
	void ClearAllAlarms();

	// Commands for controlling and getting info from the computer ==========
	void SetPlugState(int plug_id, bool plug_state);	
	//void DisplayMessage(String msg);
	float GetTemp();

	void ProcessKeypad(char key);

private:
	
	//AudioAlarm* alarm_;
	TemperatureProcess temperature_;
	Display display_;
	PowerPlugsClass power_plug_;
	AquariumKeypad keypad_;
	
	
	Process* processes[processes_count];
	bool temperature_alarm_;
	
};
#endif

