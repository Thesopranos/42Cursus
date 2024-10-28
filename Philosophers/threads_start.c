/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 22:12:31 by mertcaki          #+#    #+#             */
/*   Updated: 2024/10/27 22:15:48 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int	dead_flag(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&table->m_time);
	if (get_time() - philo->last_eat >= table->time_of_die)
	{
		pthread_mutex_unlock(&table->m_time);
		pthread_mutex_lock(&table->m_die);
		table->die_flag = 1;
		table->die_time = get_time() - table->table_start_time;
		pthread_mutex_unlock(&table->m_die);
		return (1);
	}
	pthread_mutex_unlock(&table->m_time);
	return (0);
}

static int	rfork_eat(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&table->m_fork[philo->right_fork]);
	pthread_mutex_lock(&table->m_die);
	if (table->die_flag == 1)
		return (pthread_mutex_unlock(&table->m_die), 1);
	pthread_mutex_unlock(&table->m_die);
	report(table, "has taken a right chopStick.", philo->philo_id);
	pthread_mutex_lock(&table->m_die);
	if (table->die_flag == 1)
		return (pthread_mutex_unlock(&table->m_die), 1);
	pthread_mutex_unlock(&table->m_die);
	report(table, "is eating.", philo->philo_id);
	time_sleep(table->time_of_eat);
	pthread_mutex_lock(&table->m_time);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&table->m_time);
	philo->eat_count++;
	pthread_mutex_unlock(&table->m_fork[philo->left_fork]);
	pthread_mutex_unlock(&table->m_fork[philo->right_fork]);
	return (0);
}

int	lfork(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&table->m_fork[philo->left_fork]);
	pthread_mutex_lock(&table->m_die);
	if (table->die_flag == 1)
		return (pthread_mutex_unlock(&table->m_die), 1);
	pthread_mutex_unlock(&table->m_die);
	report(table, "has taken a left chopStick.", philo->philo_id);
	if (table->num_of_philo == 1)
	{
		pthread_mutex_unlock(&table->m_fork[philo->left_fork]);
		pthread_mutex_lock(&table->m_die);
		while (table->die_flag != 1)
		{
			pthread_mutex_unlock(&table->m_die);
			usleep(100);
			pthread_mutex_lock(&table->m_die);
		}
		return (pthread_mutex_unlock(&table->m_die), 1);
	}
	return (rfork_eat(table, philo));
}

int	letsgo(t_table *table, t_philo *philo)
{
	if (lfork(table, philo) != 0)
		return (1);
	pthread_mutex_lock(&table->m_die);
	if (table->die_flag == 1)
		return (pthread_mutex_unlock(&table->m_die), 1);
	pthread_mutex_unlock(&table->m_die);
	report(table, "is sleeping.", philo->philo_id);
	time_sleep(table->time_of_sleep);
	pthread_mutex_lock(&table->m_die);
	if (table->die_flag == 1)
		return (pthread_mutex_unlock(&table->m_die), 1);
	pthread_mutex_unlock(&table->m_die);
	report(table, "is thinking.", philo->philo_id);
	return (0);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 != 1)
		time_sleep(10);
	while (!letsgo(philo->table, philo))
	{
		pthread_mutex_lock(&philo->table->m_with_eat);
		if (philo->eat_count == philo->table->eat_limit)
		{
			philo->table->check_eat_count++;
			pthread_mutex_unlock(&philo->table->m_with_eat);
			break ;
		}
		pthread_mutex_unlock(&philo->table->m_with_eat);
	}
	return (NULL);
}
