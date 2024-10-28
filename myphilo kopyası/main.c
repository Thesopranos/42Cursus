/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:16:35 by beeren            #+#    #+#             */
/*   Updated: 2024/10/27 23:03:43 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	waiting_threads(t_table *table, int i)
{
	while (++i < table->num_of_philo)//her filozoyu thread olarak oluşturuyoruz ve threadleri philo_life fonksiyonunda hazırda bekletiyoruz.
	{
		if (pthread_create(&table->philo[i].thread, NULL,
				&philo_life, &table->philo[i]))
			return (1);
	}
	while (1)//main process'imiz buradan devam.
	{
		i = -1;
		while (++i < table->num_of_philo)//filozof sayısı kadar
		{
			if (dead_flag(table, &table->philo[i])//ölmesi gereken filozof var mı varsa öldüren fonksiyon.
				|| table->check_eat_count == table->num_of_philo)//her filozofumuz yeme limitine ulaşmış mı kontrolü.
			{
				table->die_id = i + 1;//ölen filozofun id'sini atıyoruz
				break ;
			}
		}
		if (i != table->num_of_philo)//masadaki filozoflardan biri ölünce i eşit olmuyor main process'de burada bitiyor. sanırım :)
			break;
	}
	return (0);
}

int	start_simulation(t_table *table, int i)
{
	if (waiting_threads(table, -1))
		return (1);
	while (++i < table->num_of_philo)
	{
		if (pthread_join(table->philo[i].thread, NULL))//thread'leri sokuyoruz.
			return (1);
	}
	if (table->die_flag)//ölü varsa waiting thread kısmı bittikten sonra, ki eat limit'den bitmediği sürece ölü oluyor.
		printf("%llu %d is died\n", table->die_time, table->die_id);//ölüyü yazdırıyoruz.
	return (0);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (arg_ctrl(ac, av))//argümanlar sadece sayı mı, max value ve argüman sayısı kontrolü yapan fonksiyon.
		return (write(2, "Wrong Arg.\n", 12), 1);
	if (arg_init(&table, av) != 0)//argümanların struct yapılarına eklendiği ve mutexlerin oluşturulup initlendiği fonksiyon.
		return (write(2, "Arg İnit Error\n", 17),
			destroy_mutex(&table, table.num, 0), 1);//hata durumunda table.num'ları destroy ediyoruz. burada neden 0 gönderiyoruz anlamadım 5 olmalı sanki.
	table.philo = (t_philo *)malloc(sizeof(t_philo) * table.num_of_philo);//filo sayısı kadar philo struct'ı oluşturuyoruz.
	if (!table.philo)//kontrol
		return (write(2, "Malloc Error\n", 14),
			destroy_mutex(&table, table.num_of_philo + 5, 1), 1);//masadaki filozof sayısı + 5 yani tüm mutexler destroy oluyor.
	if (table.num_of_philo == 0)//filozof yoksa direkt destroylayıp bitiriyoruz. aslında bunu handle etmiştik acaba başka bir amacı mı var anlamadım
		return (destroy_mutex(&table, table.num_of_philo + 5, 1), 1);//if blogu olmasa da verimli çalışır mantıken.
	init_philo(&table);//filoların kimliklerini oluşturduğumuz fonksiyon.
	if (start_simulation(&table, -1))//her şeyin başladığı yer.
		return (write(2, "Thread Created Error.\n", 23),
			destroy_mutex(&table, table.num_of_philo + 5, 1), 1);
	return (destroy_mutex(&table, table.num_of_philo + 5, 1), 0);//başarılı bir şekilde bittikten sonra mutexleri destroy ediyoruz.
}
