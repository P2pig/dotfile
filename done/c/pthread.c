#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* fun1()
{
	while(1)
	{
		printf("fun1\n");
		sleep(1);
	}
}

void* fun2()
{
	while(1)
	{
		printf("fun2\n");
		sleep(1);
	}
}

int main()
{
	pthread_t t1;
	pthread_t t2;

	t1 = pthread_create(&t1, NULL, fun1, NULL);
	t2 = pthread_create(&t2, NULL, fun2, NULL);

	int i;
	for(i = 0; i < 10; i++)
		printf("this is main loop\n");
	
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);

	return 0;
}
