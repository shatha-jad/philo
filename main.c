/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjadalla <sjadalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 19:51:50 by sjadalla          #+#    #+#             */
/*   Updated: 2023/01/29 16:29:31 by sjadalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosopher.h"

int	check_end(t_philo	*philo)
{
	pthread_mutex_lock(&philo->data->mutex_dead);
	pthread_mutex_lock(&philo->data->mutex_eat);
	if (philo->data->death_flag || philo->data->all_eat)
	{
		pthread_mutex_unlock(&philo->data->mutex_dead);
		pthread_mutex_unlock(&philo->data->mutex_eat);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->mutex_dead);
	pthread_mutex_unlock(&philo->data->mutex_eat);
	return (1);
}

void	print_f(t_philo *philo, char c)
{
	long long int	start_time;

	start_time = philo->data->time;
	if (!check_end(philo))
		return ;
	pthread_mutex_lock(&philo->data->mutex_print);
	if (c == 'e')
	{		
		printf("%lld Philosopher %d has taken fork %d and fork %d\n",
			get_time(NULL) - start_time, philo->philo_id, philo->left_fork + 1,
			philo->right_fork + 1);
		printf("%lld Philosopher %d is eating\n",
			get_time(NULL) - start_time, philo->philo_id);
	}
	if (c == 's')
		printf("%lld Philosopher %d is sleeping\n",
			get_time(NULL) - start_time, philo->philo_id);
	if (c == 't')
	{
		printf("%lld Philosopher %d is thinking\n",
			get_time(NULL) - start_time, philo->philo_id);
		usleep(200);
	}
	pthread_mutex_unlock(&philo->data->mutex_print);
	return ;
}

void	*philo_routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	if (!philo->philo_id % 2)
		usleep (200);
	pthread_mutex_lock(&philo->data->mutex_dead);
	pthread_mutex_lock(&philo->data->mutex_eat);
	while (!philo->data->death_flag && !philo->data->all_eat)
	{
		pthread_mutex_unlock(&philo->data->mutex_dead);
		pthread_mutex_unlock(&philo->data->mutex_eat);
		while (!check_forks(philo))
			usleep(500);
		eating(philo);
		drop_forks(philo);
		go_sleep(philo);
		print_f(philo, 't');
		usleep(500);
		pthread_mutex_lock(&philo->data->mutex_dead);
		pthread_mutex_lock(&philo->data->mutex_eat);
	}
	pthread_mutex_unlock(&philo->data->mutex_dead);
	pthread_mutex_unlock(&philo->data->mutex_eat);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (!(argc == 5 || argc == 6))
	{
		printf("Invalid number of arguements\n");
		return (0);
	}
	data = (t_data *)calloc(1, sizeof(t_data));
	if (!data)
		return (0);
	if (!(argc == 5 || argc == 6))
	{
		free(data);
		printf("Invalid number of arguements\n");
		return (0);
	}
	if (!check_arg(argv, data))
	{
		free(data);
		printf("Invalid arguements\n");
		return (0);
	}
	init(data);
	destroy_mutex(data);
}
