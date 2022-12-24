// #include "pipex.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
/*
	remove all printfs
*/
int main(int argc, char **argv, char **envp)
{
	int num = argc - 3;
	int pids[num];
	int pipes[num + 1][2];
	int i;
	i = 1;
	pipes[0][0] = open(argv[1], O_RDONLY, 0777);
	pipes[num][1] = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	while (i < num)
	{
		if (pipe(pipes[i]) == -1)
		{
			printf("Error with creating pipe\n");
			return -1;
		}
		i++;
	}
	i = 0;
	while (i < num)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			printf("Error with creating process\n");
			return -1;
		}
		if (pids[i] == 0)
		{
			// Child process
			int j = 0;
			while (j < num + 1)
			{
				if (i != j)
					close(pipes[j][0]);
				if (i + 1 != j)
					close(pipes[j][1]);
				j++;
			}
			int x = 0;
			if (read(pipes[i][0], &x, sizeof(int)) == -1)
			{
				printf("Error at reading\n");
				return -1;
			}
			printf("(%d) Got %d\n", i, x);
			x++;
			if (write(pipes[i + 1][1], &x, sizeof(int)) == -1)
			{
				printf("Error at writing\n");
				return -1;
			}
			printf("(%d) Sent %d\n", i, x);
			close(pipes[i][0]);
			close(pipes[i + 1][1]);
			return 0;
		}
		i++;
	}
	// Main process
	int j = 0;
	while (j < num + 1)
	{
		if (j != num)
			close(pipes[j][0]);
		if (j != 0)
			close(pipes[j][1]);
		j++;
	}
	i = 0;
	while (i < num)
	{
		wait(NULL);
		i++;
	}
	return (0);
}