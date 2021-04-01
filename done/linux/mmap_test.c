#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main() {

	int pagesize = getpagesize();
	int fd;
	char *addr;

	printf("page size: %d\n", pagesize);

	if((fd= open("file", O_RDWR|O_CREAT, 0666)) == -1)
		perror("fd");

	//write(fd,"",1);	// mmap can not use file which has 0 size, "Bus error (core dumped)" error otherwise

	if((addr = mmap(NULL, 10, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED)
		perror("mmap");
	close(fd);

	int c ='a';
	for(int i=0; i<10;i++)
	{
		*(addr+i) = '\0';
		memcpy(addr+i, &c, 1);
		//memcpy((*(addr+i)).name, &temp, 1);
		//(*(addr+i)).age=i;

		c++;
	}

	for(int j=0;j<10;j++)
	{
		printf("no:%d\n", *(addr+j));
	}


	if(munmap(addr, pagesize) == -1)
		perror("munmap");

}
