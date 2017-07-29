// 
// 
// 
#include "Time.h"
#include "Alarm.h"
#include "TimeAlarms.h"

#include "SD.h"
#include "AquariumController.h"
#include <LiquidCrystal_I2C/LiquidCrystal_I2C.h>
#include "PowerPlugs.h"


AquariumController::AquariumController()
{
	for (int i = 0; i < processes_count; i++) {
		processes[i] = NULL;
	}
}

void AquariumController::Init()
{
	Serial.println(F("init start"));	

	processes[0] = &display_;
	processes[1] = &temperature_;
	processes[2] = &keypad_;
	processes[3] = &power_plug_;
	
	
	
	for(int i = 0; i < processes_count; i++) {
		if (processes[i] != NULL) {
			processes[i]->Init(this);
		}
	}

	//Test
	//Alarm.timerRepeat(0, 0, 5, (OnTick_t)&PowerPlugsClass::Power4Toggle);
	
	// Whites On/off
	Alarm.alarmRepeat(12, 0, 0, (OnTick_t)&PowerPlugsClass::Power1On);
	Alarm.alarmRepeat(6, 1, 0, (OnTick_t)&PowerPlugsClass::Power1Off);
	
	// Blues On/Off
	Alarm.alarmRepeat(11, 0, 0, (OnTick_t)&PowerPlugsClass::Power2On);
	Alarm.alarmRepeat(7, 1, 0, (OnTick_t)&PowerPlugsClass::Power2Off);
	

	// Moon On/Off	
	Alarm.alarmRepeat(0, 0, 0, (OnTick_t)&PowerPlugsClass::Power3On);
	Alarm.alarmRepeat(6, 0, 0, (OnTick_t)&PowerPlugsClass::Power3Off);	


	//SD.begin(4);
	//Serial.println(F("init finished"));
}

void AquariumController::DoingTheThings() {
	Serial.println("DOING THE THINGS!");
}

void AquariumController::Update()
{
	for (int i = 0; i < processes_count; i++)
	{
		if (processes[i] != NULL) {
			if (processes[i]->UpdateReady()) {

				//unsigned long start_of_update = millis();
				processes[i]->Update();
				/*
				//unsigned long delta = millis() - start_of_update;
				Serial.print("Process [");
				Serial.print(processes[i]->GetName());
				Serial.print("]: ");
				Serial.print("Updated\n");
				//Serial.print(delta);
				//Serial.println("ms");
				*/
			}
		}
		else {
			Serial.print(i);
			Serial.print(" is NULL\n");
		}
	}
	//Serial.println("");
	

}


void AquariumController::Log() {
	//Serial.println(F("LOGGING DISABLED"));
	/*
	for (int i = 0; i < processes_count; i++)
	{
		processes[i]->Log();
	}
	*/
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

void AquariumController::SetPlugState(int plug_id, bool plug_state)
{
	switch (plug_id)
	{
	case 0:
		if (plug_state) power_plug_.Power1On();
		else power_plug_.Power1Off();
		break;

	case 1:
		if (plug_state) power_plug_.Power2On();
		else power_plug_.Power2Off();
		break;

	case 2:
		if (plug_state) power_plug_.Power3On();
		else power_plug_.Power3Off();
		break;

	case 3:
		if (plug_state) power_plug_.Power4On();
		else power_plug_.Power4Off();
		break;
	}	
}

/*
void AquariumController::DisplayMessage(String msg)
{
	display_.DisplayMessage(msg);
}
*/

float AquariumController::GetTemp()
{
	return temperature_.AsFahrenheit();
}



void AquariumController::ProcessKeypad(char key) {

	switch (key) {

		// TIME INCREASE ==========================================
	case '0':
		Serial.print("Month+");
		AquariumClock::MonthIncrease();
		break;
	case '1':
		Serial.print("Day+");
		AquariumClock::DayIncrease();
		break;
	case '2':
		Serial.print("Hour+");
		AquariumClock::HourIncrease();
		break;
	case '3':
		Serial.print("Minute+");
		AquariumClock::MinuteIncrease();
		break;


		// TIME DECREASE ==========================================
	case '4':
		AquariumClock::MonthDecrease();
		break;
	case '5':
		AquariumClock::DayDecrease();
		break;
	case '6':
		AquariumClock::HourDecrease();
		break;
	case '7':
		AquariumClock::MinuteDecrease();
		break;

		
		// POWER PLUGS ==========================================
	case 'C':
		power_plug_.Power1Toggle();
		break;
	case 'D':
		power_plug_.Power2Toggle();
		break;
	case 'E':
		power_plug_.Power3Toggle();
		break;
	case 'F':
		power_plug_.Power4Toggle();
		break;
	}


}
