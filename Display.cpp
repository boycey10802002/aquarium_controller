#include "Ethernet.h"
#include "EthernetUDP.h"
#include "SD.h"

#include "AquariumController.h"
//#include "LiquidCrystal_I2C.h"
#include <Wire.h>
#include <LiquidCrystal_I2C/LiquidCrystal_I2C.h>
//#include "NtpClient.h"
#include "Clock.h"
#include "Display.h"

Display::Display() : Process("Display") {}

void Display::Init(AquariumController* controller)
{
	update_count_ = 0;
	Process::Init(controller);
	SetUpateInterval(100);
	

	//lcd_ = new LiquidCrystal_I2C(0x27);
	lcd_ = new LiquidCrystal_I2C(0x27, 2, 1, 0, 4, 5,6,7,3, POSITIVE );
	lcd_->begin(20, 4, LCD_5x8DOTS);
	lcd_->backlight();
	lcd_->clear();
	
	//lcd_->print(F("Initializing NTP..."));
	//ntp_client_.Init();
	//AquariumClock::SetTime();

	//setSyncProvider(TimeString);
	MakeCustomCharacters();
	lcd_->clear();
}


void Display::Update()
{	
	update_count_++;
		
	// Time and Date
	DisplayTime(0, 0);
	
	//Temperatures
	DisplayTemp(0, 1);				
	DisplayFans(12, 1);

	// for card data	
	DisplayStorageStats(0, 2);	
	
	// Alarms
	DisplayAlarm(0,3);
}


void Display::DisplayTime(byte col, byte row) {
	ClearSection(col, row, 18);

	lcd_->setCursor(col, row);
	lcd_->print(AquariumClock::DateString());

	lcd_->setCursor(col+11, row);
	lcd_->write(uint8_t(0));
	lcd_->print(AquariumClock::TimeString());
}

void Display::DisplayTemp(uint8_t col, uint8_t row) {	
	ClearSection(col, row, LCD_WIDTH);
	lcd_->setCursor(0, 1);	
	lcd_->write(1);
	lcd_->print(controller_->AsFahrenheit());
	lcd_->write(2);
}

void Display::DisplayFans(byte col, byte row) {
	ClearSection(col, row, 8);
	lcd_->setCursor(col, row);
	lcd_->print("Fans:On");
}


void Display::DisplayStorageStats(byte col, byte row) {
	ClearSection(col, row, LCD_WIDTH);
	lcd_->setCursor(0, 2);
	lcd_->print(GetFileSizesAsString());
}

void Display::DisplayAlarm(byte col, byte row){
	ClearSection(col, row, LCD_WIDTH);
	lcd_->setCursor(col, row);
	lcd_->print(controller_->GetAlarms());
}

void Display::ClearSection(uint8_t col, uint8_t row_start, uint8_t row_end) {
	if ((update_count_ % screen_refresh_interval) == 0)	{
		lcd_->setCursor(col, row_start);
		byte c = row_start;
		while (c <= row_end) {
			lcd_->write(' ');
			c++;
		}
	}
}


// *** Accessors and formatters ***

String Display::GetFileSizesAsString()
{
	/*
	SdVolume volume;
	Sd2Card* card = volume.sdCard();
	SdFile sd_file;
	sd_file.openRoot(volume);


	if (card->cardSize() > 0)
	{

	uint32_t volume_size = card->cardSize();
	//volume_size *= volume.clusterCount();
	//volume_size *= 512;
	volume_size /= 1024;
	//volume_size /= 1024;

	}
	else
	{
	lcd_->clear();
	lcd_->print(F("Card is unreadable"));
	}
	*/
	unsigned long file_size = 0;
	String suffix = F(" Bytes");
	/*
	if (SD.exists(TEMPERATURE_FILEPATH))
	{
		File log = SD.open(TEMPERATURE_FILEPATH, FILE_WRITE);
		if (!log) {
			return F("Can't open file");
		}
		else {
			file_size = log.size();

			if (file_size > 1048576) {
				file_size = file_size / 1048576;
				suffix = F("MB");
			}
			else if (file_size > 1024) {
				file_size = (file_size / 1024);
				suffix = F("MB");
			}
		}
		log.close();
	}
	String out = F("Size:");
	out += file_size;
	out += suffix;
	*/
	return "CARD DISABLED"; //out;
}

String Display::GetAlarms()
{
	return this->controller_->GetAlarms();
}

void Display::MakeCustomCharacters()
{
	uint8_t clock[] = {
		0x0E,		// B01110
		0x1B,		// B11011
		0x1B,		// B11011
		0x1B,		// B11011
		0x19,		// B11001
		0x1F,		// B11111
		0x1F,		// B11111
		0x0E};	// B01110
	lcd_->createChar(0, clock);

	uint8_t thermometer[] = {
		0x04,		// B00100
		0x0A,		// B01010
		0x0A,		// B01010
		0x0A,		// B01010
		0x0A,		// B01010
		0x11,		// B10001
		0x11,		// B10001
		0x0E };	// B01110
	lcd_->createChar(1, thermometer);


	uint8_t deg_f_symbol[] = {
		0x08,		// B01000
		0x14,		// B10100
		0x08,		// B01000
		0x07,		// B00111
		0x04,		// B00100
		0x07,		// B00111
		0x04,		// B00100
		0x04 };	// B00100
	lcd_->createChar(2, deg_f_symbol);
}