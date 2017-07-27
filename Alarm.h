/*************************************************
* Public Constants
************************************************* /
#pragma once


#define NOTE_A5  880

#include "Arduino.h"
#include "Process.h"

class AudioAlarm : public Process
{
public:
	AudioAlarm() : Process("AUDIO ALARM") {}
	void Init(uint8_t pin);
	void Update(float temp);

private:
	uint8_t pin_;
	long last_note_time;
	const unsigned duration_ = 1000;
};
*/