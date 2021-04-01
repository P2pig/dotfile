/*
 * simple Ultrasonic Ranging Module HC - SR04
 */

#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#define TRIG 4
#define ECHO 5

int main()
{
	if(wiringPiSetup() == -1)
	{	
		printf("init failed.");
		exit(-1);
	}

	// init
	pinMode(TRIG, OUTPUT);
	pinMode(ECHO, INPUT);
	digitalWrite(TRIG, LOW); // init low

	struct timeval time1, time2;

	printf("start\n");
	while(1) {
		// trigger the Trig
		digitalWrite(TRIG, HIGH);
		usleep(10);
		digitalWrite(TRIG, LOW); 

		while(!(digitalRead(ECHO) == 1))
			gettimeofday(&time1, NULL);

		while(!(digitalRead(ECHO) == 0))
			gettimeofday(&time2, NULL);

		long start = time1.tv_sec *  1000000 + time1.tv_usec;
		long stop  = time2.tv_sec *  1000000 + time2.tv_usec;
		float dis  = (float)(stop - start) / 1000000 * 34000 / 2;

		printf("%0.2f cm\n", dis);

		usleep(500000);
	}

	return 0;
}
