/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:34:17 by mertcaki          #+#    #+#             */
/*   Updated: 2023/12/10 05:08:32 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	counter;

	counter = ft_strlen(s);
	while (counter >= 0)
	{
		if (s[counter] == (unsigned char)c)
			return ((char *)s + counter);
		counter--;
	}
	return (NULL);
}
