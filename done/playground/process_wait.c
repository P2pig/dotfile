#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void print_status(int status);

int main() {

	int status;
	pid_t pid;

	// child process with "normal" exit
	if((pid = fork()) == 0) { exit(7); }
	wait(&status);	
	print_status(status);

	// child process with "abort" exit: /* generated SIGABRT */
	if((pid = fork()) == 0) { abort(); }
	wait(&status);	
	print_status(status);

	// child process with SIGFPE
	if((pid = fork()) == 0) { status /= 0; }
	wait(&status);	
	print_status(status);

	return 0;
}

void print_status(int status)
{
	if(WIFEXITED(status))
		printf("normal termination, exit status: %d\n", WEXITSTATUS(status));

	if(WIFSIGNALED(status))
		printf("abnormal termination, signal number: %d%s\n", WTERMSIG(status),

#ifdef WCOREDUMP
		WCOREDUMP(status) ? " (core file generated)" : "");
#else
		"");
#endif

	else if(WIFSTOPPED(status))
		printf("child stopped, singal number = %d\n", WSTOPSIG(status));
}
