#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

typedef struct{
	char name[4];
	int age;
}people;

int main() {

	int pagesize = getpagesize();
	int fd;
	people *addr;

	printf("page size: %d\n", pagesize);

	if((fd= open("file", O_RDWR|O_CREAT, 0666)) == -1)
		perror("fd");

	if((addr = (people*) mmap(NULL, sizeof(people)*10, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED)
		perror("mmap");
	close(fd);

	int temp ='a';
	for(int i=0; i<10;i++)
	{
		temp+=1;
		(*(addr+i)).name[1] = '\0';
		memcpy((*(addr+i)).name, &temp, 1);
		(*(addr+i)).age=i;
	}

	for(int j=0;j<10;j++)
	{
		printf("name:%s, age%d\n", (*(addr+j)).name, (*(addr+j)).age);
	}
	
	


	if(munmap(addr, pagesize) == -1)
		perror("munmap");

}

#if 0	//read

	int pagesize = getpagesize();
	int fd = open("file", O_CREAT | O_RDWR);
	int *addr = mmap((caddr_t) 0, pagesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(addr == (int*) -1)
		perror("mmap");

	char *txt = malloc(pagesize);
	memset(txt, '\0', pagesize);

	memcpy(txt, addr, strlen(txt));

	if(munmap(addr, pagesize) == -1)
		perror("munmap"); 
	close(fd);

#endif	

