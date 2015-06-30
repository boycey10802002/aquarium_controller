#include <Wire.h>
#include <OneWire.h>

#include <Ethernet.h>
#include <EthernetUdp.h>
#include "NtpClient.h"
/*

#include <EthernetServer.h>
#include <EthernetClient.h>

#include <Dns.h>
#include <Dhcp.h>
*/
#include <SPI.h>
#include <SD.h>

#include <CmdMessenger.h>
#include <DallasTemperature.h>



#include "AquariumController.h"


#include "Process.h"
//#include "Alarm.h"

#include "TemperatureProcess.h"
#include "Display.h""
#include "LiquidCrystal_I2C.h"


//Temperature chip i/o
AquariumController controller;
//CmdMessenger* cmd_messenger = new CmdMessenger(Serial);

unsigned long prevous_sample_millis;
unsigned long sample_interval = 100;

bool aquire_data = true;
bool log_data = true;

enum commands
{
	kAcknowledge,
	kError	
};


/*
void attachCallbacks()
{
	cmd_messenger->attach(OnUnknownCommand);
	cmd_messenger->attach(OnArduinoReady);
}


// Callbacks ========================================
void OnUnknownCommand()
{
	cmd_messenger->sendCmd(kError, "Command without callback");
}

void OnArduinoReady()
{
	cmd_messenger->sendCmd(kAcknowledge, "Arduino Ready");
}
*/


void setup(void) {
	pinMode(4, OUTPUT);
	digitalWrite(4, HIGH);
	pinMode(10, OUTPUT);
	digitalWrite(10, HIGH);

	Serial.begin(115200);

	// Add new line to every command
	//cmd_messenger->printLfCr();
	//attachCallbacks();
	//cmd_messenger->sendCmd(kAcknowledge, "Arduino Started");



	Serial.print("Initializing SD card...");

	if (!SD.begin(4)) {
		Serial.println("Card failed, or not present");
		// don't do anything more:
		return;
	}
	Serial.println("card initialized.");

	controller.Init();
}

void loop(void) {
	//cmd_messenger.sendCmd(kAcknowledge, "LOOP");
	//cmd_messenger.feedinSerialData();
	controller.Update();
	controller.Log();

	delay(100); //here to slow execution
}

bool hasExpired(unsigned long &prevTime, unsigned long interval)
{
	if (millis() - prevTime > interval)
	{
		prevTime = millis();
		return true;
	}
	else
	{
		return false;
	}
}


