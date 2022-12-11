#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int fd[2];
	fd[0] = open(argv[1], O_RDWR | O_CREAT, 0777);
	fd[1] = open(argv[4], O_RDWR | O_CREAT,0777);
	if(fd[0] == -1)
	{
		printf("error creating files \"%s\"\n", argv[1]);
		return 0;
	}
	if(fd[1] == -1)
	{
		printf("error creating files \"%s\"\n", argv[4]);
		return 0;
	}

	if(pipe(fd) < 0)
		return 0;
	int pid1 = fork();
	if(pid1 < 0)
		return 2;
	if (pid1 == 0)
	{
		//Child process 1
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		write(fd[1], "hi",2);
		close(fd[1]);
		//execlp("ls","ls",NULL,NULL);
	}
	int pid2 = fork();
	if(pid2 < 0)
		return 0;
	if(pid2 == 0)
	{
		//child process 2
		wait(NULL);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		char str[20];
		read(fd[0],str,2);
		printf("-> %s\n",str);
		close(fd[1]);
		//execlp("wc","wc","-l",NULL);
	}
	
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	
	return 0;
}