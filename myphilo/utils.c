/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meballi <meballi@student.42kocaeli.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:14:40 by beeren            #+#    #+#             */
/*   Updated: 2024/08/24 07:33:39 by meballi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

u_int64_t	get_time(void)//gettimeofday fonksiyonu bilgisayarın zamanını eş zamanlı olarak çeken fonksiyon.
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));//saniyeyi 1k ile çarpıp ve 1k mikrosaniyeye bölüp bunların ikisini toplarsak milisaniyeyi buluyorduk sanırım araştır.
}

void	time_sleep(u_int64_t time)
{
	u_int64_t	start;

	start = get_time() + time;//şimdiki zamana dışardan aldığı zamanı ekliyor ve start'a atıyor
	while (get_time() < start)//şimdiki zaman start'ı aşanakadar 200ms ekliyor.
		usleep(200);
}

int	ft_strlen(char *s)//strlen
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_no_malloc(t_table *table, int flag)//free
{
	if(flag)
		free(table->philo);
	free(table->m_fork);
	return (0);
}
