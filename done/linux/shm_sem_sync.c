#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

//int semget(key_t key, int nsems, int semflg);
//int semctl(int semid, int semnum, int cmd, ...);
// int semop(int semid, struct sembuf *sops, size_t nsops);

void pGetKey(int id)
{
	struct sembuf set;

	set.sem_num = 0;  	// which set of semaphores
	set.sem_op = -1;  	// take away 1 key
	set.sem_flg = SEM_UNDO;	// auto undone when the precess terminate

	semop(id, &set, 1);
	printf("get_key; \t");
}

void vPutBackKey(int id)
{
	struct sembuf set;

	set.sem_num = 0;	// which set of semaphores
	set.sem_op = 1;		// return 1 key
	set.sem_flg = SEM_UNDO;

	semop(id, &set, 1);
	printf("return_back; \n");
}


union semun {
	int              val;    /* Value for SETVAL */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_$ */
	unsigned short  *array;  /* Array for GETALL, SETALL $*/
	struct seminfo  *__buf;  /* Buffer for IPC_INFO
				    (Linux-specific) */
};

int main()
{
	// ----------init semaphore--------------
	key_t key = ftok(".",'z'); // use inode and a char for gen a key
	int semid = semget(key, 1, IPC_CREAT|0777); // grain a 1 set of semaphore
	if(semid != -1) printf("semget seccess\n");

	union semun initsem;
	initsem.val = 1;

	semctl(semid, 0, SETVAL, initsem); 
	perror("semctl");

	// ----------init share memory----------
	// create share memory
	int shmId;

	// delete a shared memory 
	shmctl(shmget(key, 0, 0), IPC_RMID, 0);
	// renew a sham
	shmId = shmget(key, 1024 * 4, IPC_CREAT|0666);

	pid_t pid = fork();
	if(pid > 0)
	{
		while(1)
		{
			// sem - get key(resource)
			pGetKey(semid);

			key_t key = ftok(".", 'z');
			int shmId = shmget(key,0,0);

			// obtain share memory segment
			char *shmAddr;
			shmAddr = shmat(shmId, NULL, 0);

			// write data
			strcat(shmAddr, "A");

			// show data
			printf("father: %s\t",shmAddr); 

			// close memory segment
			shmdt(shmAddr);

			usleep(100000); // 100ms
			// sem - put key back
			vPutBackKey(semid);
		}
	}
	else if(pid == 0) // child
	{
		while(1)
		{
			// sem - get key(resource)
			pGetKey(semid);

			key_t key = ftok(".", 'z');
			int shmId = shmget(key,0,0);

			// obtain memory segment
			char *shmAddr;
			shmAddr = shmat(shmId, NULL, 0);

			// write data
			strcat(shmAddr, "B");
			
			// show data
			printf("child:  %s\t", shmAddr); 

			// close memory segment
			shmdt(shmAddr);

			// sem - put key back
			vPutBackKey(semid);

			usleep(100000); // 100ms
		}
	}

	perror("ERROR");
	exit(-1);

	return 0;
}



