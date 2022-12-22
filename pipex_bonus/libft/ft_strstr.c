/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhrima <mhrima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 06:05:07 by mhrima            #+#    #+#             */
/*   Updated: 2022/12/09 06:06:10 by mhrima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*the_return(const char *needle, char *str)
{
	size_t	i;
	int		j;
	size_t	k;

	i = 0;
	if (!*needle)
		return (str);
	while (str && str[i])
	{
		k = i;
		j = 0;
		while (str[k] == needle[j] && needle[j] && str[k])
		{
			k++;
			j++;
		}
		if (!needle[j])
			return (&(str[i]));
		i++;
	}
	return (NULL);
}

char	*ft_strstr(const char *haystack, const char *needle)
{
	char	*str;

	if (ft_strncmp(needle, "", 1) == 0)
		return ((char *)haystack);
	str = (char *)haystack;
	return (the_return(needle, str));
}