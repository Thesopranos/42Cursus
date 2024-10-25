/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meballi <meballi@student.42kocaeli.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:29:32 by beeren            #+#    #+#             */
/*   Updated: 2024/05/30 10:48:38 by meballi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

void	report(t_table *table, char *str, int number)
{
	pthread_mutex_lock(&table->m_time);
	printf("%llu %d %s\n", get_time() - table->table_start_time, number, str);
	pthread_mutex_unlock(&table->m_time);
}

int	mutex_init(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philo)
		if (pthread_mutex_init(&table->m_fork[i], NULL) != 0)
			return (table->num = i, 1);
	if (pthread_mutex_init(&table->m_print, NULL) != 0)
		return (write(2, "ERROR! Mutex init error.\n", 26),
			table->num = table->num_of_philo, 1);
	if (pthread_mutex_init(&table->m_die, NULL) != 0)
		return (write(2, "ERROR! Mutex init error.\n", 26),
			table->num = table->num_of_philo + 1, 1);
	if (pthread_mutex_init(&table->m_time, NULL) != 0)
		return (write(2, "ERROR! Mutex init error.\n", 26),
			table->num = table->num_of_philo + 2, 1);
	if (pthread_mutex_init(&table->m_eat, NULL) != 0)
		return (write(2, "ERROR! Mutex init error.\n", 26),
			table->num = table->num_of_philo + 3, 1);
	if (pthread_mutex_init(&table->m_with_eat, NULL) != 0)
		return (write(2, "ERROR! Mutex init error.\n", 26),
			table->num = table->num_of_philo + 4, 1);
	return (0);
}

void	init_philo(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philo)
	{
		table->philo[i].philo_id = i + 1;
		table->philo[i].eat_count = 0;
		table->philo[i].left_fork = i;
		table->philo[i].right_fork = (i + 1) % table->num_of_philo;
		table->philo[i].last_eat = table->table_start_time;
		table->philo[i].table = table;
	}
}

int	destroy_mutex(t_table *table, int num, int flag)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philo && i < num)
		pthread_mutex_destroy(&table->m_fork[i]);
	if (i++ < num)
		pthread_mutex_destroy(&table->m_print);
	if (i++ < num)
		pthread_mutex_destroy(&table->m_die);
	if (i++ < num)
		pthread_mutex_destroy(&table->m_time);
	if (i++ < num)
		pthread_mutex_destroy(&table->m_eat);
	if (i++ < num)
		pthread_mutex_destroy(&table->m_with_eat);
	return (ft_no_malloc(table, flag));
}
