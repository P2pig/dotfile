#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char **argv)
{
	struct T
	{
		int a;
		char b;
	};

	struct T data = {100, 'a'};

	FILE *fp = fopen("./1", "w+");
	
	fwrite(&data, sizeof(struct T), 1, fp);

	fseek(fp, 0, SEEK_SET);

	struct T buffer;
	fread(&buffer, sizeof(struct T), 1, fp);

	printf("%d, %c\n", buffer.a, buffer.b);

	fclose(fp);	
	
	return 0;
}
