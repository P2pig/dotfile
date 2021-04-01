#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{

	int fd = open("./file", O_RDONLY);

	char *buf = (char *)malloc(sizeof(char) * 124);

	while(1)
	{
		read(fd, buf, 124);

		printf("Read: %s", buf);
	}
	close(fd);
	return 0;
}
