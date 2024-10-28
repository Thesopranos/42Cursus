/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:34:08 by beeren            #+#    #+#             */
/*   Updated: 2024/10/27 23:03:50 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int	dead_flag(t_table *table, t_philo *philo)//ölmesi gereken filozof varsa öldüren fonksiyon.
{
	pthread_mutex_lock(&table->m_time);//zamanı kilitle
	if (get_time() - philo->last_eat >= table->time_of_die)//şimdiki zamandan son yeme süresini çıkarınca eğer filozofun yemek yemeden durabileceği zamandan fazla çıkıyorsa
	{
		pthread_mutex_unlock(&table->m_time);//zamanın kilidini aç
		pthread_mutex_lock(&table->m_die);//ölümü kilitle
		table->die_flag = 1;//ölü flagini 1 yap
		table->die_time = get_time() - table->table_start_time;//ölüm zamanını al
		pthread_mutex_unlock(&table->m_die);//ölümün kilidini aç
		return (1);
	}
	pthread_mutex_unlock(&table->m_time);
	return (0);
}

static int	rfork_eat(t_table *table, t_philo *philo)//sağ forku aldıran ve yediren ve ekrana bastıran fonksiyon.
{
	pthread_mutex_lock(&table->m_fork[philo->right_fork]);//sağ forku kilitliyoruz.
	pthread_mutex_lock(&table->m_die);//
	if (table->die_flag == 1)//
		return (pthread_mutex_unlock(&table->m_die), 1);//
	pthread_mutex_unlock(&table->m_die);//
	report(table, "has taken a right chopStick.", philo->philo_id);//
	pthread_mutex_lock(&table->m_die);//
	if (table->die_flag == 1)//
		return (pthread_mutex_unlock(&table->m_die), 1);//
	pthread_mutex_unlock(&table->m_die);//
	report(table, "is eating.", philo->philo_id);//
	time_sleep(table->time_of_eat);//time_sleep'e gönderip yemek yeme süresi kadar zaman aşımına sokuyoruz.
	pthread_mutex_lock(&table->m_time);//zamanı kilitliyoruz.
	philo->last_eat = get_time();//şimdiki zamanı filonun kimliğindeki son yeme zamanına atıyoruz.
	pthread_mutex_unlock(&table->m_time);//zamanın kilidini açıyoruz.
	philo->eat_count++;//filo yediği için kimliğindeki yeme sayısını arttırıyoruz.
	pthread_mutex_unlock(&table->m_fork[philo->left_fork]);//forkların kilidini açıyoruz diğer thread'ler yiyebilsin diye
	pthread_mutex_unlock(&table->m_fork[philo->right_fork]);//
	return (0);
}

int	lfork(t_table *table, t_philo *philo)//sol forku verdiğimiz ve ekrana bastırdığımız kısım
{
	pthread_mutex_lock(&table->m_fork[philo->left_fork]);//fork'u kilitliyoruz
	pthread_mutex_lock(&table->m_die);//ölümü kiliyoruz
	if (table->die_flag == 1)//ölü kontrolü
		return (pthread_mutex_unlock(&table->m_die), 1);//ölü varsa ölümün kilidini açıp durduruyoruz.
	pthread_mutex_unlock(&table->m_die);//ölü yoksa ölümün kilidini açıyoruz.
	report(table, "has taken a left chopStick.", philo->philo_id);//x filo forku aldı diye ekrana bastırıyoruz.
	if (table->num_of_philo == 1)//tek filozof 2 fork olmadan hayatta kalamaz bunu en başta handle edebilirdik ama proje bizden tek filo olsa bile ona thread açmamız gerektiğini söylüyor.
	{
		pthread_mutex_unlock(&table->m_fork[philo->left_fork]);//forkun kilidini açıyoruz
		pthread_mutex_lock(&table->m_die);//ölümü kilitliyoruz
		while (table->die_flag != 1)//ölene kadar döngüye sokuyoruz.
		{
			pthread_mutex_unlock(&table->m_die);//ölümün kilidini açıyoruz
			usleep (100);//timeout
			pthread_mutex_lock(&table->m_die);//ölümü kilitliyoruz.
		}
		return (pthread_mutex_unlock(&table->m_die), 1);//ölmüşse ölümün kilidini açıyoruz. ki proje bittiğinde kilitli mutex kalmasın.
	}
	return (rfork_eat(table, philo));
}

int	letsgo(t_table *table, t_philo *philo)
{
	if (lfork(table, philo) != 0)//yedirdik içirdik
		return (1);//sıra uykuda
	pthread_mutex_lock(&table->m_die);//ölü kontrolü
	if (table->die_flag == 1)
		return (pthread_mutex_unlock(&table->m_die), 1);
	pthread_mutex_unlock(&table->m_die);
	report(table, "is sleeping.", philo->philo_id);//filozof uyuyor
	time_sleep(table->time_of_sleep);//uyku süresi kadar uyutuyoruz.
	pthread_mutex_lock(&table->m_die);//
	if (table->die_flag == 1)//
		return (pthread_mutex_unlock(&table->m_die), 1);//
	pthread_mutex_unlock(&table->m_die);//
	report(table, "is thinking.", philo->philo_id);//düşünüyor.
	return (0);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 != 1)//2'ye tam bölünmeyen thread'ler 10ms bekletilir. fork'lar için.
		time_sleep(10);
	while (!letsgo(philo->table, philo))//
	{
		if (philo->eat_count == philo->table->eat_limit)//5. argümana eşitse
		{
			philo->table->check_eat_count++;//check eat count'ı arttırıyoruz muhtemelen tüm filozoflar aynı yesin diye kontrol var öyleymiş.
			break ;
		}
	}
	return (NULL);
}
