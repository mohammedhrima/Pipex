#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(void)
{
	int fd[2];
	int fd2[2];
	fd2[0] = open("in", O_RDWR | O_CREAT, 0777);
	fd2[1] = open("out", O_RDWR | O_CREAT,0777);
	//dup2(fd2[0], STDIN_FILENO);
	//dup2(fd2[1], STDOUT_FILENO);


	if (pipe(fd) == -1)
		return 1;
	int pid1 = fork();
	if (pid1 < 0)
		return 2;
	if (pid1 == 0)
	{
		// Child process 1
		close(fd[0]);
		//dup2(fd[1], fd2[0]);
		dup2(fd[1], STDOUT_FILENO);
		execve("/bin/cat",NULL,NULL);
		close(fd[1]);
 	}
	while(waitpid(pid1, NULL, 0) != -1);

	int pid2 = fork();
	if (pid2 < 0)
		return 3;
	if (pid2 == 0)
	{
		// child process 2
		close(fd[1]);
 		dup2(fd[0],STDIN_FILENO);
		dup2(fd2[1], STDOUT_FILENO);
		execve("/bin/cat", NULL ,NULL);
		close(fd[0]);
	}
	close(fd[0]); // those two files descriptor remain opened in main process that's why we have to cloase them
	close(fd[1]);
	
	waitpid(pid2, NULL, 0);

	return 0;
}