/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:55:57 by beeren            #+#    #+#             */
/*   Updated: 2024/10/27 23:03:54 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>//thread değişkenini kullanıyoruz burada da olması lazım.

typedef struct s_philo//her filo kendi kimliğine sahip olacak bu da filozofların kendi kimlikleri için oluşturduğumuz struct.
{
	pthread_t		thread;//thread
	int				philo_id;//philo num
	int				eat_count;//yeme sayısı 5. argüman kontrolü için.
	int				left_fork;//sol çatal
	int				right_fork;//sağ çatal
	u_int64_t		last_eat;//son yediği süre.
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	t_philo			*philo;
	u_int64_t		time_of_die;//ölüm süresi
	int				num_of_philo;//filo sayısı.
	int				time_of_eat;//yeme süresi
	int				time_of_sleep;//uyku süresi
	int				eat_limit;//5. argüman yeme limit
	int				die_flag;//ölü bildirim flagi
	u_int64_t		die_time;//ölüm zamanı
	int				die_id;//ölen filo id'si
	int				check_eat_count;//yeme sayısı kontrolü
	int				num;// mutexleri destroy ederken mutex sayısını tutmak için.
	u_int64_t		table_start_time;//başlangıç zamanı
	pthread_mutex_t	*m_fork;//mutex
	pthread_mutex_t	m_print;//mutex
	pthread_mutex_t	m_die;//mutex
	pthread_mutex_t	m_time;//mutuex
}	t_table;

int			arg_ctrl(int ac, char **av);
int			arg_init(t_table *table, char **av);
int			destroy_mutex(t_table *table, int num, int flag);
void		init_philo(t_table *table);
int			mutex_init(t_table *table);
void		report(t_table *philo, char *str, int number);
int			start_simulation(t_table *table, int i);
int			waiting_threads(t_table *table, int i);
void		*philo_life(void *arg);
u_int64_t	get_time(void);
void		time_sleep(u_int64_t time);
int			ft_no_malloc(t_table *table, int flag);
int			dead_flag(t_table *table, t_philo *philo);
int			lfork(t_table *table, t_philo *philo);
int			letsgo(t_table *table, t_philo *philo);
int			ft_strlen(char *s);

#endif
