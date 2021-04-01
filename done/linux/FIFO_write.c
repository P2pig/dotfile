#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
	if( (mkfifo("./file", 0600) == -1) && errno != EEXIST)
	{
		printf("mkFIFO Failure\n");
		perror("Why");
	}

	int fd = open("./file", O_RDWR);
	char *msg = "Message from superman :D \n";
	while(1)
	{
		write(fd, msg, strlen(msg));
			
		sleep(3);
	}

	close(fd);
	return 0;
}
