#include "device.h"
#include <wiringPi.h>

int pin6 = 6;

void GPIO6_Init() {
	if(wiringPiSetup() == -1)
		printf("init GPIO6 fail\n");
	pinMode(pin6, OUTPUT);
	digitalWrite(pin6, HIGH);
}

void GPIO6_Open() {
	digitalWrite(pin6, LOW);
}

void GPIO6_Close() {
	digitalWrite(pin6, HIGH);
}

struct Device gpio6 = { 
	.name = "GPIO6",
	.init = GPIO6_Init,
	.open = GPIO6_Open,
	.close = GPIO6_Close
};

void addGPIO6ToLink() {
	addToDeviceHandler(&gpio6);
}
