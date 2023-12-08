/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 17:11:25 by mertcaki          #+#    #+#             */
/*   Updated: 2023/12/08 17:18:49 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

void    *ft_memcpy(void *dst, const void *src, size_t n)
{
    size_t counter;

    if (dst == src || n == 0)
        return (dst);

    counter = 0;
    while (counter < n)
    {
        ((unsigned char *)dst)[counter] = ((unsigned char *)src)[counter];
        counter++;
    }
    return (dst);
}