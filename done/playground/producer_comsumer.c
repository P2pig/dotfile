#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int THREAD_TOTAL = 2;
int storage[10];
int count = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void producer(void *args) {
	while(1) {
		pthread_mutex_lock(&mutex);
		if(count < 10) {
		storage[count] = rand() % 100;
		printf("count: %d, val: %d\n", count, storage[count]);
		count++;
		} else {
			printf("produce skipped\n");
		}
		pthread_mutex_unlock(&mutex);
	}
}

void comsumer(void *args) {
	int val;

	while(1) {	
		pthread_mutex_lock(&mutex);
		if(count > 0) {
			val = storage[count-1];
			count--;
		} else {
			printf("\t\t\t\t\tcomsum failed\n");
		}
		printf("\t\t\t\t\tcount: %d, got val: %d\n", count, val);
		pthread_mutex_unlock(&mutex);
	}
}

int main() {

	srand(time(NULL));

	pthread_t thread[THREAD_TOTAL];

	for(int i = 0; i < THREAD_TOTAL; i++) {
		if(i % 2 == 0)
			pthread_create(&thread[i], NULL, (void*) producer, NULL);
		else
			pthread_create(&thread[i], NULL, (void*) comsumer, NULL);
	}

	for(int i = 0; i < THREAD_TOTAL; i++) {
		pthread_join(thread[i], NULL);
	}

	pthread_mutex_destroy(&mutex);

	return 0;
}
