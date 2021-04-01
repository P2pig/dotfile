       #include <stdio.h>



int main()
{

	FILE *fd = popen("ls", "r");

	char tmp[1024] = {'\0'};

	fread(tmp, sizeof(tmp), 1, fd);
	printf("%s\n", tmp);



	return 0;
}
