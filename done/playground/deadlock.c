#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mutex1, mutex2;

void* func1() {

	pthread_mutex_lock(&mutex1);
	printf("fun1 lock mutex1\n");
	sleep(1);
	pthread_mutex_lock(&mutex2);
	printf("fun2 lock mutex1\n");

	printf("text from func1\n");

	pthread_mutex_unlock(&mutex2);
	pthread_mutex_unlock(&mutex1);

}

void* func2() {
	pthread_mutex_lock(&mutex2);
	printf("fun2 lock mutex2\n");
	sleep(1);
	pthread_mutex_lock(&mutex1);
	printf("fun1 lock mutex1\n");

	printf("text from func2\n");

	pthread_mutex_unlock(&mutex1);
	pthread_mutex_unlock(&mutex2);
}

int main() {

	pthread_mutex_init(&mutex1, NULL);
	pthread_mutex_init(&mutex2, NULL);

	pthread_t t1,t2;
	pthread_create(&t1, NULL, func1, NULL);
	pthread_create(&t1, NULL, func2, NULL);

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);

	pthread_mutex_destroy(&mutex1);
	pthread_mutex_destroy(&mutex2);

	return 0;
}
