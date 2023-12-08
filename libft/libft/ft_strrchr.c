/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:34:17 by mertcaki          #+#    #+#             */
/*   Updated: 2023/12/08 19:18:59 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


char	*ft_strrchr(const char *s, int c)
{
    int	counter;

    counter = 0;
    while (s[counter])
        counter++;
    while (counter >= 0)
    {
        if (s[counter] == c)
            return ((char *)s + counter);
        counter--;
    }
    return (0);
}
