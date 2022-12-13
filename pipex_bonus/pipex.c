//#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#define NUM 5

int main(void)
{
	int fd[NUM][2];
	int pids[NUM];
	int i = 0;
	while (i < NUM)
	{
		pipe(fd[i]);
		if (pipe(fd[i]) == -1)
		{
			printf("Error with creating pipe\n");
			return -1;
		}
		i++;
	}
	int x = 1;
	write(fd[0][1], &x, sizeof(int));
	i = 0;
	while (i < NUM - 1)
	{
		pids[i] = fork();
		if (pids[i] < 0)
			break;
		if (pids[i] == 0)
		{
			int y;
			read(fd[i][0], &y, sizeof(int));
			printf("i -> %d y -> %d\n", i, y);
			y++;
			write(fd[i + 1][1], &y, sizeof(int));
		}
		i++;
	}
	int z;
	read(fd[i][0],&z, sizeof(int));
	printf("-> %d\n",z);
	i = 0;
	while (i < NUM - 1)
	{
		wait(NULL);
		i++;
	}
	
}