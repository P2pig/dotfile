#include "device.h"
#include <wiringPi.h>

int pin25 = 25;

void GPIO25_Init() {
	if(wiringPiSetup() == -1)
		printf("init GPIO25 fail\n");
	pinMode(pin25, OUTPUT);
	digitalWrite(pin25, HIGH);
}

void GPIO25_Open() {
	digitalWrite(pin25, LOW);
}

void GPIO25_Close() {
	digitalWrite(pin25, HIGH);
}

struct Device gpio25 = { 
	.name = "GPIO25",
	.init = GPIO25_Init,
	.open = GPIO25_Open,
	.close = GPIO25_Close
};

void addGPIO25ToLink() {
	addToDeviceHandler(&gpio25);
}
