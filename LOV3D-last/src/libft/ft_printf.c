/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:59:37 by mertcaki          #+#    #+#             */
/*   Updated: 2024/11/10 17:59:38 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline int	ft_putchr(char c, t_printf *x)
{
	return (x->len++, write(1, &c, 1));
}

static inline int	ft_putstr(char *s, t_printf *x)
{
	if (!s)
		s = "(null)";
	while (*s)
		if (ft_putchr(*s++, x) == -1)
			return (-1);
	return (1);
}

static inline int	ft_itoa(uintptr_t n, int base, char *s, t_printf *x)
{
	int	tab[50];
	int	mod;
	int	i;

	mod = (x->f == 'd' || x->f == 'i') + 2 * (x->f == 'p');
	i = 0;
	if (mod == 1 && (int)n < 0)
	{
		n = -n;
		if (ft_putchr('-', x) == -1)
			return (-1);
	}
	if (mod == 2 && ft_putstr("0x", x) == -1)
		return (-1);
	if (!n)
		return (ft_putchr('0', x));
	while (n)
	{
		tab[i++] = n % base;
		n /= base;
	}
	while (i--)
		if (ft_putchr(s[tab[i]], x) == -1)
			return (-1);
	return (1);
}

static inline int	format(t_printf *x)
{
	if (x->f == 'c')
		return (ft_putchr(va_arg(x->args, int), x));
	else if (x->f == 's')
		return (ft_putstr(va_arg(x->args, char *), x));
	else if (x->f == 'u')
		return (ft_itoa(va_arg(x->args, unsigned int), 10, DEC, x));
	else if (x->f == 'd' || x->f == 'i')
		return (ft_itoa(va_arg(x->args, int), 10, DEC, x));
	else if (x->f == 'p')
		return (ft_itoa(va_arg(x->args, uintptr_t), 16, HEXLOW, x));
	else if (x->f == 'x')
		return (ft_itoa(va_arg(x->args, unsigned int), 16, HEXLOW, x));
	else if (x->f == 'X')
		return (ft_itoa(va_arg(x->args, unsigned int), 16, HEXUP, x));
	else if (x->f == '%')
		return (ft_putchr('%', x));
	return (-1);
}

int	ft_printf(const char *s, ...)
{
	t_printf	x;

	x.len = 0;
	va_start(x.args, s);
	while (*s)
	{
		if (*s == '%')
		{
			x.f = *++s;
			if (format(&x) == -1)
				return (-1);
		}
		else if (ft_putchr(*s, &x) == -1)
			return (-1);
		s++;
	}
	return (va_end(x.args), x.len);
}
