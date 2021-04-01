#include "device.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

extern struct Device LDV7;

void LDV7_init() {
	int fd = open(LDV7.name, O_RDONLY);
	
	if(fd == -1)
		perror("/dev/ttyUSB0 does not exist");
	
	LDV7.fd = fd;
}

int LDV7_read() {

	int nread = read(LDV7.fd, LDV7.cmd, sizeof(LDV7.cmd));

	return nread;
}

int LDV7_getfd() {
	return LDV7.fd;
}

char* LDV7_getcmd() {
	return LDV7.cmd;
}

void LDV7_clearCMD() {
	memset(LDV7.cmd, '\0', sizeof(LDV7.cmd));
}

void LDV7_Close() {
	close(LDV7.fd);
}

struct Device LDV7 = {
	.name = "/dev/ttyUSB0",
	.init = LDV7_init,
	.read = LDV7_read,
	.close = LDV7_Close,
	.next = NULL
};

