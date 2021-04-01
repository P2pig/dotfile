#include <stdlib.h>
#include <stdio.h>

struct Device {
	char name[32];
	char cmd[32];
	char ip[15];
	char port[4];
	int pin;
	int fd;
	void (* init)();
	void (* open)();
	int (* read)();
	void (* close)();

	struct Device *next;
};

extern struct Device *pDevice;

void addToDeviceHandler(struct Device* device);
void printAllDevice();
struct Device* findUtilByName(char* name);

void addGPIO5ToLink();
void GPIO5_Init();
void GPIO5_Open();
void GPIO5_Close();

void addGPIO6ToLink();
void GPIO6_Init();
void GPIO6_Open();
void GPIO6_Close();

void addGPIO2ToLink();
void GPIO2_Init();
void GPIO2_Open();
void GPIO2_Close();

void addGPIO25ToLink();
void GPIO25_Init();
void GPIO25_Open();
void GPIO25_Close();

void LDV7_init();
void LDV7_Close();
int LDV7_read();
int LDV7_getfd();
char* LDV7_getcmd();
void LDV7_clearCMD();

void socket_init();
int socket_read();
int socket_getfd();
char* socket_getcmd();
void socket_Close();



