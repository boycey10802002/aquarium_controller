// 
// 
// 
#include "Time.h"
#include "TimeAlarms.h"
#include "PowerPlugs.h"
PowerPlugsClass::PowerPlugsClass() : Process("PowerPlugs") {}

void PowerPlugsClass::Init(AquariumController* controller_) {	
	Process::Init(controller_);

	pinMode(power1_pin, OUTPUT);
	digitalWrite(power1_pin, relay_off);
	pinMode(power2_pin, OUTPUT);
	digitalWrite(power2_pin, relay_off);
	pinMode(power3_pin, OUTPUT);
	digitalWrite(power3_pin, relay_off);
	pinMode(power4_pin, OUTPUT);
	digitalWrite(power4_pin, relay_off);

	//events[0] = new PowerEvent(power1_pin, TimeStamp(0, 0, 5), TimeStamp(0, 0, 10));

}

void PowerPlugsClass::Update(){
	
	for (unsigned i = 0; i < MAX_POWER_EVENTS; i++)
	{
		//if (events[i] != NULL) {
			//digitalWrite(events[i]->pin_, events[i]->IsOn());
		//}
	}
}


void PowerPlugsClass::Power1On() {
	plug1_state = relay_on;
	digitalWrite(power1_pin, plug1_state);
}

void PowerPlugsClass::Power1Off() {
	plug1_state = relay_off;
	digitalWrite(power1_pin, plug1_state);
}

void PowerPlugsClass::Power1Toggle() {
	plug1_state = (plug1_state == relay_on) ? relay_off : relay_on;
	digitalWrite(power1_pin, plug1_state);
}


// POWER PLUG 2
void PowerPlugsClass::Power2On() {
	plug2_state = relay_on;
	digitalWrite(power2_pin, plug2_state);
}

void PowerPlugsClass::Power2Off() {
	plug2_state = relay_off;
	digitalWrite(power2_pin, plug2_state);
}

void PowerPlugsClass::Power2Toggle() {
	plug2_state = (plug2_state == relay_on) ? relay_off : relay_on;
	digitalWrite(power2_pin, plug2_state);
}

// POWER PLUG 3
void PowerPlugsClass::Power3On() {
	plug3_state = relay_on;
	digitalWrite(power3_pin, plug3_state);
}

void PowerPlugsClass::Power3Off() {
	plug3_state = relay_off;
	digitalWrite(power3_pin, plug3_state);
}

void PowerPlugsClass::Power3Toggle() {
	plug3_state = (plug3_state == relay_on) ? relay_off : relay_on;
	digitalWrite(power3_pin, plug3_state);
}

// POWER PLUG 4
void PowerPlugsClass::Power4On() {
	plug4_state = relay_on;
	digitalWrite(power4_pin, plug4_state);
}

void PowerPlugsClass::Power4Off() {
	plug4_state = relay_off;
	digitalWrite(power4_pin, plug4_state);
}


void PowerPlugsClass::SetPowerState(uint8_t pin, uint8_t state) {
	digitalWrite(pin, state);
};

void PowerPlugsClass::Power4Toggle() {
	plug4_state = (plug4_state == relay_on) ? relay_off : relay_on;
	digitalWrite(power4_pin, plug4_state);
}


/*
bool PowerEvent::IsOn()
{
	bool is_on = false;
	Serial.print("current time: ");
	Serial.println(now());
	
	Serial.print("on time: ");
	Serial.println(on_time_);

	Serial.print("off time: ");
	Serial.println(off_time_);
	
	return is_on;
}
*/

PowerPlugsClass PowerPlugs;