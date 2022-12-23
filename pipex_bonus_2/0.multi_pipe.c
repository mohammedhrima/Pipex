/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.multi_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 09:58:14 by mhrima            #+#    #+#             */
/*   Updated: 2022/12/23 14:54:55 by mhrima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/*
int **open_pipes()
{

}*/

int open_file(char *name, char type)
{
	int file;

	if (type == 'i')
		file = open(name, O_RDONLY);
	if (type == 'o')
		file = open(name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (file < 0)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(name, 2);
		if (type == 'o')
			exit(1);
	}
	return file;
}

void multi_Pipes(int argc, char **argv, char **envp, int *status)
{
	int **pipes;
	int num;
	int *pids;
	char *cmd;
	char **arr;
	char **paths;
	int i;

	num = argc - 3;
	pids = (int *)allocate1(num, sizeof(int));
	pipes = (int **)allocate2(num + 1, sizeof(int *), 2, sizeof(int));
	cmd = NULL;
	arr = NULL;
	pipes[0][0] = open_file(argv[1], 'i');
	pipes[num][1] = open_file(argv[argc - 1], 'o');
	i = 1;
	paths = ft_split(grep(envp, "PATH"), ':');
	open_pipes(pipes, &i, num);

	i = 0;
	while (i < num)
	{

		pids[i] = fork();
		if (pids[i] == -1)
		{
			close(pipes[i][0]);
			close(pipes[i + 1][1]);
			cmd = NULL;
			arr = NULL;
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
					ft_putstr_fd("Error: ", 2);
					ft_putstr_fd(strerror(errno), 2);
					ft_putstr_fd(": ", 2);
					ft_putendl_fd(arr[0], 2);
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
				if (i == num)
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
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
	i = 0;
	while (i < num)
	{
		waitpid(pids[i], status, 0);
		i++;
	}
	free(pids);
	i = 0;
	while (i < num + 1)
	{
		free(pipes[i]);
		i++;
	}
	Free(paths);
	free(pipes);
}