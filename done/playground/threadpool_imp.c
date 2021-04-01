#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

typedef struct Task {
	void (*ptr)();
	int a,b;
}Task;

pthread_mutex_t mutexQueue = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condQueue = PTHREAD_COND_INITIALIZER;

int MAX_THREADS = 1;
int taskcount = 0;
Task taskqueue[256];

void sum(int a, int b) {
	int total = a + b; 
	printf("sum of %d and %d is %d\n", a, b, total);
}

void mult(int a, int b) {
	int total = a * b;
	printf("multi of %d and %d is %d\n", a, b, total);

}

void executeTask(Task *task) {
	task->ptr(task->a, task->b);
//	int sum = task->a + task->b;
//	printf("result: %d\n", sum);
}

void submitTask(Task task) {
	pthread_mutex_lock(&mutexQueue);
	taskqueue[taskcount] = task;
	taskcount++;
	pthread_mutex_unlock(&mutexQueue);
	pthread_cond_signal(&condQueue);
}

void startThread() {

	while(1) {
		pthread_mutex_lock(&mutexQueue);
		while(taskcount < 0)
			pthread_cond_wait(&condQueue, &mutexQueue);

		Task task = taskqueue[0];
		taskcount--;
		for(int i=0; i<taskcount; i++) {
			taskqueue[i] = taskqueue[i+1];
		}
		pthread_mutex_unlock(&mutexQueue);

		executeTask(&task);
	}

}

int main() {

	pthread_t threadpool[MAX_THREADS];
	int i;
	for(i=0; i<MAX_THREADS; i++) {
		pthread_create(&threadpool[i], NULL, (void*)startThread, NULL);	
	}

	srand(time(NULL));
	for(i=0; i<100; i++) {
		Task task = {
			task.ptr = (i%2==0)? sum:mult,
			.a = rand() % 100, 
			.b = rand() % 100
		};
		submitTask(task);
	}

	for(i=0; i<MAX_THREADS; i++) {
		pthread_join(threadpool[i], NULL);
	}

	pthread_mutex_destroy(&mutexQueue);
	pthread_cond_destroy(&condQueue);

	return 0;
}
