/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:23:33 by mertcaki          #+#    #+#             */
/*   Updated: 2023/12/08 18:20:06 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

size_t ft_strlcat(char *dst, const char *src, size_t dstsize)
{
    size_t counter;
    size_t dst_len;
    size_t src_len;

    counter = 0;
    dst_len = ft_strlen(dst);
    src_len = ft_strlen(src);
    if (dstsize <= dst_len)
        return (dstsize + src_len);
    while (src[counter] && dst_len + counter < dstsize - 1)
    {
        dst[dst_len + counter] = src[counter];
        counter++;
    }
    dst[dst_len + counter] = '\0';
    return (dst_len + src_len);
}