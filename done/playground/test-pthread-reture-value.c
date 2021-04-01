#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void func1(void* args) {

	int ret = *(int*)args;

	ret += 100;

	*(int*)args = ret;
	pthread_exit(args);
}

int main() {

	pthread_t thread;

	int *input = malloc(sizeof(int));

	*input = 100;

	pthread_create(&thread, NULL, (void*) func1, input);

	int *retVal;
	
	pthread_join(thread, (void**) &retVal);

	printf("ret: %d\n", *retVal);

	return 0;
}
