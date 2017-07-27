// 
// 
// 

#include "AquariumController.h"
#include "Process.h"

void Process::Init(AquariumController* controller)
{
	initialized_ = true;
	controller_ = controller;
	update_interval_ = 1000;
	logging_interval_ = 60000; // 30 sec
	
}


bool Process::UpdateReady()
{
	if (millis() > last_update_time_ + update_interval_)
	{
		last_update_time_ = millis();
		return true;
	}
	return false;
}

/*
bool Process::LogReady()
{
	if (millis() > last_log_time_ + logging_interval_)
	{
		last_log_time_ = millis();
		return true;
	}
	return false;
}
*/


void Process::SetUpateInterval(unsigned long interval) {
	update_interval_ = interval;
}

void Process::SetLoggingInterval(unsigned long interval) {
	logging_interval_ = interval;
}