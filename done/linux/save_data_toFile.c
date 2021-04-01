#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

/*
 * save int to a file & read
 * save char *str to file & read;
 * save a struct to a file & read *
 * save struct arry to file & read
 */
int main(int argc, char **argv)
{
	struct T
	{
		int c;
		char s;
	};


	struct T data1[2] = {{100, 'a'},{200, 'b'}};
	struct T data2[2];

	int fd;
	fd = open("1", O_RDWR|O_CREAT,0600);
	write(fd, &data1, sizeof(struct T)*2);

	int size;
	size = lseek(fd,0,SEEK_END);
	lseek(fd, 0, SEEK_SET);
	
	read(fd, &data2, sizeof(struct T)*2);
	printf("%d,%c | %d, %c\n", data2[0].c, data2[0].s, data2[1].c, data2[1].s);
	
	close(fd);

	return 0;
}
