/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:39:04 by mertcaki          #+#    #+#             */
/*   Updated: 2023/12/08 20:09:24 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

char    *ft_strdup(const char *s1)
{
    char    *ptr;
    size_t  len;

    len = ft_strlen(s1);
    ptr = malloc(len + 1);
    if (ptr == NULL)
        return (NULL);
    ft_memcpy(ptr, s1, len);
    ptr[len] = '\0';
    return (ptr);
}