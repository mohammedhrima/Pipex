#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "libft/libft.h"

char *cmd_path(char *cmd0, char **paths)
{
	int i;
	char *cmd1;
	char *cmd2;

	i = 0;
	cmd2 = NULL;
	cmd1 = ft_strjoin("/", cmd0);
	while (paths && cmd0 && paths[i])
	{
		cmd2 = ft_strjoin(paths[i], cmd1);
		if (access(cmd2, F_OK) == 0 && access(cmd2, X_OK) == 0)
			return cmd2;
		cmd2 = NULL;
		i++;
	}
	return (cmd2);
}

char *grep(char *envp[], char *str)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strstr(envp[i], str))
			return (envp[i]);
		i++;
	}
	return NULL;
}

int main(int argc, char *argv[], char *envp[])
{
	char **paths;
	int fd[2];
	char **arr1;
	char **arr2;
	char *cmd1;
	char *cmd2;
	int in;
	int out;
	pid_t pid1;
	pid_t pid2;

	paths = ft_split(grep(envp, "PATH") + 5, ':');
	arr1 = ft_split2(argv[2], ' ', 3);
	arr2 = ft_split2(argv[3], ' ', 3);
	cmd1 = cmd_path(arr1[0], paths);
	cmd2 = cmd_path(arr2[0], paths);
	in = open(argv[1], O_RDONLY | O_CREAT, 0777);
	out = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (pipe(fd) < 0)
		return -1;
	pid1 = fork();
	if (pid1 < 0)
		return -2;
	if (pid1 == 0)
	{
		dup2(in, STDIN_FILENO);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
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
		free(arr1);
	}

	pid2 = fork();
	if (pid2 < 0)
		return -3;
	if (pid2 == 0)
	{
		dup2(out, STDOUT_FILENO);
		dup2(fd[0], STDIN_FILENO);
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
		free(arr2);
	}
	return (0);
}