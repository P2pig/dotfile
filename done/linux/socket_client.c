#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while(0);

int main(int argc, char **argv)
{

	// 1. init socket
	// int socket(int domiain, int type, int protocol);
	int c_fd;
	c_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(c_fd == -1)
		handle_error("socket");

	// 2. blind socket
	// int bind(int sockfd, const struct sockaddr &addr, socklen_t addrlen)
	struct sockaddr_in c_addr;
	c_addr.sin_family = AF_INET;
	c_addr.sin_port = htons(atoi(argv[1]));
	inet_aton("127.0.0.1", &c_addr.sin_addr);

	int isCon = connect(c_fd, (struct sockaddr *) &c_addr, sizeof(struct sockaddr));
	if(isCon == -1) {
		handle_error("connect");
		exit(-1);
	}

	char *readBuf = (char *)malloc(128);
	char *msg = (char *) malloc(128);
	int n_read;

	if(fork() == 0)
	{
		// 5. read
		while(1)
		{
			memset(readBuf, '\0', 128);
			read(c_fd, readBuf, 128);
			if(n_read == -1) {
				handle_error("read");
			} else {
				printf("ReadBuf: %s\n", readBuf);
			}
		}
	}
	else
	{
		while(1)
		{
			memset(msg, '\0', 128);
			scanf("%s",msg);
			write(c_fd, msg, strlen(msg));
		}
	}
	printf("Connection complete.\n");

	close(c_fd);
	return 0;
}
