/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:15:41 by mertcaki          #+#    #+#             */
/*   Updated: 2024/03/17 23:13:21 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_copy_to_stash(char *stash, char *buf)
{
	char	*result;

	if (!stash && buf)
	{
		result = ft_strdup(buf);
		if (!result)
			return (NULL);
		return (result);
	}
	result = ft_strjoin(stash, buf);
	ft_free_stash(&stash, 0);
	return (result);
}

static int	ft_have_nl(char *str)
{
	size_t	counter;

	if (!str)
		return (0);
	counter = -1;
	while (str[++counter] != '\0')
		if (str[counter] == '\n')
			return (1);
	return (0);
}

static char	*ft_extract_line(char *stash)
{
	char	*line;
	size_t	counter1;
	size_t	counter2;

	counter1 = 0;
	if (!stash)
		return (0);
	while (stash[counter1] != '\n')
		counter1++;
	line = malloc(sizeof(char) * (counter1 + 2));
	if (!line)
		return (0);
	counter2 = 0;
	while (counter2 < counter1 + 1)
	{
		line[counter2] = stash[counter2];
		counter2++;
	}
	line[counter2] = '\0';
	return (line);
}

static char	*ft_recreate_stash(char *stash)
{
	size_t	counter;
	char	*result;

	counter = 0;
	if (!stash)
		return (NULL);
	while (stash[counter] != '\n')
		counter++;
	if (stash[counter + 1] != '\0')
		return (ft_free_stash(&stash, 0));
	result = ft_substr(stash, counter + 1, ft_strlen(stash));
	if (!result)
	{
		ft_free_stash(&stash, 0);
		return (NULL);
	}
	ft_free_stash(&stash, 0);
	return (result);
}

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	long		bytes_read;
	static char	*stash = NULL;
	char		*line;

	line = 0;
	bytes_read = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free_stash(&stash, 0));
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if ((bytes_read <= 0 && !stash) || bytes_read == -1)
			return (ft_free_stash(&stash, 0));
		buf[bytes_read] = '\0';
		stash = ft_copy_to_stash(stash, buf);
		if (ft_have_nl(stash))
		{
			line = ft_extract_line(stash);
			if (!line)
				return (ft_free_stash(&stash, 0));
			return (stash = ft_recreate_stash(stash), line);
		}
	}
	return (ft_free_stash(&stash, 1));
}
