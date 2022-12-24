/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5.tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:11:39 by mhrima            #+#    #+#             */
/*   Updated: 2022/12/24 09:10:05 by mhrima           ###   ########.fr       */
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

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1)
		return (ft_strlen(s2));
	if (!s2)
		return (ft_strlen(s1));
	while (s1 && s2 && s1[i] && s2[i])
	{
		if (((unsigned char *)s1)[i] == ((unsigned char *)s2)[i])
			i++;
		else
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
	}
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		*ptr = c;
		ptr++;
		i++;
	}
	return (b);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
