#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>


int main(void)
{
	int fd[2];

	if (pipe(fd) < 0)
		return 1;

	pid_t pid1 = fork();
	char str[3] ;//= "abcd";
	if(pid1 < 0)
		return 2;
	if (pid1 == 0 )
	{
		close(fd[0]);
		//dup2(fd[1], STDOUT_FILENO);
		write(fd[1],"Hi",3);
	}
	if(pid1 > 0)
	{
		wait(NULL);
		close(fd[1]);
		//dup2(fd[0], STDIN_FILENO);
		read(fd[0],str,3);
		write(1,str,3);
	}
	return 0;
}