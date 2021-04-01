#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include "messageType.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while(0);

struct Msg *msgRecv;
struct Msg *msgSend;
int c_fd;
int n_read;

int get_cmd_type(char *cmd)
{
	if(!strcmp(cmd,"lls"))    return LLS;
	if(!strcmp(cmd,"lpwd"))   return LPWD;
	if(strstr(cmd,"lcd"))	  return LCD;
	if(strstr(cmd,"put"))	  return PUT;
	if(!strcmp(cmd, "quit"))  return QUIT;
	return NotFound;
}

char *getDesDir(char *msg)
{ 
	char *p; 
	p = strtok(msg, " "); 
	p = strtok(NULL, " "); 
	return p; 
} 

void receiveHandler()
{
	while(1)
	{
		memset(msgRecv, '\0', sizeof(struct Msg));
		n_read = read(c_fd, msgRecv, sizeof(struct Msg));

		if(n_read == -1) {
			handle_error("read");
		} else if(n_read == 0) {
			handle_error("server disconnected");	
			close(c_fd);
		} else {
			if(msgRecv->type == LS)
			{
				printf("-------------------------\n");
				printf("%s", msgRecv->cmd);
				printf("-------------------------\n");
			} else if(msgRecv->type == GET) {
				char *file = msgRecv->cmd;
				int fd = open(file, O_RDWR|O_CREAT|O_TRUNC, 00666);
				if(fd == -1)
					handle_error("Open");
				int n_write = write(fd, &msgRecv->buffer, sizeof(msgRecv->buffer));
				if(n_write == 0)
					handle_error("Write");		
			} else {
				printf("%s", msgRecv->cmd);
			}

		}
		fflush(stdout);
	}

}

void sendHandler()
{
	while(1)
	{
		memset(msgSend, '\0', sizeof(struct Msg));
		printf("> ");
		scanf("%[^\n]%*c", msgSend->cmd); // bug: non-stop print with empty input :(
		//gets(msgSend->cmd);

		char *dir;
		int type = get_cmd_type(msgSend->cmd);
		
		switch(type)
		{
			case LLS:
				system("ls");
				break;

			case LCD:
				dir = getDesDir(msgSend->cmd);
				chdir(dir);
				break;

			case LPWD:
				system("pwd");
				break;

			case PUT:;
				char *cmd = (char *)malloc(strlen(msgSend->cmd));
				strcpy(cmd, msgSend->cmd); // save a cmd copy before get into strtok

				dir = getDesDir(msgSend->cmd);
				if(access(dir, F_OK) == 0)
				{
					int fd = open(dir, O_RDWR);
					int n_read = read(fd, msgSend->buffer, sizeof(msgSend->buffer));
					if(n_read != -1) {
						strcpy(msgSend->cmd,cmd);
						write(c_fd, msgSend, sizeof(struct Msg));
						close(fd);
					} else {
						handle_error("PUT: READ: ");
					}

				} else {
					printf("File is not exist\n");
				}
				break;
			case QUIT:
				write(c_fd, "quit", 4);
				close(c_fd);
				exit(0);
				break;
			default:
				write(c_fd, msgSend, sizeof(struct Msg));
				break;

		}
		usleep(100000); // wait 100ms for msg to arrive and then back to loop to print ">"
	}
}

int main(int argc, char **argv)
{
	// initialize socket
	c_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(c_fd == -1)
		handle_error("socket");

	// bind socket
	struct sockaddr_in c_addr;
	c_addr.sin_family = AF_INET;
	c_addr.sin_port = htons(atoi(argv[2]));
	inet_aton(argv[1], &c_addr.sin_addr);

	int isConnected = connect(c_fd, (struct sockaddr *) &c_addr, sizeof(struct sockaddr));
	if(isConnected == -1) {
		handle_error("connect");
	}
	printf("Connected to server...\n");

	msgRecv = (struct Msg *) malloc(sizeof(struct Msg));
	msgSend = (struct Msg *) malloc(sizeof(struct Msg));

	if(fork() == 0)
		receiveHandler();

	sendHandler();

	return 0;
}
