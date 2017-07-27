// 
// 
// 
#include "AquariumController.h"
#include "Clock.h"
#include "PowerPlugs.h"
#include "AquariumKeypad.h"


AquariumKeypad::AquariumKeypad() : Process("Keypad"), keypad_(NULL), last_update(0) {}

void AquariumKeypad::Init(AquariumController* controller) {
	Process::Init(controller);
	SetUpateInterval(1);	
	keypad_ = new Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);	
}

void AquariumKeypad::Update() {	
	//Serial.println(millis());
	//Serial.println(" - keypad_->Update");
	if (keypad_ != NULL) {
		//Serial.println(keypad_->numKeys());
		char key = keypad_->getKey();
		if (key != NO_KEY)
		{
			Serial.println(key);
			controller_->ProcessKeypad(key);
		
		}
		// Serial.println(keypad_->numKeys());
		/*
		char key = keypad_->getKey();

		if (key != NO_KEY)
		{

		//Serial.println(key);
		}
		*/
	}
}

void AquariumKeypad::addKeypadReference(Keypad* keypad) {
	keypad_ = keypad;
}

void ProcesKeyPress() {

}