#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

struct msgbuf {
	long mtype;       /* message type, must be > 0 */
	char mtext[128];    /* message data */
};

int main()
{
	key_t key = ftok(".", 'z');
	printf("%x\n", key);

	int id = msgget(key, IPC_CREAT|777);
	if(id == -1)
	{
		printf("msgget FAILURE\n");
		perror("WHY");
	}
	struct msgbuf msg = {666, "Hello Linux :)"};
	msgsnd(id, &msg, strlen(msg.mtext), 0);

	struct msgbuf buffer;
	msgrcv(id, &buffer, sizeof(buffer.mtext), 777, 0);
	printf("%s\n", buffer.mtext);

	// remove id
	msgctl(id, IPC_RMID, NULL);
	return 0;
}

