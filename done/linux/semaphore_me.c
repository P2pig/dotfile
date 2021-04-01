#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
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
	printf("get key\n");
}

void vPutBackKey(int id)
{
	struct sembuf set;

	set.sem_num = 0;	// which set of semaphores
	set.sem_op = 1;		// return 1 key
	set.sem_flg = SEM_UNDO;

	semop(id, &set, 1);
	printf("put back the key\n");
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
	key_t key = ftok(".",'z'); // use inode and a char for gen a key
	int semid = semget(key, 1, IPC_CREAT|0777); // grain a 1 set of semaphore
	if(semid != -1) printf("semget seccess\n");

	union semun initsem;
	initsem.val = 1;

	// set initsem to index:0 of semaphore set
	semctl(semid, 0, SETVAL, initsem); 
	perror("semctl");

	while(1)
	{
		pGetKey(semid);
		sleep(10);
		vPutBackKey(semid);
	}

	return 0;
}



