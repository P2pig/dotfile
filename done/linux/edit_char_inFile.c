#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char **argv)
{
	if(argc != 2){
		printf("Arguments Error\n");
		exit(-1);
	}

	int src;
	src = open(argv[1], O_RDWR);
	if(src == -1) {
		printf("Source is not exist.\n");
		exit(-1);
	}

	int size = lseek(src, 0, SEEK_END);
	if(size == -1)
		printf("lseek on error.\n");
	lseek(src, 0, SEEK_SET);


	char *readBuff = (char *) malloc(size);
	int n_read= read(src, readBuff, size);
	if(n_read == -1) {
		printf("READ FAIL\n");
		exit(-1);
	}

	char* p = strstr(readBuff, "love=");
	if(p == NULL)
		printf("substring not found");

	p = p + strlen("love=");
	*p = '1';

	lseek(src, 0, SEEK_SET);

	int writeRet = write(src, readBuff, strlen(readBuff));
	if(writeRet == -1){
		printf("WRITE FAIL\n");
		exit(-1);
	}
	close(src);

	return 0;
}
