#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int fd[2];
	int pid;
	char buf[40];
	fd[0] = open("in", O_CREAT | O_RDWR, 0777);
	fd[1] = open("out", O_CREAT | O_RDWR, 0777);

	if (pipe(fd) < 0)
	{
		perror("pipe");
		exit(1);
	}
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1],1);
		write(fd[1], "Hello there", 20);
		close(fd[1]);
	}
	else
	{
		wait(NULL);
		close(fd[1]);
		dup2(fd[0],0);
		read(fd[0], buf, 15);
		printf("-> %s\n", buf);
		close(fd[0]);
	}
	close(fd[0]);
	close(fd[1]);

	return 0;
}