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

int s_fd;
int c_fd;
struct sockaddr_in s_addr;
struct sockaddr_in c_addr;

int get_cmd_type(char *cmd)
{
	if(!strcmp(cmd,"pwd"))	  return PWD;
	if(!strcmp(cmd,"ls"))	  return LS;
	if(strstr(cmd, "cd"))	  return CD;
	if(strstr(cmd, "get"))	  return GET;
	if(strstr(cmd, "put"))	  return PUT;
	if(!strcmp(cmd, "quit"))  return QUIT;
	return NotFound;
}

char *getDesDir(char *msg)
{
	char *p = msg;
	p = strtok(p, " ");
	p = strtok(NULL, " ");
	return p;
}

void msg_handler(struct Msg *msg)
{

	FILE *file = NULL;
	char *dir;

	printf("[%s]\n", msg->cmd);

	int type = get_cmd_type(msg->cmd);

	switch(type)
	{
		case LS:
			{
				msg->type = LS;
				file = popen("ls", "r");
				fread(msg->cmd, sizeof(msg->cmd), 1,  file);
				write(c_fd, msg, sizeof(struct Msg));
				break;
			}
		case PWD:
			{
				msg->type = PWD;
				file = popen("pwd", "r");
				fread(msg->cmd, sizeof(msg->cmd), 1,  file);
				write(c_fd, msg, sizeof(struct Msg));
				pclose(file);
				break;
			}
		case CD:
			{
				msg->type = CD;
				dir = getDesDir(msg->cmd);
				chdir(dir);
				break;
			}
		case GET:
			{
				dir = getDesDir(msg->cmd);
				if(access(dir, F_OK) == 0)
				{
					msg->type = GET;
					int fd = open(dir, O_RDWR);
					int n_read = read(fd, msg->buffer, sizeof(msg->buffer));
					if(n_read != -1) {
						strcpy(msg->cmd, dir); // name of file for client to reference with
						write(c_fd, msg, sizeof(struct Msg));
					} else {
						handle_error("Get: Read:");
					}

				} else {
					strcpy(msg->cmd, "File is not EXIST");
					write(c_fd, msg, sizeof(struct Msg));
				}

				break;
			}
		case PUT:
			{
				dir = getDesDir(msg->cmd);
				int fd = open(dir, O_RDWR|O_CREAT|O_TRUNC, 00666);
				int n_write = write(fd, msg->buffer, sizeof(msg->buffer));
				if(n_write != -1)
				{
					printf("Put successful");
					fflush(stdout);
				} else {
					handle_error("PUT: WRITE:");
				}
				break;
			}
		case QUIT:
			close(c_fd);
			exit(EXIT_SUCCESS);
			break;
		default:
			{
				printf("cmd NOT FOUND, o_O?\n");
				break;
			}
	}

}

void process()
{
	struct Msg *msg = (struct Msg *) malloc(sizeof(struct Msg));
	int n_read;

	while(1)
	{
		memset(msg, '\0', sizeof(struct Msg));
		n_read = read(c_fd, msg, sizeof(struct Msg));
		if(n_read < 0) {
			handle_error("read");
		} else if(n_read == 0) {
			handle_error("Client disconnected");
		} else if(n_read > 0) {
			msg_handler(msg);
		}
	}
}

int main(int argc, char **argv)
{
	if(argc!=3)
		handle_error("less input arguments");

	// initialize socket
	s_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(s_fd == -1)
		handle_error("socket");

	// bind socket
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(atoi(argv[2]));
	inet_aton(argv[1], &s_addr.sin_addr);
	bind(s_fd, (struct sockaddr *) &s_addr, sizeof(s_addr));

	// listen
	listen(s_fd, 10);

	int clen = sizeof(struct sockaddr_in);
	while(1)
	{
		// accept
		c_fd = accept(s_fd, (struct sockaddr *) &c_addr, &clen);
		if(c_fd == -1)
			handle_error("accept");
		printf("Accept connection: %s\n", inet_ntoa(c_addr.sin_addr));

		if(fork() == 0)
			process(c_fd);
	}

	return 0;
}
