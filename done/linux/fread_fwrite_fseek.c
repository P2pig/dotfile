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
	
	char *data = "hello Linux"; 
	fwrite(data, sizeof(char)*strlen(data), 1, fp);

	fseek(fp, 0, SEEK_SET);
	char buffer[128] = {0};
	fread(buffer, sizeof(char) * strlen(data), 1, fp);

	printf("%s\n", buffer);

	fclose(fp);	
	
	return 0;
}
