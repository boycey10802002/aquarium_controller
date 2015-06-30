// TemperatureProcess.h

#ifndef _TEMPERATUREPROCESS_h
#define _TEMPERATUREPROCESS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "OneWire.h"
#include <DallasTemperature.h>
#include "Process.h"

typedef uint8_t ScratchPad[9];
class AquariumController; // forward dec

class TemperatureProcess : public Process
{
 protected:

	 
#define WRITE_SCRATCH    0x4E  // Write to EEPROM
#define COPYSCRATCH     0x48  // Copy EEPROM
#define CONFIGURATION   4
	 // Device resolution
#define TEMP_9_BIT  0x1F //  9 bit
#define TEMP_10_BIT 0x3F // 10 bit
#define TEMP_11_BIT 0x5F // 11 bit
#define TEMP_12_BIT 0x7F // 12 bit

 public:
	const unsigned short DS18S20_Pin = 2; //DS18S20 Signal pin on digital 2
	
	virtual void Init(AquariumController* controller);	
	virtual void Update();
	virtual void Log();
	virtual void Alarm() {}

	float AsFahrenheit();
	float AsCelsius();

private:
	ScratchPad scratch_pad_;
	byte temp_probe_addr_[8];
	
	//OneWire* one_wire_;
	DallasTemperature* sensors_;  // on digital pin 2
	DeviceAddress tank_thermometer_;

	#define TEMPERATURE_FILEPATH "temps.log"
};

#endif

