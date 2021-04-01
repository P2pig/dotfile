#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int primes[10] = {2,3,5,7,11,13,17,19,23,29};

void calc(void* args) {

	int index = *(int*)args;
	int *total = malloc(sizeof(int));

	for(int i=0; i<5; i++) {
		*total += primes[index+i];	
	}

	pthread_exit((void*) total);
}

int main() {

	pthread_t threads[2];

	for(int i=0; i<2; i++) {
		int *index = malloc(sizeof(int));
		*index = i * 5;
		pthread_create(&threads[i], NULL, (void*) calc, index);
	}

	int total = 0;
	for(int i=0; i<2; i++) {
		int *ret;
		pthread_join(threads[i], (void**) &ret);
		total += *ret;
	}

	printf("total: %d\n", total);

	return 0;
}
