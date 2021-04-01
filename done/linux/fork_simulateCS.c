#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv)
{

	int input;

	while(1)
	{
		scanf("%d", &input);
		if(input == 1)
		{
			
			if(fork() == 0)
			{
				printf("son pid: %d", getpid());
				while(1)
				{
					printf("Sevice custom, pid: %d\n", getpid());
					sleep(3);
				}
			} else {
				printf("wait for new connection, pid: %d\n", getpid());
			}
		}
	}
	return 0;
}
