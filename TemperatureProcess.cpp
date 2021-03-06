#include "SD.h"
#include "OneWire.h"
#include "AquariumController.h"
#include "Time.h"
#include "TemperatureProcess.h"


TemperatureProcess::TemperatureProcess() : Process("Temp Process") {}

void TemperatureProcess::Init(AquariumController* ac)
{
	Process::Init(ac);
	SetUpateInterval(10000);
	

	sensors_ = new DallasTemperature(new OneWire(DS18S20_Pin));
	
	sensors_->begin();


	Serial.print(sensors_->getDeviceCount());

	// report parasite power requirements
	if (!sensors_->getAddress(tank_thermometer_, 0))
	{
		Serial.println(F("Unable to find address for Device 0"));
	}

	Serial.println(F("Set Temp Probe Resolution: "));
	sensors_->setResolution(tank_thermometer_, 12);
}

void TemperatureProcess::Update()
{	
	sensors_->requestTemperatures();

	if (AsFahrenheit() > 83)
	{
		controller_->SetAlarm(alarm_Temperature);
	}
	else
	{
		controller_->ClearAlarm(alarm_Temperature);
	}
}

float TemperatureProcess::AsFahrenheit()
{
	return sensors_->getTempFByIndex(0);
}

float TemperatureProcess::AsCelsius()
{
	return sensors_->getTempCByIndex(0);
}

void TemperatureProcess::Log()
{
	Serial.println(F("LOGGING DISABLED"));
	/*
	if (LogReady())
	{
		if (SD.exists(TEMPERATURE_FILEPATH))
		{
			File log = SD.open(TEMPERATURE_FILEPATH, FILE_WRITE);
			if (log)
			{
				Serial.println(F("LOGGING!====="));
				log.print(now());
				log.print("\t");
				log.println(AsFahrenheit());				
			}
			else
			{
				Serial.println(F("LOG FAILED TO OPEN!!!"));
			}

			log.close();

		}
		else
		{
			Serial.println(F("logging file unaccessible!"));
			File log = SD.open(TEMPERATURE_FILEPATH, FILE_WRITE);
			log.println(F("I HAVE STUFF NOW!"));
		}
	}
	*/
}
