/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjadalla <sjadalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:43:30 by sjadalla          #+#    #+#             */
/*   Updated: 2023/01/28 18:03:27 by sjadalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosopher.h"

int	check_forks_odd(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_forks[philo->left_fork]);
	if (philo->data->forks[philo->left_fork])
	{
		pthread_mutex_unlock(&philo->data->mutex_forks[philo->left_fork]);
		return (0);
	}
	pthread_mutex_lock(&philo->data->mutex_forks[philo->right_fork]);
	if (philo->data->forks[philo->right_fork])
	{
		pthread_mutex_unlock(&philo->data->mutex_forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->data->mutex_forks[philo->left_fork]);
		return (0);
	}
	philo->data->forks[philo->right_fork] = 1;
	philo->data->forks[philo->left_fork] = 1;
	pthread_mutex_unlock(&philo->data->mutex_forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->mutex_forks[philo->right_fork]);
	return (1);
}

int	check_forks(t_philo *philo)
{
	if (philo->philo_id % 2 > 0)
		return(check_forks_odd(philo));
	pthread_mutex_lock(&philo->data->mutex_forks[philo->right_fork]);
	if (philo->data->forks[philo->right_fork])
	{
		pthread_mutex_unlock(&philo->data->mutex_forks[philo->right_fork]);
		return (0);
	}
	pthread_mutex_lock(&philo->data->mutex_forks[philo->left_fork]);
	if (philo->data->forks[philo->left_fork])
	{
		pthread_mutex_unlock(&philo->data->mutex_forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->mutex_forks[philo->right_fork]);
		return (0);
	}
	philo->data->forks[philo->right_fork] = 1;
	philo->data->forks[philo->left_fork] = 1;
	pthread_mutex_unlock(&philo->data->mutex_forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->mutex_forks[philo->left_fork]);
	return (1);
}


void	drop_forks_odd(t_philo *philo)
{
	// long long int	start_time;

	// start_time = philo->data->time;
	pthread_mutex_lock(&philo->data->mutex_forks[philo->left_fork]);
	pthread_mutex_lock(&philo->data->mutex_forks[philo->right_fork]);
	philo->data->forks[philo->left_fork] = 0;
	philo->data->forks[philo->right_fork] = 0;
	// pthread_mutex_lock(&philo->data->mutex_print);
	// printf("%lld Philosopher %d has dropped fork %d and fork %d\n", get_time(NULL) - start_time, philo->philo_id, philo->left_fork + 1, philo->right_fork + 1); 
	// pthread_mutex_unlock(&philo->data->mutex_print);
	pthread_mutex_unlock(&philo->data->mutex_forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->mutex_forks[philo->right_fork]);
}

void	drop_forks(t_philo *philo)
{
	// long long int	start_time;

	// start_time = philo->data->time;
	if (philo->philo_id % 2 > 0)
	{
		drop_forks_odd(philo);
		return;		
	}
	pthread_mutex_lock(&philo->data->mutex_forks[philo->right_fork]);
	pthread_mutex_lock(&philo->data->mutex_forks[philo->left_fork]);
	philo->data->forks[philo->left_fork] = 0;
	philo->data->forks[philo->right_fork] = 0;
	// pthread_mutex_lock(&philo->data->mutex_print);
	// printf("%lld Philosopher %d has dropped fork %d and fork %d\n", get_time(NULL) - start_time, philo->philo_id, philo->left_fork + 1, philo->right_fork + 1); 
	// pthread_mutex_unlock(&philo->data->mutex_print);
	pthread_mutex_unlock(&philo->data->mutex_forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->mutex_forks[philo->left_fork]);
}