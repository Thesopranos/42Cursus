/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zumgenc <zumgenc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:06:51 by zumgenc           #+#    #+#             */
/*   Updated: 2024/05/10 14:06:53 by zumgenc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = -1;
	if (dstsize != 0)
	{
		while (src[++i] && i < dstsize - 1)
			dst[i] = src[i];
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}
