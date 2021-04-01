#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main()
{

	// create share memory
	key_t key = ftok(".", 'z');
	int shmId = shmget(key, 1024 * 4, 0);
	if(shmId == -1)
		perror("why");

	// share memory segment
	char *shmAddr;
	shmAddr = shmat(shmId, 0, 0);

	// show data
	printf("Data: %s\n", shmAddr);

	// close memory segment
	shmdt(shmAddr);

	return 0;
}

