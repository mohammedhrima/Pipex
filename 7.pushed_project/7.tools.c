/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7.tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 09:00:21 by mhrima            #+#    #+#             */
/*   Updated: 2022/12/24 09:10:34 by mhrima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

char	*ft_strstr(char *from, char *to_find)
{
	int	i;
	int	k;
	int	j;

	if (!from || !to_find)
		return (NULL);
	i = 0;
	while (from[i])
	{
		k = i;
		j = 0;
		while (from[k] == to_find[j] && to_find[j] && from[k])
		{
			k++;
			j++;
		}
		if (!to_find[j])
			return (from + i);
		i++;
	}
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		i;

	ptr = (char *)ft_calloc((ft_strlen(s) + 1), sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (c == 0 && s[i] == 0)
		return ((char *)(s + i));
	return ((char *) NULL);
}
