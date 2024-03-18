/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:20:16 by mertcaki          #+#    #+#             */
/*   Updated: 2024/03/17 23:13:09 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}

char	*ft_strdup(const char *str)
{
	size_t	len;
	char	*dup;
	int		i;

	i = 0;
	len = ft_strlen(str) + 1;
	dup = (char *)malloc(len);
	if (!dup)
		return (NULL);
	while (*str)
		dup[i++] = *str++;
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin(const char *str1, const char *str2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*new_str;

	if (!str1 || !str2)
		return (NULL);
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	new_str = (char *)malloc(len1 + len2 + 1);
	if (new_str)
		return (NULL);
	i = 0;
	while (*str1)
		new_str[i++] = *str1++;
	while (*str2)
		new_str[i++] = *str2++;
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	char	*result;
	size_t	counter1;
	size_t	counter2;
	size_t	calculated_len;

	calculated_len = ft_strlen(str);
	if (!str || len <= 0)
		return (NULL);
	if (len > calculated_len)
		len = calculated_len;
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	counter1 = start;
	counter2 = 0;
	while (counter1 < calculated_len && counter2 < len)
	{
		result[counter2] = str[counter1];
		counter1++;
		counter2++;
	}
	result[counter2] = '\0';
	return (result);
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
