/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:27:45 by mertcaki          #+#    #+#             */
/*   Updated: 2023/12/08 18:23:35 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    *ft_memset(void *b, int c, size_t len)
{
    size_t counter;

    counter = 0;
    while (counter < len)
    {
        ((unsigned char *)b)[counter] = (unsigned char)c;
        counter++;
    }
    return (b);
}
