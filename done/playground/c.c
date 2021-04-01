#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int MAX_EGGS = 5;
int eggs;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void produceEggs() {
	for(int i=0; i < MAX_EGGS; i++) {
		pthread_mutex_lock(&mutex);
		eggs++;	
		printf("produce egg: %d\n", eggs);
		pthread_mutex_unlock(&mutex);
		pthread_cond_broadcast(&cond);
		sleep(1);
	}
}

void buyEgg() {
	pthread_mutex_lock(&mutex);
	while(eggs < 2) {
		printf("no enough eggs\n");
		pthread_cond_wait(&cond, &mutex);
	}

	eggs -= 2;	

	pthread_mutex_unlock(&mutex);
	printf("got egg, left: %d\n", eggs);
}

int main() {

	int THREAD_SIZE = 3;
	pthread_t t[THREAD_SIZE];

	for(int i=0; i<THREAD_SIZE; i++) {
		if(i==1)
			pthread_create(t+i, NULL, (void*)produceEggs, NULL);
		else
			pthread_create(t+i, NULL, (void*)buyEgg, NULL);
	}

	for(int j=0; j<THREAD_SIZE; j++)
		pthread_join(t[j], NULL);

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);

	return 0;
}
