/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 19:24:55 by mertcaki          #+#    #+#             */
/*   Updated: 2023/12/10 03:57:42 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_count_words(const char *s, char c)
{
	size_t	counter;
	size_t	words;

	counter = 0;
	words = 0;
	while (s[counter])
	{
		if (s[counter] != c)
		{
			words++;
			while (s[counter] && s[counter] != c)
				counter++;
		}
		else
			counter++;
	}
	return (words);
}

static size_t	ft_wordlen(const char *s, char c)
{
	size_t	counter;

	counter = 0;
	while (s[counter] && s[counter] != c)
		counter++;
	return (counter);
}

static char	**ft_free(char **ptr, size_t counter)
{
	while (counter > 0)
	{
		counter--;
		free(ptr[counter]);
	}
	free(ptr);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char	**ptr;
	size_t	counter;
	size_t	words;

	if (s == NULL)
		return (NULL);
	words = ft_count_words(s, c);
	ptr = (char **)malloc(sizeof(char *) * (words + 1));
	if (!(ptr))
		return (NULL);
	counter = 0;
	while (counter < words)
	{
		while (*s && *s == c)
			s++;
		ptr[counter] = ft_substr(s, 0, ft_wordlen(s, c));
		if (!(ptr))
			return (ft_free(ptr, counter));
		s += ft_wordlen(s, c);
		counter++;
	}
	ptr[counter] = NULL;
	return (ptr);
}
