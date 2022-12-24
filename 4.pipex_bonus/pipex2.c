/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 04:46:12 by mhrima            #+#    #+#             */
/*   Updated: 2022/12/23 09:53:29 by mhrima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *get_path_from_env_path(char *cmd1, char **paths)
{
	char *cmd2;
	int i;

	i = 0;
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
	return (get_path_from_env_path(cmd1, paths));
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
	arr = NULL;
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
int main(int argc, char **argv, char **envp)
{
	int num;
	int *pids;
	int **pipes;
	int pipes2[2];
	int i;
	char **arr;
	char *cmd;
	char *str;
	char **paths;
	char *Error;
	int status;
	char *Exit;
	char *c;
	char *tmp;

	if (argc < 5)
		exit(1);
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		Exit = argv[2];
		if (pipe(pipes2) == -1)
		{
			perror("Error: ");
			exit(-1);
		}
		str = NULL;
		c = ft_calloc(2, 1);
		while (ft_strcmp(str, Exit))
		{
			free(str);
			str = ft_calloc(1, 1);
			while (read(STDIN_FILENO, c, 1) >= 0 && *c != '\n')
			{
				tmp = ft_strjoin(str, c);
				free(str);
				str = tmp;
			}
			if (ft_strcmp(str, Exit))
				ft_putendl_fd(str, pipes2[1]);
		}
		free(str);
		free(c);
		str = NULL;
		close(pipes2[0]);
		close(pipes2[1]);
		// execute commands
		pids = (int *)malloc(3 * sizeof(int));
		pipes = (int **)malloc(3 * sizeof(int *));
		i = 0;
		while (i < 3)
		{
			pipes[i] = (int *)malloc(2 * sizeof(int));
			i++;
		}
		cmd = NULL;
		arr = NULL;
		pipes[2][1] = open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);

		if (pipes[2][1] < 0)
		{
			Error = ft_strjoin("permission denied: ", argv[argc - 1]);
			ft_putendl_fd(Error, 2);
			free(Error);
			exit(1);
		}
		paths = ft_split(grep(envp, "PATH"), ':');
		i = 0;
		while (i < 2)
		{
			if (pipe(pipes[i]) == -1)
			{
				perror("Error: ");
				exit(-1);
			}
			i++;
		}
		i = 0;
		while (i < 2)
		{
			pids[i] = fork();
			if (pids[i] < 0)
			{
				perror("Error: ");
				exit(-1);
			}
			if (pids[i] == 0)
			{
				arr = ft_split2(argv[3 + i], ' ', 3);
				cmd = cmd_path(arr[0], paths);
				if (!cmd)
				{
					Error = ft_strjoin("command not found: ", arr[0]);
					ft_putendl_fd(Error, 2);
					free(Error);
				}
				Free(paths);
				int j = 0;
				while (j < 2)
				{
					if (i != j)
						close(pipes[j][0]);
					if (i + 1 != j)
						close(pipes[j][1]);
					j++;
				}
				dup2(pipes[i][0], STDIN_FILENO);
				dup2(pipes[i + 1][1], STDOUT_FILENO);
				if (execve(cmd, arr, envp) == -1)
				{
					if (i == 2)
						exit(127);
					else
						exit(0);
				}
			}
			else if (pids[0] > 0)
			{
				close(pipes[i][0]);
				close(pipes[i][1]);
				cmd = NULL;
				arr = NULL;
			}
			i++;
		}
		i = 0;
		while (i < 2)
		{
			waitpid(pids[i], &status, 0);
			i++;
		}
	}
	else
	{
		num = argc - 3;
		pids = (int *)malloc(num * sizeof(int));
		pipes = (int **)malloc((num + 1) * sizeof(int *));
		i = 0;
		while (i < num + 1)
		{
			pipes[i] = (int *)malloc(2 * sizeof(int));
			i++;
		}
		cmd = NULL;
		arr = NULL;

		pipes[0][0] = open(argv[1], O_RDONLY);
		pipes[num][1] = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (pipes[num][1] < 0)
		{
			Error = ft_strjoin("permission denied: ", argv[argc - 1]);
			ft_putendl_fd(Error, 2);
			free(Error);
			exit(1);
		}
		if (pipes[0][0] < 0)
		{
			Error = ft_strjoin("No such file or directory: ", argv[1]);
			ft_putendl_fd(Error, 2);
			free(Error);
		}
		i = 1;
		paths = ft_split(grep(envp, "PATH"), ':');
		while (i < num)
		{
			if (pipe(pipes[i]) == -1)
			{
				perror("Error: ");
				exit(-1);
			}
			i++;
		}
		i = 0;
		while (i < num)
		{

			pids[i] = fork();
			if (pids[i] == -1)
			{
				perror("Error: ");
				exit(-1);
			}
			if (pids[i] == 0)
			{
				if (pipes[i][0] >= 0)
				{
					arr = ft_split2(argv[i + 2], ' ', 3);
					cmd = cmd_path(arr[0], paths);
					if (!cmd)
					{
						Error = ft_strjoin("command not found: ", arr[0]);
						ft_putendl_fd(Error, 2);
						free(Error);
					}
				}
				Free(paths);
				int j = 0;
				while (j < num + 1)
				{
					if (i != j)
						close(pipes[j][0]);
					if (i + 1 != j)
						close(pipes[j][1]);
					j++;
				}
				dup2(pipes[i][0], STDIN_FILENO);
				dup2(pipes[i + 1][1], STDOUT_FILENO);
				if (execve(cmd, arr, envp) == -1)
				{
					if (i == 2)
						exit(127);
					else
						exit(0);
				}
			}
			else if (pids[i] > 0)
			{
				close(pipes[i][0]);
				close(pipes[i + 1][1]);
				cmd = NULL;
				arr = NULL;
			}
			i++;
		}
		int j = 0;
		while (j < num + 1)
		{
			if (i != j)
				close(pipes[j][0]);
			if (i + 1 != j)
				close(pipes[j][1]);
			j++;
		}
		i = 0;
		while (i < num)
		{
			waitpid(pids[i], &status, 0);
			i++;
		}
	}
	return (WEXITSTATUS(status));
}