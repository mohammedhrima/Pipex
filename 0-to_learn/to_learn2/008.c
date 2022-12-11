#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void)
{
	int arr[] = {1, 2, 3, 45, 7, 3};
	int arrSize = sizeof(arr) / sizeof(int);
	int start, end;
	int fd[2];
	if (pipe(fd) == -1)
		return 1;
	int id = fork();
	if (id == -1)
		return 2;

	if (id == 0)
	{
		start = 0;
		end = arrSize / 2;
	}
	else
	{
		start = arrSize / 2;
		end = arrSize;
	}
	int sum = 0;
	int i = start;
	while (i < end)
	{
		sum += arr[i];
		i++;
	}
	printf("sum is %d\n", sum);
	if (id == 0)
	{
		close(fd[0]);
		write(fd[1], &sum, sizeof(sum));
		close(fd[1]);
	}
	else
	{
		int sum2;
		close(fd[1]);
		read(fd[0], &sum2, sizeof(sum2));
		close(fd[0]);
		int total = sum + sum2;
		printf("total sum is %d\n", total);
		wait(NULL);
	}

	return (0);
}