/*************************************************
* Public Constants
*************************************************/
#ifndef __PITCHES_H__
#define __PITCHES_H__

#define NOTE_A5  880

#pragma endregion

#include "Arduino.h"
#include "Process.h"

class AudioAlarm : public Process
{
public:
	AudioAlarm(){}
	void Init(uint8_t pin);
	void Update(float temp);

private:
	uint8_t pin_;
	long last_note_time;
	const unsigned duration_ = 1000;
};
#endif