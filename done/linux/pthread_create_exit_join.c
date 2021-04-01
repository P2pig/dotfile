#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *func1(void *param)
{
	static char *ret = "hello world";

	printf("Number: %d\n", *((int *)param));

	pthread_exit((void *) &ret);
}

int main()
{
	pthread_t t1;
		
	int param = 100;

	char *ret;

	pthread_create((pthread_t *)&t1, NULL, func1, &param);

	pthread_join(t1, (void **) &ret);

	printf("%s\n", ret);

	return 0;
}

