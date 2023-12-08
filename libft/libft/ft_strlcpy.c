/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:30:53 by mertcaki          #+#    #+#             */
/*   Updated: 2023/12/04 14:23:08 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
    size_t counter;

    counter = 0;
    if (dstsize == 0)
        return (ft_strlen(src));
    while (src[counter] && counter < dstsize - 1)
    {
        dst[counter] = src[counter];
        counter++;
    }
    dst[counter] = '\0';
    return (ft_strlen(src));
}