/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:08:20 by mertcaki          #+#    #+#             */
/*   Updated: 2023/12/08 16:24:10 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
    size_t counter;
    size_t counter2;

    counter = 0;
    if (needle[0] == '\0')
        return ((char *)haystack);
    while (haystack[counter] && counter < len)
    {
        counter2 = 0;
        while (haystack[counter + counter2] == needle[counter2] && counter + counter2 < len)
        {
            if (needle[counter2 + 1] == '\0')
                return ((char *)haystack + counter);
            counter2++;
        }   
        counter++;
    }
    return (0);
}