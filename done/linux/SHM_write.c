#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	// create share memory
	key_t key = ftok(".", 'z');
	int shmId = shmget(key, 1024 * 4, IPC_CREAT|0666);

	// share memory segment
	char *shmAddr;
	shmAddr = shmat(shmId, NULL, 0);

	// write data
	char *data = "Hello Linux";
	strcpy(shmAddr, data);

	// close memory segment
	shmdt(shmAddr);

	sleep(10);

	// delete share memory
	shmctl(shmId, IPC_RMID, 0);

	return 0;
}
