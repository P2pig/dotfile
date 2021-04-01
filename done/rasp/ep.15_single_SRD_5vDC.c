/*
 * A simple single test of SRD-5VDC-SL-C
 */


#include <stdio.h>
#include <wiringPi.h>

#define LED 1

int main()
{
	if(wiringPiSetup() == -1)
		printf("init failed.");

	printf("LED: %d\n", LED);
	int input;
	pinMode(LED, OUTPUT);
	digitalWrite(LED, HIGH); // default off light

	while(1) {
		scanf("%d", &input);
		getchar();
		if(input == 1) {
			printf("high\n");
			digitalWrite(LED, HIGH);
		} else {
			printf("low\n");
			digitalWrite(LED, LOW);
		}
	}

	return 0;
}
