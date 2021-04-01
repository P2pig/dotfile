#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;

void printMsg(char *name)
{
	pthread_mutex_lock(&mutex);
	int i = 10;
	printf("%s: ", name);
	while(i--)
	{
		printf("%d ", i);	
		fflush(NULL);
		usleep(100000);
	}
	puts("\n");
	
	pthread_mutex_unlock(&mutex);
}

void func1(void *param)
{
	printMsg("func1");
}

void func2(void *param)
{
	printMsg("func2");
}

int main()
{
	pthread_t t1;
	pthread_t t2;

	pthread_mutex_init(&mutex, NULL);

	pthread_create((pthread_t *)&t1, NULL, (void *) &func1, NULL);
	pthread_create((pthread_t *)&t2, NULL, (void *) &func2, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	pthread_mutex_destroy(&mutex);

	return 0;
}


