/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:11:39 by mhrima            #+#    #+#             */
/*   Updated: 2022/12/24 08:12:29 by mhrima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*grep(char *arr[], char *str)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		if (ft_strstr(arr[i], str))
			return (arr[i] + 5);
		i++;
	}
	return (NULL);
}

int	open_file(char *name, char type)
{
	int	file;

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
	return (file);
}
