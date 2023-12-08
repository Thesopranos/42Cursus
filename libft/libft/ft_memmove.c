/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:18:58 by mertcaki          #+#    #+#             */
/*   Updated: 2023/12/08 18:23:56 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

void    *ft_memmove(void *dst, const void *src, size_t len)
{
    size_t counter;

    if (dst == src || len == 0)
        return (dst);

    counter = 0;
    if (dst < src)
    {
        while (counter < len)
        {
            ((unsigned char *)dst)[counter] = ((unsigned char *)src)[counter];
            counter++;
        }
    }
    else
    {
        while (counter < len)
        {
            ((unsigned char *)dst)[len - counter - 1] = ((unsigned char *)src)[len - counter - 1];
            counter++;
        }
    }
    return (dst);
}