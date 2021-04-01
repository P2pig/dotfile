#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/shm.h>

#define SHM_SIZE 1024	// 1k memory for shm

int main() {

	key_t key = ftok(".", 'a');

	int shmid;
	if((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) == -1)
	{ perror("shmget"); exit(-1); }

	int *addr;
	if((addr = shmat(shmid, 0, 0)) == (void *) -1)
		perror("shmat");

	char buf[32] = {'0'};
	if(read(0, &buf, 32) == -1)
		perror("read");

	printf("input value: %s", buf);

	shmdt(addr);

	shmctl(shmid, IPC_RMID, 0);
}
