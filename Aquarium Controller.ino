#include <Wire.h>
#include <OneWire.h>

#include <Ethernet.h>
#include <EthernetUdp.h>

#include <Keypad.h>

#include <SPI.h>
#include <SD.h>

//#include <CmdMessenger.h>
#include <DallasTemperature.h>

#include <Time.h>
#include <TimeAlarms.h>
#include <Keypad.h>

#include <LiquidCrystal_I2C/LiquidCrystal_I2C.h>
#include <RTClib.h>


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

AquariumClock clock;
RTC_DS3231 rtc;

unsigned long prevous_sample_millis;
unsigned long sample_interval = 100;
bool aquire_data = true;
bool log_data = true;
bool process_queue = false;
int cooling_fans = true;

const int cooling_fan_pin = 8;





void CheckClock() {
	Serial.print(year());
	Serial.print("-");
	Serial.print(month());
	Serial.print("-");
	Serial.print(day());
	Serial.print(" ");
	Serial.print(hour());
	Serial.print(":");
	Serial.print(minute());
	Serial.print(":");
	Serial.println(second());
}

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
	
	Serial.println("Loading RTC...");
	bool is_rtc_working = rtc.begin();
	delay(1000);
	Serial.println(rtc.now().minute());
	
	if(is_rtc_working == false) {		
		Serial.println("Cant find RTC");
		pinMode(13, OUTPUT);
		while(true){
			digitalWrite(13, HIGH);
			delay(100);
			digitalWrite(13, LOW);
			delay(100);
		}
	}

	clock.SetTime(rtc.now());	
	controller.Init();

	Serial.println("DO THE THINGS!");	
	Alarm.timerRepeat(0, 0, 15, OnSetCoolingFans);
	//Alarm.timerRepeat(0, 0, 33, CheckClock);
	
}

void loop(void) {
	// ===========================================================================
	// Alarm.Delay IS EXTREMELY IMPORTANT TO HAVE HERE AS IT IS
	// the 'Update' or 'check for alarm' function for the TimeAlarms Class
	Alarm.delay(0); 
	// ===========================================================================
	controller.Update();
}