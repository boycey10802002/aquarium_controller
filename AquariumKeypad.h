// Keypad.h
#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Process.h"
#include "Clock.h"
#include <Keypad/Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
static byte rowPins[ROWS] = { 30, 31, 32, 33 };
static byte colPins[COLS] = { 34, 35, 36, 37 };

static const char keys[ROWS][COLS] = {
	{ '0', '1', '2', '3' },
	{ '4', '5', '6', '7' },
	{ '8', '9', 'A', 'B' },
	{ 'C', 'D', 'E', 'F' }};

class AquariumController;
//typedef void(*KeyCallbackFunction) (void);

class AquariumKeypad : public Process {
public:
	AquariumKeypad();
	void Init(AquariumController* controller);
	void Update();
	void addKeypadReference(Keypad* keypad);
	void ProcesKeyPress();

private:
	Keypad* keypad_;
	unsigned long last_update;
public:
};

//extern KeypadClass Keypad;