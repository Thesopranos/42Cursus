/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:08:30 by mertcaki          #+#    #+#             */
/*   Updated: 2024/03/15 02:39:32 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *str, ...);
int	ft_putchar(char x);
int	ft_format(va_list *args, char word);
int	ft_integer(int word);
int	ft_unsigned_int(unsigned int word);
int	ft_string(char *str);
int	ft_hexadecimal(unsigned int d, char word);
int	ft_pointer(unsigned long word, int i);
int	ft_check(char str);
#endif
