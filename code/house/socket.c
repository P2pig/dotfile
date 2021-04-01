#include "device.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while(0);

extern struct Device socketCtl;
struct sockaddr_in s_addr;
struct sockaddr_in c_addr;
unsigned int s_fd;
unsigned int c_fd;

void socket_init() {

	s_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(s_fd == -1)
		handle_error("socket");

	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(atoi(socketCtl.port));
	inet_aton(socketCtl.ip, &s_addr.sin_addr);
	int isBind = bind(s_fd, (struct sockaddr *) &s_addr, sizeof(s_addr));

	listen(s_fd, 10);
}

int socket_read() {

	unsigned int clen = sizeof(struct sockaddr_in);

	printf("wait for new connection: \n");
	c_fd = accept(s_fd, (struct sockaddr *)&c_addr, &clen);
	if(c_fd == -1)
		handle_error("accept");
	printf("Accept connection: %s\n", inet_ntoa(c_addr.sin_addr));

	memset(socketCtl.cmd, '\0', sizeof(socketCtl.cmd));
	int n_read = read(c_fd, socketCtl.cmd, sizeof(socketCtl.cmd));

	close(c_fd);

	return n_read;
}

int socket_getfd() {
	return s_fd;
}

char* socket_getcmd() {
	return socketCtl.cmd;
}

void socket_Close() {
	close(s_fd);
}

struct Device socketCtl = {
	.name = "socket",
	.ip = "172.20.10.2",
	.port = "8888",
	.init = socket_init,
	.read = socket_read,
	.close = LDV7_Close,
	.next = NULL
};

