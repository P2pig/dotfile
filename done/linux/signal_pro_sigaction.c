#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void handler(int sig, siginfo_t *info, void *ucontext)
{
	if(ucontext != NULL)
	{
		printf("PID from: %d\n", info->si_pid);
		printf("Signum: %d\n", sig);

		printf("Data: %d\n", info->si_int);
		printf("Data: %d\n", info->si_value.sival_int);
		perror("WHY");
	}
}

int main()
{
	printf("pid %d\n", getpid());

	struct sigaction act;
	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;

	sigaction(SIGUSR1, &act, NULL);

	while(1);
	return 0;
}

