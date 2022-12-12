#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define PROCESS_NUM 3

int main(void)
{
	int pids[4];
	int pipes[4][2];
	int i = 0;
	while (i < 4)
	{
		if (pipe(pipes[i]) == -1)
		{
			printf("Error 0\n");
			return -1;
		}
		i++;
	}
	i = 0;
	while (i < 4)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			printf("Error 1\n");
			return -1;
		}
		if (pids[i] == 0)
		{
			int x;
			if (read(pipes[i][0], &x, sizeof(int)) == -1)
			{
				printf("Error 2\n");
				return -1;
			}
			printf("in %d Got %d\n", i, x);
			x++;
			if (write(pipes[i + 1][1], &x, sizeof(int)) == -1)
			{
				printf("Error 3\n");
				return -1;
			}
			printf("from %d Send %d\n", i, x);
			close(pipes[i][0]);
			close(pipes[i + 1][1]);
			return 0;
		}
		i++;
	}
}