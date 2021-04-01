#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#include <poll.h>

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
	int isBind;
	struct sockaddr_in s_addr;
	struct sockaddr_in c_addr;

	if(argc != 2)
		handle_error("parameter invalid");

	// set up server socket
	if((s_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		handle_error("socket");

	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(atoi(argv[1]));
	s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if((isBind = bind(s_fd, (struct sockaddr *) &s_addr, sizeof(s_addr))) == -1)
		handle_error("bind");

	listen(s_fd, 10);
	int yes = 1;
	// get rid of "address already in use" error message
	setsockopt(s_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)); 

	// setup for server accept
	unsigned int clen = sizeof(struct sockaddr_in);
	char *readBuf = (char *)malloc(128);
	char *msg = (char *) malloc(128);
	int n_read;


	// set up poll
	int POLL_SIZE = 5;
	int poll_count;
	struct pollfd pfd[POLL_SIZE];
	bzero( pfd, sizeof(pfd));
	pfd[0].fd = s_fd;
	pfd[0].events = POLL_IN;

	poll_count = 1; // for server_fd

	while(1)
	{
		int nfds;
		if((nfds = poll(pfd, poll_count, -1)) == -1)
			handle_error("poll");

		for(int i=0; i < poll_count; i++)
		{
			if(pfd[i].revents & POLL_IN)
			{
				if(pfd[i].fd == s_fd)
				{
					if((c_fd = accept(s_fd, (struct sockaddr *)&c_addr, &clen)) == -1)
						handle_error("accept");

					// add to poll
					pfd[poll_count].fd = c_fd;
					pfd[poll_count].events = POLL_IN;
					poll_count++;

					printf("Accept connection: %s\n", inet_ntoa(c_addr.sin_addr));

					if(poll_count == POLL_SIZE) handle_error("pollcount full");	// Todo

				} else {
					// listen client
					if((n_read = recv(pfd[i].fd, readBuf, sizeof(readBuf), 0)) <= 0) 
					{
						if(n_read == -1) handle_error("read");
						if(n_read == 0) printf("socket hang up");
						// remove from poll
						close(c_fd);
						pfd[i] = pfd[poll_count-1];
						poll_count--;
					} 

					printf("recieve: %s\n", readBuf);

				}
			}
		}
	}

	close(s_fd);
	close(c_fd);
	return 0;
}
