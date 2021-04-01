#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char **argv)
{
	if(argc != 3) {
		printf("Arguments Error\n");
		exit(-1);
	}

	int src;
	src = open(argv[1], O_RDWR);
	if(src == -1) {
		printf("Source is not exist.\n");
		exit(-1);
	}

	int dest;
	dest = open(argv[2], O_RDWR|O_CREAT|O_TRUNC, 0600);
	if(dest == -1)	{
		printf("Dest: %d\n", dest);
		exit(-1);
	}
	int size = lseek(src, 0, SEEK_END);
	lseek(src, 0, SEEK_SET);

	char *buffer = (char *) malloc(size);
	int readRet = read(src, buffer, size);
	if(readRet == -1) {
		printf("READ FAIL\n");
		exit(-1);
	}
	int writeRet = write(dest, buffer, size);
	if(writeRet == -1){
		printf("WRITE FAIL\n");
		exit(-1);
	}
	close(src);
	close(dest);

	return 0;
}
