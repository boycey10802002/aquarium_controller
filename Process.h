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
public:
	virtual void Init(AquariumController* controller);
	virtual void Update() {}
	//virtual void Log() {}
	bool UpdateReady();
	//bool LogReady();
	String GetName() { return name_; }

protected:
	Process(String name) : initialized_(false) {
		name_ = name;
	}
	void SetUpateInterval(unsigned long update_interval);
	void SetLoggingInterval(unsigned long log_interval);
	AquariumController* controller_;

private:
	unsigned long update_interval_;
	unsigned long last_update_time_;

	unsigned long logging_interval_;
	unsigned long last_log_time_;	
	
	bool initialized_;
	String name_;

	
};

#endif

