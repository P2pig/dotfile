#include "device.h"
#include <wiringPi.h>

int pin5 = 5;

void GPIO5_Init() {
	if(wiringPiSetup() == -1)
		printf("init GPIO5 fail\n");
	pinMode(pin5, OUTPUT);
	digitalWrite(pin5, HIGH);
}

void GPIO5_Open() {
	digitalWrite(pin5, LOW);
}

void GPIO5_Close() {
	digitalWrite(pin5, HIGH);
}

struct Device gpio5 = { 
	.name = "GPIO5",
	.init = GPIO5_Init,
	.open = GPIO5_Open,
	.close = GPIO5_Close
};

void addGPIO5ToLink() {
	addToDeviceHandler(&gpio5);
}
