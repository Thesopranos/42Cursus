/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:08:37 by mertcaki          #+#    #+#             */
/*   Updated: 2024/04/06 02:37:15 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_integer(int word)
{
	int	len;
	int	temp;

	len = 0;
	if (word == 0)
		return (write(1, "0", 1));
	if (word == -2147483648)
		return (write(1, "-2147483648", 11));
	if (word < 0)
	{
		if (write(1, "-", 1) == -1)
			return (-1);
		len++;
		word *= -1;
	}
	if (word >= 10)
	{
		temp = ft_integer(word / 10);
		if (temp == -1)
			return (-1);
		len += temp;
	}
	if (write(1, &"0123456789"[word % 10], 1) == -1)
		return (-1);
	return (len + 1);
}

int	ft_unsigned_int(unsigned int word)
{
	int	len;
	int	temp;

	len = 0;
	if (word >= 10)
	{
		temp = ft_unsigned_int(word / 10);
		if (temp == -1)
			return (-1);
		len += temp;
	}
	if (write(1, &"0123456789"[word % 10], 1) == -1)
		return (-1);
	return (len + 1);
}

int	ft_string(char *str)
{
	int	i;

	i = -1;
	if (str == NULL)
	{
		if (write(1, "(null)", 6) == -1)
			return (-1);
		return (6);
	}
	while (str[++i])
	{
		if (write(1, &str[i], 1) == -1)
			return (-1);
	}
	return (i);
}

int	ft_hexadecimal(unsigned int d, char word)
{
	int	len;
	int	temp;

	len = 0;
	if (d >= 16)
	{
		temp = ft_hexadecimal(d / 16, word);
		if (temp == -1)
			return (-1);
		len += temp;
	}
	if (word == 'X')
	{
		if (write(1, &"0123456789ABCDEF"[d % 16], 1) == -1)
			return (-1);
	}
	else if (word == 'x')
	{
		if (write(1, &"0123456789abcdef"[d % 16], 1) == -1)
			return (-1);
	}
	return (len + 1);
}

int	ft_pointer(unsigned long word, int i)
{
	int	len;
	int	temp;

	len = 0;
	if (i == 1)
	{
		if (write(1, "(nil)", 5) == -1)
			return (-1);
		i = 0;
		len += 2;
	}
	if (word >= 16)
	{
		temp = ft_pointer(word / 16, i);
		if (temp == -1)
			return (-1);
		len += temp;
	}
	if (write(1, &"0123456789abcdef"[word % 16], 1) == -1)
		return (-1);
	return (len + 1);
}
