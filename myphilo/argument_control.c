/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 04:32:17 by beeren            #+#    #+#             */
/*   Updated: 2024/10/11 20:41:42 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static int	is_numeric(char *str) // numeric
{
	int i;

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
// sadece sayı mı ve int max value kontrolünün yapıldığı fonksiyon.
{
	int i;

	i = 0;
	while (++i < 5)
	{
		if (is_numeric(av[i]))
			return (1);
	}
	if (!!av[5]) // eğer argüman 5 varsa kontrol ediyoruz.
	{
		if (is_numeric(av[5]))
			return (1);
	}
	return (0);
}

static int	ft_atoi(char *str) // atoi
{
	int i;
	long result;

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
// argümanların struct yapılarına eklendiği ve mutexlerin oluşturulup initlendiği fonksiyon.
{
	table->num_of_philo = ft_atoi(av[1]);  // filozof sayısı
	table->time_of_die = ft_atoi(av[2]);   // filozofların ömrü
	table->time_of_eat = ft_atoi(av[3]); // filozofların yemek yerken harcadıkları süre
	table->time_of_sleep = ft_atoi(av[4]); // filozofların uyku süreleri.
	table->eat_limit = -1; // eat limit 5. argüman istisnai bir durum olduğu için ona -1 değeri atıyoruz bkz.93.satır. table->die_flag = 0;
	table->check_eat = 0;
	table->check_eat_count = 0;
	table->num = 0;
	table->table_start_time = get_time(); // gettimeofday fonksiyonu bilgisayarın saatiyle eş zamanlı olarak zaman çeken fonksiyon.
	table->philo = NULL;
	if (av[5])
		table->eat_limit = ft_atoi(av[5]); // 5. argüman atama.
	table->m_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* table->num_of_philo); // forkların hepsi birer mutex olacak ve her filozofun birer forku olacağından filo sayısı kadar.
	if (!table->m_fork || table->num_of_philo == 0 || table->time_of_die == 0
		|| table->time_of_eat == 0 || table->time_of_sleep == 0
		|| table->eat_limit == 0) // hata kontrolü.
		return (1);
	if (mutex_init(table))
		return (1);
	return (0);
}

int	arg_ctrl(int argc, char **argv) // argümanlar sadece sayı mı, max value ve argüman sayısı kontrolü yapan fonksiyon.
{
	if (argc != 5 && argc != 6)
		return (1);
	if (check_numb(argv))
		// sadece sayı mı ve int max value kontrolünün yapıldığı fonksiyon.
		return (1);
	return (0);
}
