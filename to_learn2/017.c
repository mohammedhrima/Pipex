#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int main(void)
{
	int fd[2];
	if (pipe(fd) == -1)
		return 1;
	int pid = fork();
	if (pid < 0)
		return 2;
	if (pid == 0)
	{
		// Child process
		close(fd[0]);
		char str[200];
		printf("input string:\n");
		fgets(str, 200, stdin);
		str[strlen(str) - 1] = '\0'; // because fgets will take the new alse , that's why we did put '\0' in the end
		int n = strlen(str) + 1;
		if (write(fd[1], &n, sizeof(int)) < 0)
			return 4;
		if (write(fd[1], str, n * sizeof(char)) < 0) // +1 for the null character
			return 3;
		close(fd[1]);
	}
	else
	{
		// Parent process
		close(fd[1]);
		char str[200];
		int n;

		if (read(fd[0], &n, sizeof(int)) < 0)
			return 5;
		if (read(fd[0], str, n * sizeof(char)) < 0)
			return 6;
		printf("Received: %s\n", str);
		close(fd[0]);
		wait(NULL);
	}
	return 0;
}