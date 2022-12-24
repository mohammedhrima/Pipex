/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.here_doc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:04:14 by mhrima            #+#    #+#             */
/*   Updated: 2022/12/24 08:27:36 by mhrima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process_h(t_a *var, char *argv_i, int pipes_len, int i)
{
	char	*cmd;
	char	**arr;

	arr = ft_split2(argv_i, ' ', 3);
	cmd = cmd_path(arr[0], var->envp);
	check_cmd(cmd, arr);
	close_pipes(var, pipes_len, i);
	dup2(var->pipes[i][0], STDIN_FILENO);
	dup2(var->pipes[i + 1][1], STDOUT_FILENO);
	if (execve(cmd, arr, var->envp) == -1)
	{
		if (i == 2)
			exit(127);
		else
			exit(0);
	}
}
