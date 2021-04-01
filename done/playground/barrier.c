#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int NUM_THREADS = 10;
int status[10] = {0};
int statusVal[10] = {0};
pthread_barrier_t barrierRollDice;
pthread_barrier_t barrierCalculated;

void* rolldices(void *arg) {
	int index = *(int*)arg;

	while(1) {
		// roll dices
		for(int i=0; i<NUM_THREADS; i++) {
			statusVal[i] = rand() %6 + 1;
		}

		pthread_barrier_wait(&barrierRollDice);
		pthread_barrier_wait(&barrierCalculated); // guaranteed status are calculated

		if(status[index] == 1)
			printf("%d rolled %d, won\n", index, statusVal[index]);
		else
			printf("%d rolled %d, lost\n", index, statusVal[index]);
	}
}

int main() {
	srand(time(NULL));

	pthread_t threads[NUM_THREADS];

	pthread_barrier_init(&barrierRollDice, NULL, NUM_THREADS+1);
	pthread_barrier_init(&barrierCalculated, NULL, NUM_THREADS+1);

		// create threads
		for(int i=0; i < NUM_THREADS; i++) {
			int *index = malloc(sizeof(int));
			*index = i;
			pthread_create(&threads[i], NULL, rolldices, index);
		}


	while(1) {

		pthread_barrier_wait(&barrierRollDice); // guaranteed dice rolled are calculated
		printf("\nNEW ROUND:\n");

		// calculate
		int max;
		for(int i=0; i<NUM_THREADS; i++) { 
			if(statusVal[i] > max)
				max = statusVal[i];
		}
		for(int i=0; i<NUM_THREADS; i++) {
			if(statusVal[i] == max)
				status[i] = 1;
			else
				status[i] = 0;
		}

		sleep(3);
		pthread_barrier_wait(&barrierCalculated); // guaranteed status are calculated

	}

	// clean up
	for(int i=0; i < NUM_THREADS; i++) {
		pthread_join(threads[i], NULL);
	}

	pthread_barrier_destroy(&barrierRollDice);
	pthread_barrier_destroy(&barrierCalculated);

	return 0;
}
