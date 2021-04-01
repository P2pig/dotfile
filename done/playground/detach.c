#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

void f() {
	sleep(3);
	printf("hello linux\n");
}

int main(){

	pthread_t thread;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);	

	pthread_create(&thread, &attr, (void*)f, NULL);

	pthread_detach(thread);

	pthread_exit(0);
	//return 0;
}
