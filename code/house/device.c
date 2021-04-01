#include "device.h"
#include <stdio.h>
#include <string.h>

struct Device *pDevice = NULL;

void addToDeviceHandler(struct Device* device) {

	if(pDevice == NULL)
		pDevice = device;
	
	else {
		device->next = pDevice;
		pDevice = device;
	}
}

void printAllDevice() {

	struct Device *current = pDevice;
	while(current != NULL) {
		printf("Name: %s\n", current->name);
		current = current->next;
	}
}

struct Device* findUtilByName(char* name) {

	struct Device *current = pDevice;
	while(current != NULL)
	{
		if(strcmp(current->name, name) == 0)
			return current;

		current = current->next;
	}

	return NULL;
}
