#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *func1(void *param)
{
	printf("Number: %d\n", *((int *)param));

/*	// pase int
	static int ret = 666;
	pthread_exit((void*)&ret);
*/
	static char *ret = "hello linux";
	pthread_exit((void *) ret);

}

int main()
{
	pthread_t t1;
		
	int param = 100;


	pthread_create((pthread_t *)&t1, NULL, func1, &param);

/*	//recieve int
	int *ret;
	pthread_join(t1, (void **) &ret);
	printf("%d\n", ret);
*/

	// recieve char*
	char *ret;
	pthread_join(t1, (void **) &ret);
	printf("%s\n", ret);

	return 0;
}

