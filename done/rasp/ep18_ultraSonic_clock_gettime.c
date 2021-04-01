/*
 * simple Ultrasonic Ranging Module HC - SR04
 */

#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

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

	struct timespec time1, time2;

	printf("start\n");
	while(1) {
		// trigger the Trig
		digitalWrite(TRIG, HIGH);
		usleep(10);
		digitalWrite(TRIG, LOW); 

		while(!(digitalRead(ECHO) == 1))
			clock_gettime(CLOCK_REALTIME, &time1);

		while(!(digitalRead(ECHO) == 0))
			clock_gettime(CLOCK_REALTIME, &time2);

		long start = time1.tv_sec *  1000000000 + time1.tv_nsec;
		long stop  = time2.tv_sec *  1000000000 + time2.tv_nsec;
		//float dis  = (float)(stop - start) / 1000000 * 34000 / 2;
		float dis  = (float)(stop - start) / 58309;

		printf("%0.2f cm\n", dis);

		usleep(500000);
	}

	return 0;
}



