// PowerPlugs.h
#include "TimeAlarms.h"

#ifndef _POWERPLUGS_h
#define _POWERPLUGS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Process.h"
#include "Time.h"
#include "TimeAlarms.h"

class AquariumController;

enum RelayState {
	relay_on = LOW,
	relay_off = HIGH
};
/*
struct TimeStamp{
	unsigned long time_in_seconds_;
	TimeStamp(unsigned h, unsigned m, unsigned s)
	{
		time_in_seconds_ = (h * SECS_PER_HOUR) + (m * SECS_PER_MIN) + s;
	}

	time_t ToTime()	{ return time_in_seconds_; }
};


class PowerEvent
{
public:
	uint8_t pin_;
	time_t on_time_;
	time_t off_time_;
	bool IsOn();

	PowerEvent(uint8_t pin, TimeStamp on_time, TimeStamp off_time)
	{
		pin_ = pin;		
		on_time_ = on_time.ToTime();
		off_time_ = off_time.ToTime();
	}
};
*/
class PowerPlugsClass : public Process
{

protected:
	//uint8_t power1_pin;
	static const uint8_t power1_pin = 22;
	static const uint8_t power2_pin = 23;
	static const uint8_t power3_pin = 24;
	static const uint8_t power4_pin = 25;
	static const unsigned MAX_POWER_EVENTS = 10;

 public:
	 PowerPlugsClass();
	void Init(AquariumController* controller_);
	void Update();

	void Power1On();
	void Power1Off();
	void Power1Toggle();

	void Power2On();
	void Power2Off();
	void Power2Toggle();

	void Power3On();
	void Power3Off();
	void Power3Toggle();

	void Power4On();
	void Power4Off();
	void Power4Toggle();

	void SetPowerState(uint8_t pin, uint8_t state);

	//PowerEvent* events[MAX_POWER_EVENTS];
	RelayState plug1_state;
	RelayState plug2_state;
	RelayState plug3_state;
	RelayState plug4_state;
	
};

extern PowerPlugsClass PowerPlugs;

#endif

