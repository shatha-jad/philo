/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjadalla <sjadalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:43:30 by sjadalla          #+#    #+#             */
/*   Updated: 2023/01/29 16:15:57 by sjadalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosopher.h"

void	init(t_data *data)
{
	set_philos(data, data->philo);
	mutex_intit(data);
	if (!mutex_intit(data))
	{
		destroy_mutex(data);
		return ;
	}
	if (data->n_philo == 1)
	{
		my_sleep(data->philo, data->tdie);
		printf("%d Philosopher %d has died\n", data->tdie, 1);
		return ;
	}
	threads(data);
}	

void	set_philos(t_data *data, t_philo	*philo)
{
	unsigned int	i;
	unsigned int	j;

	j = 0;
	i = 0;
	data->time = get_time(NULL);
	data->death_flag = 0;
	while (i < data->n_philo)
	{
		philo[i].philo_id = j + 1;
		philo[i].left_fork = j;
		philo[i].right_fork = (j + 1) % (data->n_philo);
		philo[i].death_flag = 0;
		philo[i].data = data;
		philo[i].last_meal = get_time(NULL);
		philo[i].times_ate = 0;
		data->forks[i] = 0;
		i++;
		j++;
	}
}

		// if ((j + 1) % (data->n_philo + 1) == 0)
		// 	philo[i].right_fork = 1;
		// else
		// 	philo[i].right_fork = (j + 1) % (data->n_philo + 1);

int	mutex_intit(t_data	*data)
{
	unsigned int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_init(&data->mutex_forks[i], NULL);
		i++;
	}
	if (pthread_mutex_init(&data->mutex_print, NULL))
		return (0);
	if (pthread_mutex_init(&data->mutex_dead, NULL))
		return (0);
	if (pthread_mutex_init(&data->mutex_eat, NULL))
		return (0);
	if (pthread_mutex_init(&data->mutex_meal, NULL))
		return (0);
	return (1);
}

void	threads(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->n_philo)
	{	
		pthread_create(&data->philos[i], NULL, &philo_routine, &data->philo[i]);
		usleep(100);
		i++;
	}
	death_monitor(data);
	i = 0;
	while (i < data->n_philo)
		pthread_join(data->philos[i++], NULL);
}

void	destroy_mutex(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&data->mutex_forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mutex_print);
	pthread_mutex_destroy(&data->mutex_dead);
	pthread_mutex_destroy(&data->mutex_eat);
	pthread_mutex_destroy(&data->mutex_meal);
	free(data);
}
