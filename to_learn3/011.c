#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "libft/libft.h"
// #include "get_next_line/get_next_line.h"

char *cmd_path(char *cmd)
{
	int fd[2];
	char *arr[] = {"whereis", NULL, NULL, NULL};

	arr[1] = cmd;
	//	printf("line 15 -> %s\n", arr[1]);
	if (pipe(fd) < 0)
		return NULL;
	pid_t pid = fork();
	if (pid < 0)
		return NULL;
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execve("/usr/bin/whereis", arr, NULL);
		close(fd[1]);
	}
	if (pid > 0)
		wait(NULL);

	return get_next_line(fd[0]);
}

int main(int argc, char **argv)
{
	// check if argc >= 4
	// printf("-> %s\n", cmd_path("ls"));

	// return 0;
	int fd[2];
	char **arr1 = ft_split2(argv[2], ' ', 3);
	char **arr2 = ft_split2(argv[3], ' ', 3);

	/*int i = -1;
	while (i++ < 3)
		printf("%d -> %s\n", i, arr1[i]);
	i = -1;
	while (i++ < 3)
		printf("%d -> %s\n", i, arr2[i]);*/

	char *cmd1 = cmd_path(arr1[0]);
	char *cmd2 = cmd_path(arr2[0]);

	//printf("cmd1 -> %s\n", cmd1);
	//printf("cmd2 -> %s\n", cmd2);

	//printf("========================================\n");
	int in = open("in", O_RDONLY | O_CREAT, 0777);
	int out = open("out", O_WRONLY | O_TRUNC | O_CREAT, 0777);

	if (!cmd1 || !cmd2)
		return -1;
	if (pipe(fd) < 0)
		return -1;


	pid_t pid1 = fork();
	if (pid1 < 0)
		return -2;
	if (pid1 == 0)
	{
		dup2(in, STDIN_FILENO);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		// char *arr[] = {"ls", "-l",NULL, NULL};
		execve(cmd1, arr1, NULL);
		close(fd[1]);
		free(cmd1);
		free(arr1);
	}
	if (pid1 > 0)
	{
		wait(NULL);
		close(fd[1]);
		free(cmd1);
	}

	pid_t pid2 = fork();
	if (pid2 < 0)
		return -3;
	if (pid2 == 0)
	{
		dup2(out, STDOUT_FILENO);
		dup2(fd[0], STDIN_FILENO);
		// char *arr[] = {"wc", "-l", NULL, NULL};
		execve(cmd2, arr2, NULL);
		close(fd[0]);
		free(cmd2);
		free(arr2);
	}
	if (pid2 > 0)
	{
		wait(NULL);
		close(fd[0]);
		free(cmd2);
	}
	free(arr1);
	free(arr2);
}