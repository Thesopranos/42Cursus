/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 22:16:15 by mertcaki          #+#    #+#             */
/*   Updated: 2024/10/27 22:16:40 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

u_int64_t	get_time(void)

{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	time_sleep(u_int64_t time)
{
	u_int64_t	start;

	start = get_time() + time;
	while (get_time() < start)
		usleep(200);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_no_malloc(t_table *table, int flag)
{
	if (flag)
		free(table->philo);
	free(table->m_fork);
	return (0);
}
