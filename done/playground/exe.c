#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	char* en[] = { "ls", "-l", NULL };
	execv("/bin/ls", en);



	return 0;
}
