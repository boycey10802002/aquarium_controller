// 
// 
// 
#include "Ethernet.h"
#include "EthernetUDP.h"
#include "SD.h"

#include "AquariumController.h"
#include "LiquidCrystal_I2C.h"
//#include "NtpClient.h"

#include "Display.h"





void Display::Init(AquariumController* controller)
{
	Process::Init(controller);
	update_interval_ = 100;
	updates_before_full_refresh = screen_reset_interval_in_seconds / (update_interval_ / 1000.0);	
	lcd_ = new LiquidCrystal_I2C(0x27, 20, 4);
	lcd_->init();
	lcd_->backlight();
	lcd_->clear();
	lcd_->print(F("GO"));

	//ntp_client_.Init();
	//seconds_ = ntp_client_.GetTime();
	MakeCustomCharacters();
}


void Display::Update()
{	
	if (UpdateReady()) {
		if (update_count_ > updates_before_full_refresh) {
			update_count_ = 0;
			lcd_->clear();
		}

		lcd_->setCursor(0, 0);		
		lcd_->write(1);
		lcd_->print(controller_->AsFahrenheit());
		lcd_->write(2);

		lcd_->setCursor(11, 0);	
		lcd_->write(0);
		lcd_->print(MillisToTime());		
		
		
		lcd_->setCursor(0, 1);
		lcd_->print(NtpTime());
				
		lcd_->setCursor(0, 2);
		lcd_->print(GetFileSizesAsString());

		// for card data
		lcd_->setCursor(0, 3);
		lcd_->print(controller_->GetAlarms());
		
	}
}

String Display::NtpTime()
{
	millis_accumulator_ += millis() - last_millis_;
	last_millis_ = millis();
	bool just_ticked_seconds = false;
	
	if (millis_accumulator_ > millis_per_second)
	{
		Serial.print("Accumulator: ");
		Serial.println(millis_accumulator_);
		just_ticked_seconds = true;
		seconds_++;
		millis_accumulator_ -= millis_per_second;
		Serial.print("Accumulator: ");
		Serial.println(millis_accumulator_);
	}
	
	String msg;
	if (just_ticked_seconds)
	{
		if ((seconds_ % 1000) == 0) {
			Serial.print("Update UDP: ");
			Serial.println(seconds_);
			EthernetUDP udp;
			seconds_ = ntp_client_.GetTime();
		}
	}
	return String(seconds_);
}

String Display::MillisToTime()
{
	/*
	unsigned long unix_time = 123;
	EthernetUDP udp;
	unix_time = NtpClientClass::ntpUnixTime(udp);
	delay(500);
	*/
	unsigned long time = millis() / 1000;
	unsigned hours = time / (3600);
	unsigned short minutes = time / (60) % 60;
	unsigned short seconds = time % 60;

	String time_string = "";
	
	time_string += PadZeros(hours);
	time_string += ":";
	time_string += PadZeros(minutes);
	time_string += ":";
	time_string += PadZeros(seconds);
	return time_string;
}

String Display::PadZeros(int number)
{
	String num = "";
	if (number < 10) { num += "0"; }
	num += String(number);
	return num;
}

void Display::MakeCustomCharacters()
{
	uint8_t clock[] = {	B01110,
											B11011,
											B11011,
											B11011,
											B11001,
											B11111,
											B11111,
											B01110};
	lcd_->createChar(0, clock);

	uint8_t thermometer[] = { B00100,
														B01010,
														B01010,
														B01010,
														B01010,
														B10001,
														B10001,	
														B01110};
	lcd_->createChar(1, thermometer);


	uint8_t deg_f_symbol[] = {	B01000,
															B10100,
															B01000,
															B00111,
															B00100,
															B00111,
															B00100,
															B00100 };
	lcd_->createChar(2, deg_f_symbol);
}

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
				suffix = F(" MB");
			}
			else if (file_size > 1024) {
				file_size = (file_size / 1024);
				suffix = F(" MB");
			}
		}
		log.close();
	}
	String out = F("Size: ");
	out += file_size;
	out += suffix;
	return out;
}


String Display::GetAlarms()
{
	return this->controller_->GetAlarms();
}