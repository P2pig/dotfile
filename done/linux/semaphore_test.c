#include <stdio.h>
#include <sys/sem.h>

union semun {
	int val;
	struct semid_ds *buf;
	unsigned short  *array;
};

int main() {
	key_t key = ftok(".", 'b');
	int nSems = 10;
	int semid;
	
	if((semid = semget(key, nSems, IPC_CREAT | 0660)) == -1)
		perror("semget");

#if 0	// set sem resource to 1
	union semun arg = {.val=1};
	semctl(semid, 0, SETVAL, arg);   
	perror("SETVAL");
#endif


#if 0	// allocated resource
	struct sembuf allocateR = {0, -1, IPC_NOWAIT};

	if((semop(semid, &allocateR, 1)) == -1)
		perror("semop");
#endif

#if 0	// release resource
	struct sembuf releaseR = {0, 1, IPC_NOWAIT};

	if((semop(semid, &releaseR, 1)) == -1)
		perror("semop");
#endif

#if 0	// show resource
	int result = semctl(semid, 0, GETVAL);
	printf("number of resources: %d\n", result);
#endif

#if 1	// retrieve sem_num
	struct semid_ds ds;
	union semun arg = {.buf=&ds};
	if((semctl(semid, 0, IPC_STAT, arg)) == -1)
		perror("STAT\n");
	printf("Number of sem_num: %ld\n", arg.buf->sem_nsems);

#endif

#if 0	// remove semid
	if((semctl(semid, IPC_RMID, 0)) == -1)
		perror("semop");
#endif

}
