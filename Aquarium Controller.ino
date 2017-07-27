#include <Wire.h>
#include <OneWire.h>

#include <Ethernet.h>
#include <EthernetUdp.h>

#include <Keypad.h>

#include <SPI.h>
#include <SD.h>

#include <CmdMessenger.h>
#include <DallasTemperature.h>

#include <Time.h>
#include <TimeAlarms.h>
#include <Keypad.h>

#include <LiquidCrystal_I2C/LiquidCrystal_I2C.h>


#include "Utils.h"
#include "Clock.h"
#include "NtpClient.h"

#include "Process.h"
#include "Display.h"
#include "TemperatureProcess.h"
#include "PowerPlugs.h"
#include "AquariumKeypad.h"

#include "AquariumController.h"


//Temperature chip i/o
AquariumController controller;
CmdMessenger cmd_messenger = CmdMessenger(Serial);
unsigned long prevous_sample_millis;
unsigned long sample_interval = 100;
bool aquire_data = true;
bool log_data = true;
bool process_queue = false;
int cooling_fans = true;

const int cooling_fan_pin = 8;

//Keypad keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

/* 
enum commands
{
	kAcknowledge = 0,
	kError,
	kSetPowerPlugState,
	kGetCurrentTemperature,
	kGetCurrentTemperatureResponse,
	KGetAllTemperatures,
	kSetCoolingFans
};

void attachCallbacks()
{
	cmd_messenger.attach(OnUnknownCommand);
	cmd_messenger.attach(OnArduinoReady);
	cmd_messenger.attach(kSetPowerPlugState, OnSetPowerPlugState);
	cmd_messenger.attach(kGetCurrentTemperature, OnGetCurrentTemperature);
	cmd_messenger.attach(KGetAllTemperatures, OnGetAllTemperatures);
	cmd_messenger.attach(kSetCoolingFans, SetCoolingFans);
}


// Callbacks ========================================
void OnUnknownCommand()
{
	cmd_messenger.sendCmd(kError, "Command without callback");
}

void OnArduinoReady()
{
	cmd_messenger.sendCmd(kAcknowledge, "Arduino Ready");
}

void OnSetPowerPlugState()
{
	//controller.DisplayMessage("SET POWER");
	uint8_t plug_id = cmd_messenger.readInt16Arg();
	bool plug_state = cmd_messenger.readBoolArg();
	controller.SetPlugState(plug_id, plug_state);
	cmd_messenger.sendCmd(kAcknowledge, " 'SET POWER' Command Acknowledged");
}

void OnGetCurrentTemperature() {
	Serial.println("GET TEMPERATURE");
	cmd_messenger.sendCmd(kAcknowledge, "GetTemp");
	//process_queue = true;
	SendTemperatures();
}

void OnGetAllTemperatures() { Serial.println("GET ALL TEMPERATURES"); }
*/

void OnSetCoolingFans()
{
	Serial.print("Set cooling fans: ");
	float temp = controller.GetTemp();
	if (temp < 80.0) {
		digitalWrite(cooling_fan_pin, LOW);
		Serial.println("OFF");
	}
	else if (temp > 80.5) {
		digitalWrite(cooling_fan_pin, HIGH);
		Serial.println("ON");
	}
}



// MAIN =============================================
void setup(void) {
	pinMode(4, OUTPUT);
	digitalWrite(4, HIGH);
	pinMode(10, OUTPUT);
	digitalWrite(10, HIGH);

	pinMode(cooling_fan_pin, OUTPUT);
	pinMode(cooling_fan_pin, HIGH);

	Serial.begin(115200);	


	AquariumClock::SetTime();
	
	//Serial.print("Initializing SD card...");

	/*
	if (!SD.begin(4)) {
		Serial.println("Card failed, or not present");
		while (1) { Serial.println("no dice"); }// don't do anything more:
		return;
	}
	Serial.println("card initialized.");
	*/

	controller.Init();

	Serial.println("DO THE THINGS!");	
	Alarm.timerRepeat(0, 0, 15, OnSetCoolingFans);	


	//Add new line to every command
	//cmd_messenger.printLfCr();
	//attachCallbacks();
	//cmd_messenger.sendCmd(kAcknowledge, "cmd_msgr_init");
}

void loop(void) {
	// ===========================================================================
	// Alarm.Delay IS EXTREMELY IMPORTANT TO HAVE HERE AS IT IS
	// the 'Update' or 'check for alarm' function for the TimeAlarms Class
	Alarm.delay(0); 
	// ===========================================================================

	//cmd_messenger.feedinSerialData();
	controller.Update();
	//controller.Log();	
	//ProcessCommandQueue();	
	//Alarm.delay(100);
}

/*
void SendTemperatures()
{
	cmd_messenger.sendCmdStart(kGetCurrentTemperatureResponse);	
	cmd_messenger.sendCmdArg("2015");
	cmd_messenger.sendCmdArg(12.34);
	cmd_messenger.sendCmdEnd();
	controller.SetPlugState(3, true);
}

void ProcessCommandQueue()
{
	/*
	if (process_queue)
	{
		SendTemperatures();
		process_queue = false;
	}
	* /
}

void SetCoolingFans()
{
	bool set_fan = cmd_messenger.readBoolArg();	
}
*/