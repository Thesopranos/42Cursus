/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meballi <meballi@student.42kocaeli.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:29:32 by beeren            #+#    #+#             */
/*   Updated: 2024/08/24 07:31:39 by meballi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

void	report(t_table *table, char *str, int number)//yazdırma fonksiyonu.
{
	pthread_mutex_lock(&table->m_time);//zamanı kilitliyor
	printf("%llu %d %s\n", get_time() - table->table_start_time, number, str);//zamanı, yazdıracağı, filozofun hangisi olduğuyla birlikte yazdırıyor.
	pthread_mutex_unlock(&table->m_time);//zamanın kilidini açıyoruz.
}

int	mutex_init(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philo)//filozof sayısı kadar fork'u oluşturmuştuk şimdi initliyoruz.
		if (pthread_mutex_init(&table->m_fork[i], NULL) != 0)
			return (table->num = i, 1);
	if (pthread_mutex_init(&table->m_print, NULL) != 0)//yazdırma için mutex
		return (write(2, "ERROR! Mutex init error.\n", 26),
			table->num = table->num_of_philo, 1);
	if (pthread_mutex_init(&table->m_die, NULL) != 0)//ölüm için mutex.
		return (write(2, "ERROR! Mutex init error.\n", 26),
			table->num = table->num_of_philo + 1, 1);
	if (pthread_mutex_init(&table->m_time, NULL) != 0)//zaman için mutex.
		return (write(2, "ERROR! Mutex init error.\n", 26),
			table->num = table->num_of_philo + 2, 1);
	if (pthread_mutex_init(&table->m_eat, NULL) != 0)//bu ne sike yarıyor bilmiyorum götten salla 
		return (write(2, "ERROR! Mutex init error.\n", 26),
			table->num = table->num_of_philo + 3, 1);
	if (pthread_mutex_init(&table->m_with_eat, NULL) != 0)//bu da aynı bok bilmiyom.
		return (write(2, "ERROR! Mutex init error.\n", 26),
			table->num = table->num_of_philo + 4, 1);//hata dönüşleri için table->num'u kullanacağız ilerde anlarsın zaten tüm mutexlerde var
	return (0);
}

void	init_philo(t_table *table)//filoların kimliklerini oluşturduğumuz fonksiyon.
{
	int	i;

	i = -1;//++ile başadığımzıdan
	while (++i < table->num_of_philo)//filozof sayısı kadar
	{
		table->philo[i].philo_id = i + 1;//filozofun id'si 
		table->philo[i].eat_count = 0;//filozofun yeme sayısı.
		table->philo[i].left_fork = i;//filozofun solundaki fork
		table->philo[i].right_fork = (i + 1) % table->num_of_philo;//son filozof'un en baştaki çatal sağına gelsin diye.
		table->philo[i].last_eat = table->table_start_time;//son yeme zamanları başta hepsinin program başlangıcı.
		table->philo[i].table = table;//güncelleme.
	}
}

int	destroy_mutex(t_table *table, int num, int flag)//mutexlerin destroy edildiği fonksiyon.
{//ör hata hangi mutex'de olursa philo_num+x kadar diyerek fonksiyona göndereceğiz ve while'de tüm forkları destroy ettikten sonra +x kadarını da edeceğiz.
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
