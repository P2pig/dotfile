#include <pthread.h>
#include <stdio.h>

void *start(void *val)
{
	printf("%d\n", *(int *)val);
	
	static int ret = 11;
	pthread_exit((void*) &ret);
}

int main() {

	pthread_t thread;
	int val = 10;

	pthread_create(&thread, NULL, start, &val);

	int *retval;

	pthread_join(thread, (void**)&retval);
 
	printf("%d\n", *retval);

	return 0;
}
