/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 01:24:28 by chguerr           #+#    #+#             */
/*   Updated: 2026/08/20 15:33:52 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	should_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->someone_died)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (0);
}

static int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mutex);
	if (current_time(philo) - philo->last_meal > philo->data->time_to_die)
	{
		print_log(philo,"Has die!!...");
		pthread_mutex_unlock(&philo->last_meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (0);
}

void	*monitor(void *arg)
{
	t_philo	*philo;
	int		i;
	int		one_die;

	philo = arg;
	while (1)
	{
		ft_usleep(10, philo);
		i = 0;
		while (i < philo->data->num_philos)
		{
			one_die = is_dead(&philo[i]);
			if (one_die)
				break ;
			i++;
		}
		if (one_die)
		{
			pthread_mutex_lock(&philo->data->death_mutex);
			philo->data->someone_died = 1;
			pthread_mutex_unlock(&philo->data->death_mutex);
			break ;
		}
	}
	return (NULL);
}
