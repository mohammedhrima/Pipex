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
	char **paths;
	int fd[argc - 2][2]; // verify if i open more than needed
	int pids[argc - 2];	 // verify if i open more than needed
	int status;
	int i = 0;
	int in;
	int out;
	char *Error;
	char **arr1;
	char *cmd1;
	char *msg;
	char *msg2;
	char *msg3;
	
	printf("-> argc=%d\n", argc);
	if (argc < 5)
		return -1;
	write(1, "start\n", 7);
	paths = ft_split(grep(envp, "PATH"), ':');
	in = open(argv[1], O_RDONLY, 0777);
	out = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	arr1 = ft_split2(argv[2], ' ', 3);
	cmd1 = cmd_path(arr1[0], paths);

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
	i = 0;
	while (i < argc - 3)
	{
		//	write(1, "line 105\n", 10);
		if (pipe(fd[i]) == -1)
		{
			printf("Error with creating pipe\n");
			return -1;
		}
		i++;
	}
	// first fork from "infile" to fd[0][1]
	// dup2(in, STDIN_FILENO);
	i = 0;
	while (i < argc - 3)
	{
		write(1, "line 117\n", 10);
		pids[i] = fork();
		if (pids[i] < 0)
			break;
		if (pids[i] == 0)
		{
			printf("pids[%d] -> %d\n", i, pids[i]);
			if (i == 0)
			{
				read(in, msg, 20);
			}
			else
			{
				read(fd[i][0], msg, 20 + i);
			}
			//msg2 = ft_calloc(2, sizeof(char));
			//msg2[0] = '-';
			msg3 = ft_strjoin("-", msg);
			msg = msg3;
			if (i == argc - 4)
			{
				// last fork from fd[0][n] to "outfile"
				// dup2(out, STDOUT_FILENO);
				write(STDOUT_FILENO, msg, 40);
				write(STDOUT_FILENO, "write msg: ", 12);
				write(STDOUT_FILENO, msg, 40);
				write(STDOUT_FILENO, " to out file\n", 14);
			}
			else
			{
				int j = i = 1;
				write(fd[i + 1][1], msg, 40);
				write(STDOUT_FILENO, "write msg: ", 12);
				write(STDOUT_FILENO, msg, 40);
				write(STDOUT_FILENO, " to fd ", 8);
				write(STDOUT_FILENO, &j, sizeof(int));
				write(1, "\n", 2);
			}
			exit(0);
		}
		i++;
	}
	write(fd[0][1], "heloooooo", 10);
	i = 0;
	while (i < argc - 3)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	return (WEXITSTATUS(status));
}