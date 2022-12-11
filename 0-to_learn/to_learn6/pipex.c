#include "pipex.h"

char *cmd_path(char *cmd0, char **paths)
{
	int i;
	char *cmd1;
	char *cmd2;

	i = 0;
	cmd2 = NULL;
	cmd1 = ft_strjoin("/", cmd0);
	if (access(cmd1, F_OK) == 0 && access(cmd1, X_OK) == 0)
		return cmd1;
	while (paths && cmd0 && paths[i])
	{
		cmd2 = ft_strjoin(paths[i], cmd1);
		if (access(cmd2, F_OK) == 0 && access(cmd2, X_OK) == 0)
			return cmd2;
		free(cmd2);
		cmd2 = NULL;
		i++;
	}
	return (cmd2);
}

char *grep(char *arr[], char *str)
{
	int i;

	i = 0;
	while (arr[i])
	{
		if (ft_strstr(arr[i], str))
			return (arr[i]);
		i++;
	}
	return NULL;
}

int main(int argc, char **argv, char *envp[])
{
	char **arr1;
	char **arr2;
	char *cmd1;
	char *cmd2;
	char **paths;
	int in;
	int out;
	int fd[2];
	int exit_code;
	pid_t pid1;
	pid_t pid2;

	exit_code = 0;
	arr1 = ft_split2(argv[2], ' ', 3);
	arr2 = ft_split2(argv[3], ' ', 3);
	in = open(argv[1], O_RDONLY, 0777);
	out = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);

	paths = ft_split(grep(envp, "PATH"), ':');
	cmd1 = cmd_path(arr1[0], paths);
	cmd2 = cmd_path(arr2[0], paths);
	free(paths);
	if (in < 0)
		ft_putendl_fd(ft_strjoin("no such file or directory: ", argv[1]), 2);
	if (out < 0)
		out = STDOUT_FILENO;
	if (!cmd1 && in >= 0)
		ft_putendl_fd(ft_strjoin("command not found: ", arr1[0]), 2);
	if (!cmd2)
		ft_putendl_fd(ft_strjoin("command not found: ", arr2[0]), 2);
	if (pipe(fd) < 0)
	{
		perror("Error: ");
		exit(-1);
	}
	if (in < 0)
	{
		free(cmd1);
		cmd1 = NULL;
		free(arr1);
		arr1 = NULL;
	}
	pid1 = fork();
	if (pid1 < 0)
	{
		perror("Error: ");
		exit(-1);
	}
	else if (pid1 == 0)
	{
		dup2(in, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		free(arr2);
		free(cmd2);
		close(in);
		if (out > 0)
			close(out);
		if (in >= 0 && cmd1)
			execve(cmd1, arr1, NULL);
	}
	else if (pid1 > 0)
	{
		close(fd[1]);
		free(cmd1);
		free(arr1);
		close(in);
		pid2 = fork();
		if (pid2 < 0)
		{
			perror("Error: ");
			exit(-1);
		}
		else if (pid2 > 0)
		{
			wait(NULL);
			close(fd[0]);
			free(cmd2);
			free(arr2);
			if (out > 0)
				close(out);
		}
		else if (pid2 == 0)
		{
			if (out != STDOUT_FILENO)
				dup2(out, STDOUT_FILENO);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			free(arr2);
			free(cmd2);
			if (out != STDOUT_FILENO)
				close(out);
			if (cmd2)
				execve(cmd2, arr2, NULL);
		}
	}
	return (0);
}
/*
verify
*/