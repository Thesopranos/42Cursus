/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transactions_a.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:32:44 by mertcaki          #+#    #+#             */
/*   Updated: 2024/06/07 15:32:45 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>

void	pa(t_stack *s, int print)
{
	int	i;

	if (s->size_b)
	{
		s->size_a++;
		i = s->size_a;
		while (--i > 0)
			s->a[i] = s->a[i - 1];
		s->a[0] = s->b[0];
		i = -1;
		s->size_b--;
		while (++i < s->size_b)
			s->b[i] = s->b[i + 1];
		if (!print)
			write(1, "pa\n", 3);
	}
}

void	sa(t_stack *s, int print)
{
	int	tmp;

	tmp = 0;
	tmp = s->a[0];
	s->a[0] = s->a[1];
	s->a[1] = tmp;
	if (!print)
		write(1, "sa\n", 3);
}

void	ra(t_stack *s, int print)
{
	int	tmp;
	int	i;

	i = 0;
	tmp = s->a[i];
	i++;
	while (i < s->size_a)
	{
		s->a[i - 1] = s->a[i];
		i++;
	}
	s->a[i - 1] = tmp;
	if (!print)
		write(1, "ra\n", 3);
}

void	rra(t_stack *s, int print)
{
	int	tmp;
	int	i;

	i = s->size_a - 1;
	tmp = s->a[i];
	while (i)
	{
		s->a[i] = s->a[i - 1];
		i--;
	}
	s->a[i] = tmp;
	if (!print)
		write(1, "rra\n", 4);
}
