#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void handler(int signum)
{
	printf("signum: %d\n", signum);
}

int main(int argc, char **argv)
{
	printf("pid: %d\n", getpid());
	
	//signal(SIGINT, SIG_IGN); // ignore, ctl+c signal
	signal(SIGINT, handler);

	/*
	// use system to send cmd to kill pid
	int signum = atoi(argv[1]);
	int pid = atoi(argv[2]);

	char cmd[128] = {0};
	sprintf(cmd, "kill -%d %d", signum, pid);

	system(cmd);
	*/

	while(1);
	return 0;
}
