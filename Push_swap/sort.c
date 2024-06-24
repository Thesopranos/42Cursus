/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:32:24 by mertcaki          #+#    #+#             */
/*   Updated: 2024/06/08 16:23:16 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft/libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_is_num(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-')
		i++;
	if (s[i] == '\0')
		return (0);
	while (s[i])
	{
		if (!(ft_isdigit(s[i])))
			return (0);
		i++;
	}
	return (1);
}

int	ft_sorted_control(int *stack_x, int size, int flag)
{
	int	i;

	i = 0;
	while ((flag == 0) && (++i < size))
	{
		if (stack_x[i - 1] > stack_x[i])
			return (0);
	}
	while ((flag == 1) && (++i < size))
	{
		if (stack_x[i - 1] < stack_x[i])
			return (0);
	}
	return (1);
}

int	ft_sort(t_stack *stack, int size)
{
	if (ft_sorted_control(stack->a, stack->size_a, 0) == 0)
	{
		if (size == 2)
			sa(stack, 0);
		else if (size == 3)
			ft_sort_three(stack);
		else
			ft_first_separation(stack, size);
	}
	return (1);
}

void	recheck(t_stack *stack, int size, char **av, int control)
{
	int	i;
	int	j;

	i = -1;
	while (++i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (stack->a[i] == stack->a[j])
			{
				ft_free_av(av, stack, control);
				return ;
			}
			++j;
		}
	}
}
