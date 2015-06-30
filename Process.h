// Process.h

#ifndef _PROCESS_h
#define _PROCESS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class AquariumController; //forward dec.

class Process
{
 protected:	 
	 unsigned long update_interval_;
	 unsigned long last_update_time_;

	 unsigned long logging_interval_;
	 unsigned long last_log_time_;


	 AquariumController* controller_;

 public:
	 virtual void Init(AquariumController* controller);
	virtual void Update() {}
	virtual void Log() {}
	virtual void Alarm() {}
	bool UpdateReady();
	bool LogReady();


private:
	
};

#endif

