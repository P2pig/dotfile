/*
 * Test pins
 * ./a.out [gio name] [CON]
 * ./a.out 1 1  // pin 1 HIHG	OUTPUT
 * ./a.out 1 0  // pin 1 LOW	OUTPUT
 * ./a.out 1 3  // pin 1	INPUT
 */

#include <stdio.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int pin = atoi(argv[1]);
	int volt = atoi(argv[2]);

	if(wiringPiSetup() == -1)
		printf("init failed.");

	if(volt == 0) {
		pinMode(pin, OUTPUT);
		digitalWrite(pin, LOW);
	} else if(volt == 1) {
		pinMode(pin, OUTPUT);
		digitalWrite(pin, HIGH);
	} else if(volt == 3){
		pinMode(pin, INPUT);
	}

	system("gpio readall");
	return 0;
}
