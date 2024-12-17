/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:14:00 by mertcaki          #+#    #+#             */
/*   Updated: 2024/11/12 04:17:21 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../cub3d.h"
#include <stdlib.h>
#include <stdio.h>

static unsigned int	ft_word_counter(const char *s, char control)
{
	unsigned int	word;

	word = 0;
	while (*s)
	{
		if (*s == control)
		{
			if (*(s + 1) == control)
				word++;
			s++;
		}
		else
		{
			while (*s != control && *s)
				s++;
			word++;
		}
	}
	return (word);
}

static char	*allocate_space_token(void)
{
	char	*token;

	token = (char *)malloc(2 * sizeof(char));
	if (token)
	{
		token[0] = ' ';
		token[1] = '\0';
	}
	return (token);
}

static char	*allocate_word_token(const char *s, char c)
{
	int		len;
	int		i;
	char	*token;

	i = 0;
	len = 0;
	len = (int)ft_charlen(s, c);
	token = (char *)malloc((len + 1) * sizeof(char));
	if (token)
	{
		while (*s && *s != c)
			token[i++] = *s++;
		token[i] = '\0';
	}
	return (token);
}

static int	process_token(char **arr, const char **s, char c, int *a)
{
	if (**s == c && *(*s + 1) == c)
	{
		arr[++(*a)] = allocate_space_token();
		if (!arr[*a])
			return (0);
		(*s)++;
	}
	else if (**s != c)
	{
		arr[++(*a)] = allocate_word_token(*s, c);
		if (!arr[*a])
			return (0);
		while (**s && **s != c)
			(*s)++;
	}
	else
		(*s)++;
	return (1);
}

char	**ft_adv_split(char const *s, char c, int *a)
{
	char	**arr;

	arr = (char **)malloc((ft_word_counter(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (*s)
	{
		if (!process_token(arr, &s, c, a))
		{
			free_array2d(arr);
			return (NULL);
		}
	}
	arr[++*a] = NULL;
	return (arr);
}
