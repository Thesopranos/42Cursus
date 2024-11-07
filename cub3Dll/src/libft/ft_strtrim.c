/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zumgenc <zumgenc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:06:10 by zumgenc           #+#    #+#             */
/*   Updated: 2024/05/10 14:06:11 by zumgenc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *str, char const *set)
{
	char	*trimmed;
	size_t	i;
	size_t	str_len;
	size_t	tindex;

	if (!str || !set)
		return (NULL);
	i = 0;
	str_len = ft_strlen(str);
	while (str[i] && ft_strchr(set, str[i]))
		i++;
	while (str_len > i && ft_strchr(set, str[str_len - 1]))
		str_len--;
	trimmed = (char *)malloc(sizeof(char) * (str_len - i + 1));
	if (!trimmed)
		return (NULL);
	tindex = 0;
	while (i < str_len)
		trimmed[tindex++] = str[i++];
	trimmed[tindex] = '\0';
	return (trimmed);
}
