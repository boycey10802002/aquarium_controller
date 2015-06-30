#include "Alarm.h"


void AudioAlarm::Init(uint8_t pin)
{
	pin_ = pin;
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
}

void AudioAlarm::Update(float temp)
{
	if ((temp < 78.0) || (temp > 82.0))
	{
		if (millis() > last_note_time + duration_)
		{
			tone(pin_, NOTE_A5, duration_ / 2);
			last_note_time = millis();
		}
	}
}
