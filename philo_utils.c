/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjadalla <sjadalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 19:59:57 by sjadalla          #+#    #+#             */
/*   Updated: 2023/01/30 13:29:17 by sjadalla         ###   ########.fr       */
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
		if ((get_time(NULL) - et) >= philo->data->tdie)
			break ;
		usleep(ms);
	}
}

void	go_sleep(t_philo *philo)
{
	print_f(philo, 's');
	my_sleep(philo, philo->data->tsleep);
}

void	eating(t_philo *philo)
{
	print_f(philo, 'e');
	my_sleep(philo, philo->data->teat);
	pthread_mutex_lock(&philo->data->mutex_meal);
	philo->last_meal = get_time(NULL);
	pthread_mutex_unlock(&philo->data->mutex_meal);
	philo->times_ate++;
	pthread_mutex_lock(&philo->data->mutex_eat);
	if (philo->times_ate > philo->data->n_eat)
		philo->data->all_eat = 1;
	pthread_mutex_unlock(&philo->data->mutex_eat);
}
