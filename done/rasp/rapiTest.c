#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	int fd;

	fd = open("/dev/pin27", O_RDWR);

	int input;
	printf("0/1: \n ");
	scanf("%d", &input);

	if(input == 0)
	{
		printf("Input == 0 \n");		
		fd = write(fd, &input, 1);
	}else if(input == 1){
		printf("Input == 1 \n");		
		fd = write(fd, &input, 1);
	} else {
		printf("I DONT KNOW\n");
	}

	return 0;
}
