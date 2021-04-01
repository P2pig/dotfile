#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
	system("clear");

	if(argc == 1)
	{
		system("gcc test.c -o test");
		system("./test");
		return 0;
	}

	int isCompile = system("gcc test.c -o test -pthread");
	if(isCompile == 0)
	{
		perror("Compile State ");

		char cmd[128];
		sprintf(cmd, "./test 172.20.10.2 %s", argv[1]);
		system(cmd);
	}
	return 0;
}

