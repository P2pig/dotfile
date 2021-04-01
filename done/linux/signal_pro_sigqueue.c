#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv)
{ 
	int signum = atoi(argv[1]);
	pid_t pid  = atoi(argv[2]);

	union sigval value;
	value.sival_int = 100;
		
	sigqueue(pid, signum, value);
	
	printf("Pid: %d Finish.\n", getpid());

	sleep(10);
	return 0;
}

