/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:08:33 by mertcaki          #+#    #+#             */
/*   Updated: 2024/03/15 02:43:21 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		len;
	int		temp;
	int		counter;

	counter = -1;
	len = 0;
	va_start(args, str);
	while (str[++counter] != '\0')
	{
		if (str[counter] == '%' && ft_check(str[counter + 1]))
		{
			temp = ft_format(&args, str[++counter]);
			if (temp == -1)
				return (-1);
			len += temp - 1;
		}
		else if (ft_putchar(str[counter]) == -1)
			return (-1);
		len++;
	}
	va_end(args);
	return (len);
}

int	ft_check(char str)
{
	if (str == 'c' || str == 'd' || str == 'i' || str == 'u' || str == '%'
		|| str == 's' || str == 'x' || str == 'X' || str == 'p')
		return (1);
	return (0);
}

int	ft_putchar(char x)
{
	return (write(1, &x, 1));
}

int	ft_format(va_list *args, char word)
{
	if (word == 'c')
		return (ft_putchar(va_arg((*args), int)));
	else if (word == '%')
		return (ft_putchar('%'));
	else if (word == 'd' || word == 'i')
		return (ft_integer(va_arg((*args), int)));
	else if (word == 'u')
		return (ft_unsigned_int(va_arg((*args), unsigned int)));
	else if (word == 's')
		return (ft_string(va_arg((*args), char *)));
	else if (word == 'X' || word == 'x')
		return (ft_hexadecimal(va_arg((*args), unsigned int), word));
	else if (word == 'p')
		return (ft_pointer(va_arg((*args), unsigned long), 1));
	else
		return (0);
}
