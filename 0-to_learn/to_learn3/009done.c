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

	int in = open("in", O_RDWR | O_CREAT, 0777);
	int out = open("out", O_RDWR | O_CREAT | O_TRUNC, 0777);

	pid_t pid1 = fork();
	char str[3] ;//= "abcd";
	if(pid1 < 0)
		return 2;
	if (pid1 == 0 )
	{
		close(fd[0]);
		//set stdin is in file here !!
		dup2(in, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO); //replace stdout with fd write
		/*
		when executing command the output
		will be written in out file
		*/
		char *arr[] = {"ls", "-l", "-a", NULL};
		execve("/bin/ls", arr, NULL);	
	}
	if(pid1 > 0)
	{
		wait(NULL);
		close(fd[1]);
		/*
		here we used fork and run excev in child process
		because exec replace th whole process
		*/
	}
	pid_t pid2 = fork();
	if(pid2 < 0)
		return 2;
	if(pid2 == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO); //replace stdin with fd read
		dup2(out, STDOUT_FILENO);
		char *arr[] = {"wc", "-l", NULL, NULL};
		execve("/usr/bin/wc", arr, NULL);	
	}
	if(pid2 > 0)
	{
		wait(NULL);
		close(fd[0]);
	}

	return 0;
}