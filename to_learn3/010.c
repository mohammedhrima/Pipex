#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(void)
{
	int fd[2];
	int in = open("in", O_RDONLY | O_CREAT, 0777);
	int out = open("out", O_WRONLY | O_TRUNC | O_CREAT, 0777);

	if (pipe(fd) < 0)
		return -1;

	int pid1 = fork();
	if (pid1 < 0)
		return -2;
	if (pid1 == 0)
	{
		dup2(in, STDIN_FILENO);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		char *arr[] = {"ls", "-l", NULL, NULL};
		execve("/bin/ls", arr, NULL);
		close(fd[1]);
	}
	if (pid1 > 0)
	{
		wait(NULL);
		// close(fd[0]);
		close(fd[1]);
	}

	int pid2 = fork();
	if (pid2 < 0)
		return -3;
	if (pid2 == 0)
	{
		
		dup2(out, STDOUT_FILENO);
		dup2(fd[0], STDIN_FILENO);
		char *arr[] = {"wc", "-l", NULL, NULL};
		execve("/usr/bin/wc", arr, NULL);
		close(fd[0]);
	}
	if (pid2 > 0)
	{
		wait(NULL);
		close(fd[0]);
	}
}