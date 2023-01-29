/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjadalla <sjadalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 19:59:57 by sjadalla          #+#    #+#             */
/*   Updated: 2023/01/29 15:37:15 by sjadalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosopher.h"

int	death_monitor(t_data *info)
{
	unsigned int	i;

	i = 0;
	pthread_mutex_lock(&info->mutex_eat);
	while (!info->death_flag && !info->all_eat)
	{
		pthread_mutex_unlock(&info->mutex_eat);
		i = 0;
		while (i < info->n_philo)
		{
			if (!death_check(&info->philo[i]))
				break ;
			i++;
		}
		usleep(100);
		pthread_mutex_lock(&info->mutex_eat);
	}
	pthread_mutex_unlock(&info->mutex_eat);
	return (1);
}

int	death_check(t_philo *ph)
{
	pthread_mutex_lock(&ph->data->mutex_meal);
	if (get_time(NULL) - ph->last_meal >= ph->data->tdie)
	{
		pthread_mutex_unlock(&ph->data->mutex_meal);
		print_death(ph);
		pthread_mutex_lock(&ph->data->mutex_dead);
		ph->death_flag = 1;
		ph->data->death_flag = 1;
		pthread_mutex_unlock(&ph->data->mutex_dead);
		return (0);
	}
	else
		pthread_mutex_unlock(&ph->data->mutex_meal);
	return (1);
}

void	print_death(t_philo *philo)
{
	long long int	start_time;

	start_time = philo->data->time;
	pthread_mutex_lock(&philo->data->mutex_dead);
	if (philo->data->death_flag)
	{
		pthread_mutex_unlock(&philo->data->mutex_dead);
		return ;
	}
	pthread_mutex_unlock(&philo->data->mutex_dead);
	pthread_mutex_lock(&philo->data->mutex_print);
	printf("%lld Philosopher %d died\n",
		get_time(NULL) - start_time, philo->philo_id);
	pthread_mutex_unlock(&philo->data->mutex_print);
}

// void	death(t_data *data)
// {
// 	unsigned int	i;

// 	i = 0;
// 	pthread_mutex_lock(&data->mutex_eat);
// 	pthread_mutex_lock(&data->mutex_dead);
// 	while (!data->death_flag && !data->all_eat)
// 	{
// 		pthread_mutex_unlock(&data->mutex_eat);
// 		pthread_mutex_unlock(&data->mutex_dead);
// 		i = 0;
// 		while (i < data->n_philo && !data->death_flag)
// 		{
// 			// if (data->all_eat == 1)
// 		// printf("DEATH\n");
// 			if (check_death(&data->philo[i]))
// 				break ;
// 			i++;
// 		}
// 		usleep(100);
// 		pthread_mutex_lock(&data->mutex_eat);
// 		pthread_mutex_lock(&data->mutex_dead);
// 	}
// 	pthread_mutex_unlock(&data->mutex_eat);
// 	pthread_mutex_unlock(&data->mutex_dead);
// }

// int	check_death(t_philo *philo)
// {
// 	unsigned int	i;

// 	pthread_mutex_lock(&philo->data->mutex_dead);
// 	while (!philo->death_flag && !philo->data->death_flag)
// 	{
// 		i = 0;
// 		// printf("DEATH_CHECK 1\n");
// 		while (i < philo->data->n_philo && !philo->data->death_flag)
// 		{
// 			pthread_mutex_unlock(&philo->data->mutex_dead);
// 			// printf("DEATH_CHECK 2\n");
// 			pthread_mutex_lock(&philo->data->mutex_eat);
// 			if ((get_time(NULL) - philo->last_meal) > philo->data->tdie
				//  && philo->data->all_eat == 0)
// 			{
// 				printf("last meal:%lld\n", get_time(NULL) - philo->last_meal);
// 				print_f(philo, 'd');
// 				philo->death_flag = 1;
// 				pthread_mutex_lock(&philo->data->mutex_dead);
// 				philo->data->death_flag = 1;
// 				pthread_mutex_unlock(&philo->data->mutex_dead);
// 				pthread_mutex_unlock(&philo->data->mutex_eat);
// 				return(1);
// 			}
// 			pthread_mutex_unlock(&philo->data->mutex_eat);
// 			// usleep(100);
// 			pthread_mutex_lock(&philo->data->mutex_dead);
// 			i++;
// 		}
// 	}
// 	pthread_mutex_unlock(&philo->data->mutex_dead);
// 	return (0);
// }

// int	death_check(t_philo *philo)
// {
// 	long long	t;

// 	pthread_mutex_lock(&philo->data->mutex_dead);
// 	if (philo->data->death_flag)
// 		{
// 			pthread_mutex_unlock(&philo->data->mutex_dead);
// 			return (0);
// 		}
// 	// pthread_mutex_unlock(&philo->data->mutex_dead);
// 	// pthread_mutex_lock(&philo->data->mutex_meal);
// 	t = get_time(NULL) - philo->last_meal;
// 	// printf("last meal%lld for philo:%d  ",
			// philo->last_meal, philo->philo_id);
// 	// pthread_mutex_unlock(&philo->data->mutex_meal);
// 	// pthread_mutex_lock(&philo->data->mutex_dead);
// 	if (t >= philo->data->tdie)
// 	{
// 		print_f(philo, 'd');
// 		philo->death_flag = 1;
// 		philo->data->death_flag = 1;
// 		pthread_mutex_unlock(&philo->data->mutex_dead);
// 		return (0);
// 	}
// 	pthread_mutex_unlock(&philo->data->mutex_dead);
// 	return (1);
// }
