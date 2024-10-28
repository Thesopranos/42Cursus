/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 22:02:57 by mertcaki          #+#    #+#             */
/*   Updated: 2024/10/27 22:53:58 by mertcaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				philo_id;
	int				eat_count;
	int				left_fork;
	int				right_fork;
	u_int64_t		last_eat;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	t_philo			*philo;
	u_int64_t		time_of_die;
	int				num_of_philo;
	int				time_of_eat;
	int				time_of_sleep;
	int				eat_limit;
	int				die_flag;
	u_int64_t		die_time;
	int				die_id;
	int				check_eat_count;
	int				num;
	u_int64_t		table_start_time;
	pthread_mutex_t	m_with_eat;
	pthread_mutex_t	*m_fork;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_die;
	pthread_mutex_t	m_time;
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
