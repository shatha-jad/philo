/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjadalla <sjadalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:43:30 by sjadalla          #+#    #+#             */
/*   Updated: 2023/01/29 16:19:17 by sjadalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosopher.h"

int	check_forks(t_philo *philo)
{
	if (philo->philo_id % 2 != 0)
		return (check_forks_odd(philo));
	pthread_mutex_lock(&philo->data->mutex_forks[philo->right_fork]);
	if (philo->data->forks[philo->right_fork])
	{
		pthread_mutex_unlock(&philo->data->mutex_forks[philo->right_fork]);
		return (0);
	}
	pthread_mutex_lock(&philo->data->mutex_forks[philo->left_fork]);
	if (philo->data->forks[philo->left_fork])
	{
		pthread_mutex_unlock(&philo->data->mutex_forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->data->mutex_forks[philo->left_fork]);
		return (0);
	}
	philo->data->forks[philo->right_fork] = 1;
	philo->data->forks[philo->left_fork] = 1;
	pthread_mutex_unlock(&philo->data->mutex_forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->mutex_forks[philo->left_fork]);
	return (1);
}

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
		pthread_mutex_unlock(&philo->data->mutex_forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->mutex_forks[philo->right_fork]);
		return (0);
	}
	philo->data->forks[philo->left_fork] = 1;
	philo->data->forks[philo->right_fork] = 1;
	pthread_mutex_unlock(&philo->data->mutex_forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->mutex_forks[philo->right_fork]);
	return (1);
}

void	drop_forks(t_philo *philo)
{
	if (philo->philo_id % 2 != 0)
	{
		drop_forks_odd(philo);
		return ;
	}
	pthread_mutex_lock(&philo->data->mutex_forks[philo->right_fork]);
	pthread_mutex_lock(&philo->data->mutex_forks[philo->left_fork]);
	philo->data->forks[philo->right_fork] = 0;
	philo->data->forks[philo->left_fork] = 0;
	pthread_mutex_unlock(&philo->data->mutex_forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->mutex_forks[philo->left_fork]);
}

void	drop_forks_odd(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_forks[philo->left_fork]);
	pthread_mutex_lock(&philo->data->mutex_forks[philo->right_fork]);
	philo->data->forks[philo->left_fork] = 0;
	philo->data->forks[philo->right_fork] = 0;
	pthread_mutex_unlock(&philo->data->mutex_forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->mutex_forks[philo->right_fork]);
}
