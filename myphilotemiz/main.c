/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meballi <meballi@student.42kocaeli.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:16:35 by beeren            #+#    #+#             */
/*   Updated: 2024/05/27 19:04:12 by meballi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	waiting_threads(t_table *table, int i)
{
	while (++i < table->num_of_philo)
	{
		if (pthread_create(&table->philo[i].thread, NULL,
				&philo_life, &table->philo[i]))
			return (1);
	}
	while (1)
	{
		i = -1;
		while (++i < table->num_of_philo)
		{
			pthread_mutex_lock(&table->m_with_eat);
			if (dead_flag(table, &table->philo[i])
				|| table->check_eat_count == table->num_of_philo)
			{
				pthread_mutex_unlock(&table->m_with_eat);
				table->die_id = i + 1;
				break ;
			}
			pthread_mutex_unlock(&table->m_with_eat);
		}
		if (i != table->num_of_philo)
			break ;
	}
	return (0);
}

int	start_simulation(t_table *table, int i)
{
	if (waiting_threads(table, -1))
		return (1);
	while (++i < table->num_of_philo)
	{
		if (pthread_join(table->philo[i].thread, NULL))
			return (1);
	}
	if (table->die_flag)
		printf("%llu %d is died\n", table->die_time, table->die_id);
	return (0);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (arg_ctrl(ac, av))
		return (write(2, "Wrong Arg.\n", 12), 1);
	if (arg_init(&table, av) != 0)
		return (write(2, "Arg İnit Error\n", 17),
			destroy_mutex(&table, table.num, 0), 1);
	table.philo = (t_philo *)malloc(sizeof(t_philo) * table.num_of_philo);
	if (!table.philo)
		return (write(2, "Malloc Error\n", 14),
			destroy_mutex(&table, table.num_of_philo + 5, 1), 1);
	if (table.num_of_philo == 0)
		return (destroy_mutex(&table, table.num_of_philo + 5, 1), 1);
	init_philo(&table);
	if (start_simulation(&table, -1))
		return (write(2, "Thread Created Error.\n", 23),
			destroy_mutex(&table, table.num_of_philo + 5, 1), 1);
	return (destroy_mutex(&table, table.num_of_philo + 5, 1), 0);
}
