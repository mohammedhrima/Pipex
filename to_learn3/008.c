
// CPP program to illustrate dup2()
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{
	int fd[2];

	if (pipe(fd) < 0)
		return 1;

	int in = open("in", O_RDWR | O_CREAT);
	int out = open("out", O_RDWR | O_CREAT | O_TRUNC);

	pid_t pid1 = fork();
	char str[3]; //= "abcd";
	if (pid1 < 0)
		return 2;
	if (pid1 == 0)
	{
		// child process
		close(fd[0]);
		dup2(out, STDOUT_FILENO); // replace sdin with in file
		char *arr[] = {"ls", "-l", "-a", NULL};
		execve("/bin/ls", arr, NULL);
	}
	if (pid1 > 0)
	{
		// parent process
		wait(NULL);
		return 0;

		close(fd[1]);
		dup2(out, STDOUT_FILENO); // replace stdout with out file
		read(fd[0], str, 3);
		write(1, str, 3);
	}

	return 0;
}