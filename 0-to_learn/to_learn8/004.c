#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	int fd[2];
	int pid1,pid2;
	if(pipe(fd) < 0)
		return -1;
	pid1 = fork();
	if(pid1 == 0)
	{
		char str[8];
		printf("Parent \n");
		read(fd[0], str,7);
		printf("-> %s",str);
		exit(0);
	}
	pid2 = fork();
	if(pid2 == 0)
	{
		printf("Child \n");
		write(fd[1], "hello\n",7);
		exit(0);
	}
	int status;
	waitpid(pid1,&status, 0);
	waitpid(pid2,&status, 0);
	exit(EXIT_SUCCESS);
}