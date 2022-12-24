#include "pipex.h"

char *cmd_path(char *cmd0, char **paths)
{
	int i;
	char *cmd1;
	char *cmd2;

	i = 0;
	cmd2 = NULL;
	if (access(cmd0, F_OK) == 0 && access(cmd0, X_OK) == 0)
		return cmd0;
	if (cmd0 && cmd0[0] != '/')
		cmd1 = ft_strjoin("/", cmd0);
	else
		cmd1 = ft_strdup(cmd0);
	if (access(cmd1, F_OK) == 0 && access(cmd1, X_OK) == 0)
		return cmd1;
	while (paths && cmd1 && paths[i])
	{
		cmd2 = ft_strjoin(paths[i], cmd1);
		if (access(cmd2, F_OK) == 0 && access(cmd2, X_OK) == 0)
		{
			free(cmd1);
			return cmd2;
		}
		free(cmd2);
		cmd2 = NULL;
		i++;
	}
	free(cmd1);
	return (cmd2);
}

void Free(char **arr)
{
	int i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char *grep(char *arr[], char *str)
{
	int i;

	i = 0;
	while (arr && arr[i])
	{
		if (ft_strstr(arr[i], str))
			return (arr[i] + 5);
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
	char *Error;
	int in;
	int out;
	int fd[2];
	pid_t pid1;
	pid_t pid2;
	int status;

	if (argc != 5)
		return -1;
	paths = ft_split(grep(envp, "PATH"), ':');
	arr1 = ft_split2(argv[2], ' ', 3);
	arr2 = ft_split2(argv[3], ' ', 3);
	cmd1 = cmd_path(arr1[0], paths);
	cmd2 = cmd_path(arr2[0], paths);
	Free(paths);
	in = open(argv[1], O_RDONLY, 0777);
	out = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (out < 0)
	{
		Error = ft_strjoin("No such file or directory: ", argv[4]);
		ft_putendl_fd(Error, 2);
		free(Error);
		return -1;
	}
	if (in < 0)
	{
		Error = ft_strjoin("No such file or directory: ", argv[1]);
		ft_putendl_fd(Error, 2);
		free(Error);
		free(cmd1);
		cmd1 = NULL;
		Free(arr1);
		arr1 = NULL;
	}
	if (!cmd1 && in >= 0)
	{
		Error = ft_strjoin("command not found: ", arr1[0]);
		ft_putendl_fd(Error, 2);
		free(Error);
	}
	if (!cmd2)
	{
		Error = ft_strjoin("command not found: ", arr2[0]);
		ft_putendl_fd(Error, 2);
		free(Error);
	}
	if (pipe(fd) < 0)
	{
		perror("Error");
		exit(-1);
	}
	pid1 = fork();
	if (pid1 < 0)
	{
		perror("Error");
		exit(-1);
	}
	else if (pid1 == 0)
	{
		dup2(in, STDIN_FILENO);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		if (execve(cmd1, arr1, NULL) == -1)
			exit(EXIT_FAILURE);
	}
	else if (pid1 > 0)
	{
		close(fd[1]);
		free(cmd1);
		Free(arr1);
		close(in);
	}
	pid2 = fork();
	if (pid2 < 0)
	{
		perror("Error");
		exit(-1);
	}
	else if (pid2 > 0)
	{
		close(fd[0]);
		free(cmd2);
		Free(arr2);
	}
	else if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
		if (!cmd2)
			exit(127);
		if (execve(cmd2, arr2, NULL) == -1)
			exit(EXIT_FAILURE);
	}
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	system("leaks pipex");
	return (WEXITSTATUS(status));
}