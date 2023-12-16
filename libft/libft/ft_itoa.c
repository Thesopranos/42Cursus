/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 20:05:17 by mertcaki          #+#    #+#             */
/*   Updated: 2023/12/15 16:40:47 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_string_leng(int num)
{
	int	i;

	if (num == 0)
		return (1);
	i = 0;
	while (num > 0 || num < 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;
	long	nbr;

	nbr = n;
	len = ft_string_leng(nbr);
	if (n < 0)
	{
		len++;
		nbr *= -1;
	}
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (nbr > 0)
	{
		str[--len] = (nbr % 10) + 48;
		nbr /= 10;
	}
	if (n < 0)
		str[0] = '-';
	if (n == 0)
		str[0] = '0';
	return (str);
}
