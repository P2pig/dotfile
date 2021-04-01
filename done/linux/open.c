#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	// OPEN
	// int open(const char *pathname, int flags);
	// int open(const char *pathname, int flags, mode_t mode);
	// flag: O_RDONLY, O_WRONLY, O_RDWR
	// 	 O_CREAT, O_EXCL, O_APPEND, O_TRUNC
	int fd;

	fd = open("./file1", O_RDWR|O_TRUNC);
	if(fd == -1)
		printf("Fail to open!\n");

	// Open onCreate if not exist
	// if exist then return -1
	// fd = open("./file1", O_RDWR|O_CREAT|O_EXCL, 0700);
	// if(fd == -1)
	// 	printf("file1 exist\n");

	// WRITE
	// ssize_t write(int fd, const void *buf, size_t count);
	char *buffer = "54321";
	int n_write = write(fd, buffer, strlen(buffer));
	if(n_write != -1)
	{
		printf("Success write\n");
		printf("Write %d bit to ./file1\n", n_write);
	}

	// LSEEK - move cursor
	//        off_t lseek(int fd, off_t offset, int whence);
	// whence: SEEK_SET, SEEK_END, SEEK_CUR (head, tail, current position)

	int size = lseek(fd, 0, SEEK_END);

	printf("lseek: current cur: %d\n", size);

	// READ 
	// ssize_t read(int fd, void *buf, size_t count);

	char *readBuffer = (char *) malloc(sizeof(char) * n_write);
	int readResult = read(fd, readBuffer, n_write);
	printf("Read Result = %d, Read Buffer = %s\n", readResult, readBuffer);

	// 0  STDIN_FILENO -  input from cmd
	// 1 STDOUT_FILENO - output to cmd
	// 2 STDERR_FILENO - (XXXXX)
	printf("TEST STANDARD IN OUT AND ERR");
	char input[128] = "12345";
	//	read(STDIN_FILENO, input, 5);
	write(STDOUT_FILENO, input, 5);

	close(fd);


	// CREAT FILE
	fd = creat("/home/dock/code/file2", 0700);
	if(fd != -1)
		printf("/home/dock/code/file2  file create successful!\n");



	return 0;
}

