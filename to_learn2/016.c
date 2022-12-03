#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

/*
Exercice:
1) Child process should generate random numbers and send the to the parent
2) Parent is going to sum all the numbers and print the result
*/

int main(void)
{
	int fd[2];
	if (pipe(fd) == -1)
		return 2;
	int pid = fork();
	if (pid == -1)
		return 1;
	if (pid == 0)
	{
		close(fd[0]);
		int n, i;
		int arr[10] = {};
		srand(time(NULL));
		n = rand() % 10 + 1;
		i = 0;
		printf("Generated: ");
		while (i < n)
		{
			arr[i] = rand() % 11;
			printf("%d ", arr[i]);
			i++;
		}
		printf("\n");
		if (write(fd[1], &n, sizeof(int)) < 0)
			return 4;
		printf("Sent n = %d\n",n);
		if (write(fd[1], arr, sizeof(int) * n) < 0)
			return 3;
		printf("Sent array\n");
		close(fd[1]);
	}
	else
	{
		// Parent process
		close(fd[1]);
		int arr[10];
		int n, i, sum = 0;
		if (read(fd[0], &n, sizeof(int)) < 0)
			return 5;
		printf("Received n = %d\n", n);
		if(read(fd[0], arr, sizeof(int) * n) < 0)
			return 6;
		printf("Received array\n");
		i = 0;
		while(i < n)
		{
			sum += arr[i];
			i++;
		}
		printf("sum is %d\n", sum);
		wait(NULL);
	}
	return 0;
}