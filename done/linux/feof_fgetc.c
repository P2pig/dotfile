#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	FILE *fp = fopen("./1", "r");

	while(!feof(fp))
		printf("%c",fgetc(fp));

	fclose(fp);

	return 0;
}
