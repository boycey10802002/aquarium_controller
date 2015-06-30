// 
// 
// 
#include "SD.h"
#include "AquariumController.h"
//#include "Alarm.h"
#include "LiquidCrystal_I2C.h"

void AquariumController::Init()
{
	Serial.println(F("init start"));
	
	display_ = new Display();
	//alarm_ = new AudioAlarm();
	temperature_ = new TemperatureProcess();	
	
	processes[0] = display_;
	processes[1] = temperature_;
	//processes[2] = alarm_;
	
	display_->Init(this);	
	temperature_->Init(this);	
	//alarm_->Init(9);

	SD.begin(4);
	Serial.println(F("init finished"));
}


void AquariumController::Update()
{
	for (int i = 0; i < processes_count; i++)
	{
		processes[i]->Update();		
	}
}

void AquariumController::Log()
{
	for (int i = 0; i < processes_count; i++)
	{
		processes[i]->Log();
	}
}

String AquariumController::GetAlarms()
{
	String alarm_string = F("Alarms: ");
	
	if(temperature_alarm_)
	{
		alarm_string += F("Temp High");
	}

	else
	{
		alarm_string = F("Alarms: None");
	}

	return alarm_string;
}

void AquariumController::SetAlarm(AlarmTypes alarm_type)
{
	if (alarm_type == alarm_Temperature)
	{
		temperature_alarm_ = true;
	}
}

void AquariumController::ClearAlarm(AlarmTypes alarm_type)
{
	if (alarm_type == alarm_Temperature)
	{
		temperature_alarm_ = false;
	}
}