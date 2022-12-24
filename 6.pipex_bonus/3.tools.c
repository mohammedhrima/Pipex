/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3.tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 05:16:12 by mhrima            #+#    #+#             */
/*   Updated: 2022/12/24 08:03:34 by mhrima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*path_from_env_path(char *cmd1, char **envp)
{
	char	*cmd2;
	char	**paths;
	int		i;

	paths = ft_split(grep(envp, "PATH"), ':');
	i = 0;
	while (paths && cmd1 && paths[i])
	{
		cmd2 = ft_strjoin(paths[i], cmd1);
		if (access(cmd2, F_OK) == 0 && access(cmd2, X_OK) == 0)
		{
			free_arr(paths);
			free(cmd1);
			return (cmd2);
		}
		free(cmd2);
		cmd2 = NULL;
		i++;
	}
	free_arr(paths);
	free(cmd1);
	return (cmd2);
}

char	*cmd_path(char *cmd0, char **envp)
{
	int		i;
	char	*cmd1;
	char	*cmd2;

	i = 0;
	cmd2 = NULL;
	if (ft_strchr(cmd0, '/'))
	{
		if (access(cmd0, F_OK) == 0 && access(cmd0, X_OK) == 0)
			return (cmd0);
		return (NULL);
	}
	if (cmd0 && cmd0[0] != '/')
		cmd1 = ft_strjoin("/", cmd0);
	else
		cmd1 = ft_strdup(cmd0);
	if (access(cmd1, F_OK) == 0 && access(cmd1, X_OK) == 0)
		return (cmd1);
	return (path_from_env_path(cmd1, envp));
}

void	*allocate_1d(int len, size_t size)
{
	void	*res;

	res = malloc(len * size);
	if (!res)
		exit(1);
	return (res);
}

void	**allocate_2d(int len, size_t size, int sublen, size_t subsize)
{
	void	**res;
	int		i;

	i = 0;
	res = malloc(len * size);
	if (!res)
		exit(1);
	while (i < len)
	{
		res[i] = malloc(sublen * subsize);
		if (!res[i])
		{
			while (i > 0)
			{
				free(res[i]);
				i--;
			}
			free(res);
			exit(1);
		}
		i++;
	}
	return (res);
}
