/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:28:00 by mertcaki          #+#    #+#             */
/*   Updated: 2023/12/08 18:31:42 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

int     ft_memcmp(const void *s1, const void *s2, size_t n)
{
    size_t counter;

    counter = 0;
    while (counter < n)
    {
        if (((unsigned char *)s1)[counter] != ((unsigned char *)s2)[counter])
            return (((unsigned char *)s1)[counter] - ((unsigned char *)s2)[counter]);
        counter++;
    }
    return (0);
}