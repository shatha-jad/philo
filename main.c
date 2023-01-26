/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjadalla <sjadalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 19:51:50 by sjadalla          #+#    #+#             */
/*   Updated: 2023/01/26 18:01:37 by sjadalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosopher.h"

int	print_f(t_philo *philo, char c)
{
	long long int	start_time;

	start_time = philo->data->time;
	pthread_mutex_lock(&philo->data->mutex_print);
	if (c == 'e')
	{		
		printf("%lld Philosopher %d has taken fork %d and fork %d\n", get_time(NULL) - start_time, philo->philo_id, philo->left_fork, philo->right_fork);
		printf("%lld Philosopher %d is eating\n",
			get_time(NULL) - start_time, philo->philo_id);
	}
	if (c == 's')
		printf("%lld Philosopher %d is sleeping\n",
			get_time(NULL) - start_time, philo->philo_id);
	if (c == 't')
		printf("%lld Philosopher %d is thinking\n",
			get_time(NULL) - start_time, philo->philo_id);
	if (c == 'd')
	{
		printf("%lld Philosopher %d died\n",
			get_time(NULL) - start_time, philo->philo_id);
		pthread_mutex_unlock(&philo->data->mutex_print);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->mutex_print);
	return (1);
}

void	*philo_routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	philo->times_ate = 0;
	while (!philo->data->death_flag)
	{
		while (!check_forks(philo))
			usleep(500);
		eating(philo);
		drop_forks(philo);
		go_sleep(philo);
		print_f(philo, 't');
		philo->times_ate++;
		pthread_mutex_lock(&philo->data->mutex_eat);
		if (philo->times_ate > 0 && philo->times_ate >= philo->data->n_eat)
		{
			pthread_mutex_unlock(&philo->data->mutex_eat);
			break ;
		}
		pthread_mutex_unlock(&philo->data->mutex_eat);
		// death(philo->data);
		death_check(philo);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		i;

	i = 1;
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
	// while (argv[i])
	// {
	// 	if (ft_atoi(argv[i]) == 0)
	// 	{
	// 		error(data, 1);
	// 		return (0);
	// 	}
	// 	i++;
	// }
	// if (!arg_check(argv, data))
	// 	return (0);
	init(data);
	destroy_mutex(data);
}
