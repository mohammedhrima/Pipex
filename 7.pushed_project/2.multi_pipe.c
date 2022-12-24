/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.multi_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:04:23 by mhrima            #+#    #+#             */
/*   Updated: 2022/12/24 08:27:47 by mhrima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process_m(t_a *var, char *argv_i, int pipes_len, int i)
{
	char	*cmd;
	char	**arr;

	arr = ft_split2(argv_i, ' ', 3);
	cmd = cmd_path(arr[0], var->envp);
	check_cmd(cmd, arr);
	close_pipes(var, pipes_len + 1, i);
	dup2(var->pipes[i][0], STDIN_FILENO);
	dup2(var->pipes[i + 1][1], STDOUT_FILENO);
	if (execve(cmd, arr, var->envp) == -1)
	{
		if (i == pipes_len)
			exit(127);
		else
			exit(0);
	}
}

void	fork_func_m(t_a *var, int pipes_len)
{
	int	i;

	i = 0;
	while (i < pipes_len)
	{
		var->pids[i] = fork();
		if (var->pids[i] == -1)
		{
			perror("Error: ");
			exit(-1);
		}
		if (var->pids[i] == 0)
		{
			child_process_m(var, var->argv[i + 2], pipes_len, i);
		}
		else if (var->pids[i] > 0)
		{
			close(var->pipes[i][0]);
			close(var->pipes[i + 1][1]);
		}
		i++;
	}
}

void	close_pipes_wait_pids_m(t_a var, int pipes_len, int *status)
{
	int	i;

	i = 0;
	while (i < pipes_len + 1)
	{
		close(var.pipes[i][0]);
		close(var.pipes[i][1]);
		i++;
	}
	i = 0;
	while (i < pipes_len)
	{
		waitpid(var.pids[i], status, 0);
		i++;
	}
	free(var.pids);
	i = 0;
	while (i < pipes_len + 1)
	{
		free(var.pipes[i]);
		i++;
	}
	free(var.pipes);
}

void	multi_pipes(int argc, char **argv, char **envp, int *status)
{
	int	pipes_len;
	t_a	var;

	var.argv = argv;
	var.envp = envp;
	pipes_len = argc - 3;
	var.pids = (int *)allocate_1d(pipes_len, sizeof(int));
	var.pipes = (int **)allocate_2d(pipes_len + 1, sizeof(int *), 2,
			sizeof(int));
	var.pipes[0][0] = open_file(argv[1], 'r');
	var.pipes[pipes_len][1] = open_file(argv[argc - 1], 't');
	open_pipes(var.pipes, 1, pipes_len);
	fork_func_m(&var, pipes_len);
	close_pipes_wait_pids_m(var, pipes_len, status);
}
