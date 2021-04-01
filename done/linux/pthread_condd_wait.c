#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int gNumber = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *func1(void *param)
{

	pthread_cond_wait(&cond, &mutex);
	//pthread_mutex_lock(&mutex);
	printf("\tfun1 - GNumber: %d\n",gNumber);
	pthread_mutex_unlock(&mutex);
}

void *func2(void *param)
{
	while(1)
	{
		pthread_mutex_lock(&mutex);
		if(gNumber == 3)
		{
			pthread_cond_signal(&cond);
		}else{
			printf("fun2 - GNumber: %d \n", gNumber);
		}	
		pthread_mutex_unlock(&mutex);
		usleep(50000);
		
		if(gNumber == 16)
			break;

		gNumber++;
	}
}

int main()
{
	pthread_t t1;
	pthread_t t2;

	//pthread_mutex_init(&mutex, NULL);
	//pthread_cond_init(&cond, NULL);

	pthread_create((pthread_t *)&t1, NULL, func1, NULL);
	pthread_create((pthread_t *)&t2, NULL, func2, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	return 0;
}

