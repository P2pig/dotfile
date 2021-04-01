#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int MAX_MOM = 6;
int t_shirt_per_day = 6; 
int t_shirt;
int isWorking;

void* shopping(void *param) {
	pthread_mutex_lock(&mutex);

	while(t_shirt < 1 && isWorking) {
		printf("\t\t\t\tNo.%d is waiting...\n", *(int*)param);
		pthread_cond_wait(&cond, &mutex);
	}

	if(t_shirt > 0) {
		t_shirt--;
		printf("\t\t\t\tNo.%d bought one, %d left\n", *(int*)param, t_shirt);
		usleep(100000);
	} else {
		printf("\t\t\t\tNo. %d missed.\n", *(int*)param);
	}

	pthread_mutex_unlock(&mutex);
}

void makeT_shirt() {
	isWorking = 1;

	for(int i=0; i < t_shirt_per_day; i++) {
		pthread_mutex_lock(&mutex);
		t_shirt += 2;
		printf("Made %d new T-shirt. total: %d\n", i, t_shirt);
		if(i == t_shirt_per_day-1)
			isWorking = 0;
		pthread_mutex_unlock(&mutex);
		pthread_cond_signal(&cond);
		//pthread_cond_broadcast(&cond);
		usleep(300000);
	}
	printf("worker: job off\n");
}

int main()
{
	pthread_t worker;
	pthread_t moms[MAX_MOM];

	pthread_create(&worker, NULL, (void*) makeT_shirt, NULL);

	for(int i=0; i<MAX_MOM; i++) {
		int *pi = malloc(sizeof(int));
		*pi = i;
		pthread_create(&moms[i], NULL, &shopping, pi);
	}

	for(int i=0; i<MAX_MOM; i++) {
		pthread_join(moms[i], NULL);
	}

	pthread_join(worker,NULL);

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);

	return 0;
}

