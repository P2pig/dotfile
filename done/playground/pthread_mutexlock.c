#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int total;
pthread_mutex_t mutex;

void addOne() {
	pthread_mutex_lock(&mutex);
	total++;
	pthread_mutex_unlock(&mutex);
}

void printMsg(char *name)
{
	int i = 10;
	printf("%s: ", name);
	while(i--)
	{
		printf("%d ", i);	
		fflush(NULL);
		usleep(100000);
	}
	puts("\n");
}

void func1(void *param)
{
	//printMsg("func1");
	int i = 10000000;
	while(i)
	{
		addOne();
		i--;
	}
}

void func2(void *param)
{
	//printMsg("func2");
	int i = 10000000;
	while(i)
	{
		addOne();
		i--;
	}
}

int main()
{
	if(_POSIX_THREADS) 
		perror("support posix_thread");

	pthread_mutex_init(&mutex, NULL);
	pthread_t t1;
	pthread_t t2;

	pthread_create((pthread_t *)&t1, NULL, (void *) &func1, NULL);
	pthread_create((pthread_t *)&t2, NULL, (void *) &func2, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	printf("total: %d\n", total);

	pthread_mutex_destroy(&mutex);

	return 0;
}


