#include <stdio.h>

int main()
{

	union un{
		int a;
		char b;
	}u;

	u.a = 1;
	
	if(u.b == 1)
		printf("Little");
	
	if(u.b == 0)
		printf("Large");

	return 0;
}
