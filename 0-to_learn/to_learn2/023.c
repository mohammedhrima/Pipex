#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "libft/libft.h"

int main(int argc, char **argv)
{
	int status;
	char **arr1, **arr2;
	char *cmd1, *cmd2;
	int fd[2];
	int pid1,pid2;

	arr1 = ft_split(argv[2], ' ');
	arr2 = ft_split(argv[3], ' ');
	cmd1 = ft_strjoin("/bin/", arr1[0]);
	cmd2 = ft_strjoin("/usr/bin/", arr2[0]);
	fd[0] = open(argv[1], O_RDWR | O_CREAT, 0777);
	fd[1] = open(argv[4], O_RDWR | O_CREAT,0777);
	
	if(access(cmd1, F_OK) < 0)
	{
		printf("file is inaccessible: %s\n",cmd1);
		return 0;
	}
	if(access(cmd2, F_OK) < 0)
	{
		printf("file is inaccessible: %s\n",cmd2);
		return 0;
	}
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
	pid1 = fork();
	if(pid1 < 0)
		return 0;
	if(pid1 == 0)
	{
		//1st child process
		close(fd[1]);
		dup2(STDIN_FILENO, fd[0]);
		close(fd[0]);
		execv(cmd1, arr1);
	}
	else
	{
		wait(NULL);
		close(fd[0]);
		dup2(STDOUT_FILENO, fd[1]);
		close(fd[1]);
		execv(cmd2, arr2);
	}
	waitpid(pid1, NULL, 0);
	close(fd[0]);
	close(fd[1]);
	//access("in", F_OK); //F_OK check the existance
	
	

}