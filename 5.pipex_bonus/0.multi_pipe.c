/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0.multi_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 09:58:14 by mhrima            #+#    #+#             */
/*   Updated: 2022/12/23 19:46:50 by mhrima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int open_file(char *name, char type)
{
	int file;

	if (type == 'r')
		file = open(name, O_RDONLY);
	if (type == 't')
		file = open(name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (type == 'a')
		file = open(name, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (file < 0)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(name, 2);
		if (type == 'w' || type == 'a')
			exit(1);
	}
	return file;
}

void func(t_var *_, int *status, char **envp, int l)
{
	int i;

	i = 0;
	while (i < _->num)
	{
		Fork(*_, i, envp);
		i++;
	}
	i = 0;
	while (i < _->num + _->k)
	{
		close(_->pipes[i][0]);
		close(_->pipes[i][1]);
		i++;
	}
	i = 0;
	while (i < _->num)
	{
		waitpid(_->pids[i], status, 0);
		i++;
	}
	free(_->pids);
	i = 0;
	while (i < l)
	{
		free(_->pipes[i]);
		i++;
	}
	free(_->pipes);
}

void multi_pipes_func(int argc, char **argv, char **envp, int *status)
{
	t_var _;

	_.num = argc - 3;
	_.k = 1;
	_.pids = (int *)allocate1(_.num, sizeof(int));
	_.pipes = (int **)allocate2(_.num + 1, sizeof(int *), 2, sizeof(int));
	_.cmd = NULL;
	_.arr = NULL;
	_.pipes[0][0] = open_file(argv[1], 'r');
	_.pipes[_.num][1] = open_file(argv[argc - 1], 't');
	_.argv = argv;
	open_pipes(_, 1);
	func(&_, status, envp, _.num + 1);
}