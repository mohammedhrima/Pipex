/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.here_doc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:04:03 by mhrima            #+#    #+#             */
/*   Updated: 2022/12/24 08:29:28 by mhrima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fork_func_h(t_a var)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		var.pids[i] = fork();
		if (var.pids[i] == -1)
		{
			perror("Error: ");
			exit(-1);
		}
		if (var.pids[i] == 0)
			child_process_h(&var, var.argv[3 + i], 2, i);
		else if (var.pids[0] > 0)
		{
			close(var.pipes[i][0]);
			close(var.pipes[i + 1][1]);
		}
		i++;
	}
}

void	close_pipes_wait_pids_h(t_a var, int *status)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		close(var.pipes[i][0]);
		close(var.pipes[i][1]);
		i++;
	}
	i = 0;
	while (i < 2)
	{
		waitpid(var.pids[i], status, 0);
		i++;
	}
	free(var.pids);
	i = 0;
	while (i < 3)
	{
		free(var.pipes[i]);
		i++;
	}
	free(var.pipes);
}

void	read_form_her_doc(t_b *var, char *Exit)
{
	free(var->str1);
	var->str1 = ft_calloc(1, 1);
	while (read(STDIN_FILENO, var->str2, 1) >= 0 && *(var->str2) != '\n')
	{
		var->tmp = ft_strjoin(var->str1, var->str2);
		free(var->str1);
		var->str1 = var->tmp;
	}
	if (ft_strcmp(var->str1, Exit))
		ft_putendl_fd(var->str1, var->pipes2[1]);
}

void	open_here_doc(char *Exit)
{
	t_b	var;

	if (pipe(var.pipes2) == -1)
	{
		perror("Error: ");
		exit(-1);
	}
	var.str1 = NULL;
	var.str2 = ft_calloc(2, 1);
	while (!var.str1 || ft_strcmp(var.str2, Exit))
		read_form_her_doc(&var, Exit);
	close(var.pipes2[1]);
	close(var.pipes2[0]);
	free(var.str1);
	free(var.str2);
}

void	here_doc(int argc, char **argv, char **envp, int *status)
{
	t_a	var;

	open_here_doc(argv[2]);
	var.argv = argv;
	var.envp = envp;
	var.pids = (int *)allocate_1d(3, sizeof(int));
	var.pipes = (int **)allocate_2d(3, sizeof(int *), 2, sizeof(int));
	var.pipes[2][1] = open_file(argv[argc - 1], 'a');
	open_pipes(var.pipes, 0, 2);
	fork_func_h(var);
	close_pipes_wait_pids_h(var, status);
}
