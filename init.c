/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 19:25:38 by chguerre          #+#    #+#             */
/*   Updated: 2026/08/21 19:56:40 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_threads(pthread_t *threads, t_philo *philo, pthread_t *dog_watch )
{
	int	i;

	i = 0;
	pthread_join(*dog_watch, NULL);
	while (i < philo->data->num_philos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

void	*create_threads(t_philo *philo, int num_philos, pthread_t *dog_watch)
{
	pthread_t	*thread;
	int			i;

	thread = malloc(sizeof(pthread_t) * num_philos);
	if (!thread)
	{
		return (NULL);
	}
	pthread_create(dog_watch, NULL, (void *)monitor, philo);
	i = 0;
	while (i < num_philos)
	{
		pthread_create(&thread[i], NULL, (void *)routine, &philo[i]);
		i++;
	}
	return (thread);
}

int	ini_data(t_data *data, char **argv)
{
	int	num_philos;
	int	i;
	int error;

	data->time_to_die = ft_strtol(argv[2],&error);
	data->time_to_eat = ft_strtol(argv[3],&error);
	data->time_to_sleep = ft_strtol(argv[4],&error);
	data->num_philos = ft_strtol(argv[1],&error);
	data->someone_died = 0;
	data->start_time = get_time_ms();
	num_philos = data->num_philos;
	data->forks = malloc(sizeof(pthread_mutex_t) * num_philos);
	if (!data->forks)
		return (0);
	i = 0;
	while (i < num_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->print_log, NULL);
	if (error == 1)
		return (0);
	return (1);
}

void	*ini_philo(t_philo *philo, t_data *data)
{
	int	i;
	int	num_philo;

	num_philo = data->num_philos;
	philo = malloc(sizeof(t_philo) * data->num_philos);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < num_philo)
	{
		philo[i].id = i + 1;
		philo[i].right_fork = &data->forks[i];
		philo[i].left_fork = &data->forks[(i - 1 + data->num_philos)
			% data->num_philos];
		philo[i].last_meal = 0;
		philo[i].data = data;
		philo[i].times_eaten = 0;
		philo[i].is_eating = 0;
		pthread_mutex_init(&philo[i].last_meal_mutex, NULL);
		i++;
	}
	return (philo);
}
