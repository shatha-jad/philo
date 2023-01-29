/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjadalla <sjadalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 19:54:28 by sjadalla          #+#    #+#             */
/*   Updated: 2023/01/29 15:34:21 by sjadalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include "limits.h"
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo{
	int				death_flag;
	int				philo_id;
	int long long	last_meal;
	int				left_fork;
	int				right_fork;
	unsigned int	times_ate;
	struct s_data	*data;
}	t_philo;

typedef struct s_data{
	unsigned int	n_philo;
	unsigned int	tdie;
	unsigned int	teat;
	unsigned int	tsleep;
	unsigned int	tthink;
	unsigned int	n_eat;
	unsigned int	all_eat;
	int long long	time;
	int				death_flag;
	int				forks[200];
	pthread_t		philos[200];
	pthread_mutex_t	mutex_forks[200];
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_dead;
	pthread_mutex_t	mutex_eat;
	pthread_mutex_t	mutex_meal;
	struct s_philo	philo[200];
}	t_data;

int				check_arg(char **argv, t_data *data);
int				ft_atoi(const char *str);
long long int	get_time(t_data *data);
void			threads(t_data *data);
int				mutex_intit(t_data	*data);
void			*philo_routine(void *data);
void			my_sleep(t_philo *ph, int ms);
void			drop_forks(t_philo *ph);
void			drop_forks_odd(t_philo *philo);
int				check_forks(t_philo *philo);
int				check_forks_odd(t_philo *philo);
void			print_f(t_philo *philo, char c);
void			go_sleep(t_philo *philo);
void			eating(t_philo *philo);
void			set_philos(t_data *data, t_philo *philo);
void			init(t_data *data);
void			death(t_data *data);
int				death_check(t_philo *philo);
int				death_monitor(t_data *info);
void			destroy_mutex(t_data *data);
int				check_death(t_philo *philo);
void			print_death(t_philo *philo);

#endif