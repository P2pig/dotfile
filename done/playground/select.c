#include <sys/select.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/socket.h>
#include <strings.h>
#include <stdio.h>

#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int ret;
	char buf;
	fd_set readfd;

	int keyboard = open("/dev/tty", O_RDONLY|O_NONBLOCK);

	struct timeval tv = { .tv_sec=3, .tv_usec=500000 }; // 3.5s

	while(1)
	{

		FD_ZERO(&readfd);
		FD_SET(keyboard, &readfd);

		ret = select(keyboard+1, &readfd, NULL, NULL, &tv);

		bzero(&buf, 1);
		if(FD_ISSET(keyboard, &readfd))
		{
			read(keyboard, &buf, 1); 
			if(buf == '\n')
				continue;

			fprintf(stdout, "key: %c\n", buf);
		}

		if(ret==0)
			fprintf(stdout, "...\n");
	}

	return 0;
}
