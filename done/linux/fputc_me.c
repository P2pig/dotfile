#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char **argv)
{
	FILE *fp = fopen("./1", "w+");

	char *str = "Linux is cool";

	int len = strlen(str);

	int i;
	for(i = 0; i < len; i++)
	{
		fputc(*str, fp);
		str++;
	}

	fclose(fp);

	return 0;
}
