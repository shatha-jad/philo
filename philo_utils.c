/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjadalla <sjadalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 19:59:57 by sjadalla          #+#    #+#             */
/*   Updated: 2023/01/26 18:00:09 by sjadalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosopher.h"

long long int	get_time(t_data *data)
{
	struct timeval	current_time;

	(void) data;
	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void	my_sleep(t_philo *philo, int ms)
{
	long long	et;

	(void)philo;
	et = get_time(NULL);
	while ((get_time(NULL) - et) < ms)
	{
		// printf("time:%lld et:%lld\n", get_time(NULL) - et, et);
		if (get_time(NULL) - philo->last_meal >= philo->data->tdie)
			break ;
		usleep(ms);
	}
}

void	go_sleep(t_philo *philo)
{
	print_f(philo, 's');
	my_sleep(philo, philo->data->tsleep);
		// if (get_time(NULL) - philo->last_meal >= philo->data->tdie)
		// 	return ;
}

void	eating(t_philo *philo)
{
	print_f(philo, 'e');
	my_sleep(philo, philo->data->teat);
	// pthread_mutex_lock(&philo->data->mutex_meal);
	philo->last_meal = get_time(NULL);
	philo->times_ate++;
	pthread_mutex_lock(&philo->data->mutex_eat);
	if (philo->times_ate >= philo->data->n_eat)
		philo->data->all_eat = 1;
	pthread_mutex_unlock(&philo->data->mutex_eat);
		// if (get_time(NULL) - philo->last_meal >= philo->data->tdie)
		// 	return ;
}

void	death(t_data *data)
{
	unsigned int	i;

	i = 0;
	pthread_mutex_lock(&data->mutex_eat);
	pthread_mutex_lock(&data->mutex_dead);
	while (!data->death_flag && !data->all_eat)
	{
		pthread_mutex_unlock(&data->mutex_eat);
		pthread_mutex_unlock(&data->mutex_dead);
		i = 0;
		while (i < data->n_philo && !data->death_flag)
		{
			if (!death_check(&data->philo[i]))
				break ;
			i++;
		}
		usleep(100);
		pthread_mutex_lock(&data->mutex_eat);
		pthread_mutex_lock(&data->mutex_dead);
	}
	pthread_mutex_unlock(&data->mutex_eat);
	pthread_mutex_unlock(&data->mutex_dead);
}

int	death_check(t_philo *philo)
{
	long long	t;

	pthread_mutex_lock(&philo->data->mutex_dead);
	if (philo->data->death_flag)
		{
			pthread_mutex_unlock(&philo->data->mutex_dead);
			return (0);
		}
	// pthread_mutex_unlock(&philo->data->mutex_dead);
	// pthread_mutex_lock(&philo->data->mutex_meal);
	t = get_time(NULL) - philo->last_meal;
	// printf("last meal%lld for philo:%d  ", philo->last_meal, philo->philo_id);
	// pthread_mutex_unlock(&philo->data->mutex_meal);
	// pthread_mutex_lock(&philo->data->mutex_dead);
	if (t >= philo->data->tdie)
	{
		print_f(philo, 'd');
		philo->death_flag = 1;
		philo->data->death_flag = 1;
		pthread_mutex_unlock(&philo->data->mutex_dead);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->mutex_dead);
	return (1);
}


// int	is_philo_dead(t_philo *philo)
// {
// 	long long	n_time;
// 	int			flag;

// 	flag = 0;
// 	pthread_mutex_lock(&philo->data->mutex_dead);
// 	if (philo->data->death_flag)
// 		flag = 1;
// 	else
// 	{
// 		n_time = get_time(NULL) - philo->last_meal;
// 		if ((n_time) > (philo->data->tdie))
// 		{
// 			pthread_mutex_lock(&philo->data->mutex_print);
// 			print_f(philo, 'd');
// 			pthread_mutex_unlock(&philo->data->mutex_print);
// 			philo->data->death_flag = 1;
// 			philo->death_flag = 1;
// 			flag = 1;
// 		}
// 	}
// 	pthread_mutex_unlock(&philo->data->mutex_dead);
// 	return (flag);
// }