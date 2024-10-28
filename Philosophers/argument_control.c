/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 22:07:55 by mertcaki          #+#    #+#             */
/*   Updated: 2024/10/27 22:15:38 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '0')
		return (1);
	if (str[i] == 43)
		i++;
	if (!('0' <= str[i] && str[i] <= '9'))
		return (1);
	while (str[i])
	{
		if (!('0' <= str[i] && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

static int	check_numb(char **av)

{
	int	i;

	i = 0;
	while (++i < 5)
	{
		if (is_numeric(av[i]))
			return (1);
	}
	if (!!av[5])
	{
		if (is_numeric(av[5]))
			return (1);
	}
	return (0);
}

static int	ft_atoi(char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	if (!str)
		return (0);
	while (str[i] <= 32)
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		result = result * 10 + (str[i++] - 48);
		if (result > 2147483647 && str[i])
			return (0);
	}
	return (result);
}

int	arg_init(t_table *table, char **av)
{
	table->num_of_philo = ft_atoi(av[1]);
	table->time_of_die = ft_atoi(av[2]);
	table->time_of_eat = ft_atoi(av[3]);
	table->time_of_sleep = ft_atoi(av[4]);
	table->eat_limit = -1;
	table->check_eat_count = 0;
	table->num = 0;
	table->table_start_time = get_time();
	table->philo = NULL;
	if (av[5])
		table->eat_limit = ft_atoi(av[5]);
	table->m_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* table->num_of_philo);
	if (!table->m_fork || table->num_of_philo == 0 || table->time_of_die == 0
		|| table->time_of_eat == 0 || table->time_of_sleep == 0
		|| table->eat_limit == 0)
		return (1);
	if (mutex_init(table))
		return (1);
	return (0);
}

int	arg_ctrl(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (1);
	if (check_numb(argv))
		return (1);
	return (0);
}
