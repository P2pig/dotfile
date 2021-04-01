#include "device.h"
#include <unistd.h>
#include <string.h>
#include <pthread.h>

pthread_t voiceThread;
pthread_t socketThread;

void cmdInvocation() {

	if(strcmp(LDV7_getcmd(), "number #1\n") == 0 ) {
		GPIO5_Open();
	} else if(strcmp(LDV7_getcmd(), "number #2\n") == 0 ) {
		GPIO6_Open();
	} else if(strcmp(LDV7_getcmd(), "number #3\n") == 0 ) {
		GPIO2_Open();
	} else if(strcmp(LDV7_getcmd(), "number #4\n") == 0 ) {
		GPIO25_Open();
	} else if(strcmp(LDV7_getcmd(), "Open all\n") == 0 ) {
		GPIO5_Open();
		GPIO6_Open();
		GPIO2_Open();
		GPIO25_Open();
	} else if(strcmp(LDV7_getcmd(), "Close all\n") == 0 ) {
		GPIO5_Close();
		GPIO6_Close();
		GPIO2_Close();
		GPIO25_Close();
	}
}

void voiceHandler() {
	while(LDV7_getfd() > 0) {
		LDV7_clearCMD();	// clear before reading
		LDV7_read();
		printf("%s\n", LDV7_getcmd());
		fflush(stdout);

		cmdInvocation();		
	}
}

void socketHandler() {

	while(socket_getfd() > 0) {
		socket_read();
		printf("socket cmd: %s\n", socket_getcmd());
	}
}

void initAllGPIO() {

	addGPIO5ToLink();
	addGPIO6ToLink();
	addGPIO25ToLink();
	addGPIO2ToLink();
	GPIO5_Init();
	GPIO6_Init();
	GPIO25_Init();
	GPIO2_Init();

}

int main()
{
	// init GPIO devices
//	initAllGPIO();

	// init cmd device
	LDV7_init();
	socket_init();

	pthread_create(&voiceThread, NULL, (void *) voiceHandler, NULL);
	pthread_create(&socketThread, NULL, (void *) socketHandler, NULL);

	pthread_join(voiceThread, NULL);
	pthread_join(socketThread, NULL);

	return 0;
}
