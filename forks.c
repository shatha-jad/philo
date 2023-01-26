/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjadalla <sjadalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:43:30 by sjadalla          #+#    #+#             */
/*   Updated: 2023/01/26 17:58:31 by sjadalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosopher.h"

int	check_forks(t_philo *ph)
{
	pthread_mutex_lock(&ph->data->mutex_forks[ph->right_fork]);
	if (ph->data->forks[ph->right_fork])
	{
		pthread_mutex_unlock(&ph->data->mutex_forks[ph->right_fork]);
		return (0);
	}
	pthread_mutex_lock(&ph->data->mutex_forks[ph->left_fork]);
	if (ph->data->forks[ph->right_fork])
	{
		pthread_mutex_unlock(&ph->data->mutex_forks[ph->right_fork]);
		pthread_mutex_unlock(&ph->data->mutex_forks[ph->left_fork]);
		return (0);
	}
	ph->data->forks[ph->right_fork] = 1;
	ph->data->forks[ph->left_fork] = 1;
	pthread_mutex_unlock(&ph->data->mutex_forks[ph->right_fork]);
	pthread_mutex_unlock(&ph->data->mutex_forks[ph->left_fork]);
	return (1);
}
void	drop_forks(t_philo *ph)
{
	pthread_mutex_lock(&ph->data->mutex_forks[ph->right_fork]);
	pthread_mutex_lock(&ph->data->mutex_forks[ph->left_fork]);
	ph->data->forks[ph->left_fork] = 0;
	ph->data->forks[ph->right_fork] = 0;
	pthread_mutex_unlock(&ph->data->mutex_forks[ph->right_fork]);
	pthread_mutex_unlock(&ph->data->mutex_forks[ph->left_fork]);
}