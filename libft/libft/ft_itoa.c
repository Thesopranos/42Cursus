/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 20:05:17 by mertcaki          #+#    #+#             */
/*   Updated: 2023/12/10 03:57:01 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_count(int n)
{
	int	counter;

	counter = 0;
	if (n <= 0)
		counter++;
	while (n != 0)
	{
		n /= 10;
		counter++;
	}
	return (counter);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		counter;
	int		sign;

	counter = ft_count(n);
	sign = 1;
	str = (char *)malloc(sizeof(char) * (counter + 1));
	if (!(str))
		return (NULL);
	str[counter] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		sign = -1;
	}
	while (counter > 0 && str[counter - 1] != '-')
	{
		str[counter - 1] = (n % 10) * sign + '0';
		n /= 10;
		counter--;
	}
	return (str);
}
