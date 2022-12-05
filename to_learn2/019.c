#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	int fd[2];
	if (pipe(fd) == -1)
		return 1;
	int pid1 = fork();
	if (pid1 < 0)
		return 2;
	if (pid1 == 0)
	{
		// Child process 1
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execlp("ls", "ls", "-l", NULL, NULL, NULL);
	}
	int pid2 = fork();
	if (pid2 < 0)
		return 3;
	if (pid2 == 0)
	{
		// child process 2
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		execlp("wc", "wc", "-l", NULL, NULL);
	}
	close(fd[0]); // those two files descriptor remain opened in main process that's why we have to cloase them
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	return 0;
}