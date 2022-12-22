/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 05:52:22 by mhrima            #+#    #+#             */
/*   Updated: 2022/12/09 01:42:30 by mhrima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	includes2(char *str, char c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*handle_backup_and_set_res(char **bcp, char **str, char **res)
{
	int		i;
	char	*tmp;

	if (ft_strlen(*bcp))
	{
		tmp = ft_strjoin(*bcp, *str);
		*str = tmp;
		*bcp = NULL;
	}
	i = includes2(*str, '\n');
	if (i == -1)
	{
		i = ft_strlen(*str) - 1;
		free(*bcp);
		*bcp = NULL;
	}
	*bcp = ft_substr(*str, i + 1, ft_strlen(*str));
	*res = ft_substr(*str, 0, i /*+ 1*/);
	free(*str);
	*str = NULL;
	return (*res);
}

int	read_from_file_and_feed_str(char **str, char **bcp, int fd, ssize_t *r)
{
	char	*tmp;

	tmp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (tmp == NULL)
	{
		free(*str);
		return (0);
	}
	*r = read(fd, tmp, BUFFER_SIZE);
	if (*r == -1)
	{
		free(tmp);
		free(*str);
		free(*bcp);
		return (0);
	}
	tmp[*r] = '\0';
	*str = ft_strjoin(*str, tmp);
	return (1);
}

void	in_the_end_of_file(char **bcp, char **str, char **res)
{
	free(&bcp);
	free(&str);
	free(&res);
}

char	*get_next_line(int fd)
{
	char		*res;
	char		*str;
	static char	*bcp;
	ssize_t		r;

	res = NULL;
	if (fd < 0)
		return (NULL);
	str = ft_calloc(1, sizeof(char));
	if (!str)
		return (NULL);
	r = 1;
	while (r && includes2(str, '\n') == -1)
	{
		if (!r)
		{
			in_the_end_of_file(&bcp, &str, &res);
			return (NULL);
		}
		if (!read_from_file_and_feed_str(&str, &bcp, fd, &r))
			return (NULL);
	}
	return (handle_backup_and_set_res(&bcp, &str, &res));
}
