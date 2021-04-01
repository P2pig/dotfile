#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while(0);

void handler(int sig, siginfo_t *info, void *context)
{
	while( waitpid(-1, NULL, WNOHANG) > 0);
}

int main(int argc, char **argv)
{
	int s_fd;
	int c_fd;
	struct sockaddr_in s_addr;
	struct sockaddr_in c_addr;

	// 1. init socket
	// int socket(int domiain, int type, int protocol);
	s_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(s_fd == -1)
		handle_error("socket");

	// 2. blind socket
	// int bind(int sockfd, const struct sockaddr &addr, socklen_t addrlen)
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(atoi(argv[1]));
	//s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	inet_aton("127.0.0.1", &s_addr.sin_addr);
	if((bind(s_fd, (struct sockaddr *) &s_addr, sizeof(s_addr))) == -1)
		perror("bind");


	char *readBuf = (char *)malloc(128);
	int n_read;

	if(!fork()) {
		memset(readBuf, '\0', 128);
		unsigned int clen = sizeof(struct sockaddr_in);
		if((n_read = recvfrom(s_fd, readBuf, 128-1, 0, (struct sockaddr *)&c_addr, &clen)) == -1)
			perror("recvfrom");
		readBuf[128] = '\0';
		fprintf(stdout, "packet nByte:%d, ReadBuf: %s\n", n_read, readBuf);
	}

	while(1)
		sleep(5);

	// never actually reach
	close(s_fd);
	close(c_fd);

	return 0;
}
