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

//#define MAX_CALLBACKS 10

enum AlarmTypes
{
	alarm_Temperature = 0,
	ALARM_COUNT
};

class AquariumController
{
 protected:


 public:
	 void Init();
	void Update();
	void Log();
	//CallbackInterface* OnUpdate[MAX_CALLBACKS];
	
	float AsFahrenheit() { return temperature_->AsFahrenheit(); }
	float AsCelsius() { return temperature_->AsCelsius(); }
	String GetAlarms();

	void SetAlarm(AlarmTypes alarm_type);	
	void ClearAlarm(AlarmTypes alarm_type);
	void ClearAllAlarms();

private:
	
	//AudioAlarm* alarm_;
	TemperatureProcess* temperature_;
	Display* display_;
	
	static const unsigned short processes_count = 2;
	Process* processes[processes_count];
	bool temperature_alarm_;
	
};
#endif

