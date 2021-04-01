#include <unistd.h>
#include <stdlib.h>


int main() {


	if(!fork())
	{
		exit(-1);
	}

	while(1)
		pause();
	return 0;
}
