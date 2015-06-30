// 
// 
// 

#include "Process.h"
void Process::Init(AquariumController* controller)
{
	update_interval_ = 1000;
	logging_interval_ = 30000; // 30 sec
	controller_ = controller;
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

bool Process::LogReady()
{
	if (millis() > last_log_time_ + logging_interval_)
	{
		last_log_time_ = millis();
		return true;
	}
	return false;
}