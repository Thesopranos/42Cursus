/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:46:00 by mertcaki          #+#    #+#             */
/*   Updated: 2023/12/08 19:12:44 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

char    *ft_substr(char const *s, unsigned int start, size_t len)
{
    char    *ptr;
    size_t  s_len;

    if (s == NULL)
        return (NULL);
    s_len = ft_strlen(s);
    if (start > s_len)
        return (ft_strdup(""));
    if (s_len - start < len)
        len = s_len - start;
    ptr = malloc(len + 1);
    if (ptr == NULL)
        return (NULL);
    ft_memcpy(ptr, s + start, len);
    ptr[len] = '\0';
    return (ptr);
}