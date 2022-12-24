/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.here_doc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 09:57:50 by mhrima            #+#    #+#             */
/*   Updated: 2022/12/23 15:25:32 by mhrima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void here_doc(int argc, char **argv, char **envp, int *status)
{
	char *Exit;
	int **pipes;
	int pipes2[2];
	char *str;
	int *pids;
	// int pid;
	char *cmd;
	char **arr;
	char **paths;
	int i;
	char *c;
	char *tmp;

	Exit = argv[2];
	if (pipe(pipes2) == -1)
	{
		perror("Error: ");
		exit(-1);
	}
	str = NULL;
	c = ft_calloc(2, 1);
	while (!str || ft_strcmp(str, Exit))
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
		{
			ft_putendl_fd(str, pipes2[1]);
		}
	}
	close(pipes2[1]);
	close(pipes2[0]);
	free(str);
	free(c);
	str = NULL;

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
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(argv[argc - 1], 2);
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
		if (pids[i] == -1)
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
				ft_putstr_fd("Error: ", 2);
				ft_putstr_fd(strerror(errno), 2);
				ft_putstr_fd(": ", 2);
				ft_putendl_fd(arr[0], 2);
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
			close(pipes[i + 1][1]);
			cmd = NULL;
			arr = NULL;
		}
		i++;
	}
	int j = 0;
	while (j < 2)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
	i = 0;
	while (i < 2)
	{
		waitpid(pids[i], status, 0);
		i++;
	}
	free(pids);
	i = 0;
	while (i < 3)
	{
		free(pipes[i]);
		i++;
	}
	Free(paths);
	free(pipes);
}