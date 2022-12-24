/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4.tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:03:07 by mhrima            #+#    #+#             */
/*   Updated: 2022/12/24 08:28:03 by mhrima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

void	check_cmd(char *cmd, char **arr)
{
	if (!cmd)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(arr[0], 2);
	}
}

void	close_pipes(t_a *var, int len, int current_index)
{
	int	j;

	j = 0;
	while (j < len)
	{
		if (current_index != j)
			close(var->pipes[j][0]);
		if (current_index + 1 != j)
			close(var->pipes[j][1]);
		j++;
	}
}

void	open_pipes(int **pipes, int i, int len)
{
	while (i < len)
	{
		if (pipe(pipes[i]) == -1)
		{
			while (i > 0)
			{
				close(pipes[i][0]);
				close(pipes[i][1]);
				i--;
			}
			perror("Error: ");
			exit(-1);
		}
		i++;
	}
}
