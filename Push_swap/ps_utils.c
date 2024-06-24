/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:30:32 by mertcaki          #+#    #+#             */
/*   Updated: 2024/06/08 16:02:15 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ps_strlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ps_atoi2(char *str, int *sign)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

int	ps_atoi(char *str, t_stack *stack, char **av, int control)
{
	unsigned int		i;
	int					sign;
	unsigned long int	num;

	num = 0;
	sign = 1;
	i = ps_atoi2(str, &sign);
	if (!(ft_is_num(str)))
		ft_free_av(av, stack, control);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			ft_free_av(av, stack, control);
		num = (str[i] - '0') + (num * 10);
		i++;
	}
	if ((num > 2147483648 && sign == -1) || (num > 2147483647 && sign == 1))
		ft_free_av(av, stack, control);
	return (num * sign);
}
