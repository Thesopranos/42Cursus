/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:36:16 by mertcaki          #+#    #+#             */
/*   Updated: 2023/12/08 20:09:21 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

void    *ft_calloc(size_t count, size_t size)
{
    void    *ptr;

    ptr = malloc(count * size);
    if (ptr == NULL)
        return (NULL);
    ft_bzero(ptr, count * size);
    return (ptr);
}