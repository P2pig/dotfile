#include "device.h"
#include <wiringPi.h>

int pin2 = 2;

void GPIO2_Init() {
	if(wiringPiSetup() == -1)
		printf("init GPIO2 fail\n");
	pinMode(pin2, OUTPUT);
	digitalWrite(pin2, HIGH);
}

void GPIO2_Open() {
	digitalWrite(pin2, LOW);
}

void GPIO2_Close() {
	digitalWrite(pin2, HIGH);
}

struct Device gpio2 = { 
	.name = "GPIO2",
	.init = GPIO2_Init,
	.open = GPIO2_Open,
	.close = GPIO2_Close
};

void addGPIO2ToLink() {
	addToDeviceHandler(&gpio2);
}
