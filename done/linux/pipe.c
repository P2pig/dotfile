#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	int pipefd[2]; // fd[0] for read, fd[1] for write
	pid_t cpid;
	char *buf;
	if(pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	cpid = fork();
	if(cpid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	// daddy write to son
	if(cpid == 0)
	{
		printf("son\n");
		close(pipefd[1]); // close write

		buf = (char *) malloc(sizeof(char) * 1024);
		read(pipefd[0], buf, 1024);	// if read empty it would hang until data come
		printf("Son: read from father: %s\n", buf);

		close(pipefd[0]);
		exit(0);
	}
	else
	{
		printf("Father\n");
		sleep(3);
		close(pipefd[0]); // close read

		write(pipefd[1], "Data from daddy", strlen("Data from daddy"));
		close(pipefd[1]);
		wait(NULL);
		exit(EXIT_SUCCESS);

	}

	return 0;
}
