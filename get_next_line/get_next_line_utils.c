/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 23:18:31 by mertcaki          #+#    #+#             */
/*   Updated: 2024/03/19 08:12:23 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dup;
	int		counter;

	counter = 0;
	len = ft_strlen(s) + 1;
	dup = (char *)malloc(len);
	if (!dup)
		return (NULL);
	while (*s)
		dup[counter++] = *s++;
	dup[counter] = '\0';
	return (dup);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	counter;
	char	*new_str;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_str = (char *)malloc(len1 + len2 + 1);
	if (!new_str)
		return (NULL);
	counter = 0;
	while (*s1)
		new_str[counter++] = *s1++;
	while (*s2)
		new_str[counter++] = *s2++;
	new_str[counter] = '\0';
	return (new_str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	counter1;
	size_t	counter2;
	size_t	calc_len;

	calc_len = ft_strlen(s);
	if (!s || len <= 0)
		return (NULL);
	if (len > calc_len)
		len = calc_len;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	counter1 = start;
	counter2 = 0;
	while (counter1 < calc_len && counter2 < len)
	{
		res[counter2] = s[counter1];
		counter1++;
		counter2++;
	}
	res[counter2] = '\0';
	return (res);
}

void	*ft_free_stash(char **stash, int create_line)
{
	char	*line;

	if (!*stash)
		return (NULL);
	if (create_line == 0)
	{
		if (*stash)
		{
			free(*stash);
			*stash = NULL;
		}
		return (NULL);
	}
	else if (create_line == 1)
	{
		line = ft_strdup(*stash);
		free(*stash);
		*stash = NULL;
		return (line);
	}
	return (NULL);
}
