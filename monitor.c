/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 01:24:28 by chguerr           #+#    #+#             */
/*   Updated: 2026/08/22 15:34:10 by chguerre         ###   ########.fr       */
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
		print_log(philo, "died");
		pthread_mutex_unlock(&philo->last_meal_mutex);
		pthread_mutex_lock(&philo->data->death_mutex);
		philo->data->someone_died = 1;
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->last_meal_mutex);
	return (0);
}

int	all_ate_enough(t_philo *philo)
{
	int	i;
	int	eat_enough;

	i = 0;
	eat_enough = 0;
	while (i < philo->data->num_philos)
	{
		if (philo[i].times_eaten >= philo[i].data->num_times_to_eats)
			eat_enough++;
		i++;
	}
	if (eat_enough == philo->data->num_philos)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		philo->data->someone_died = 1;
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
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
		ft_usleep(1, philo);
		i = 0;
		if (philo->data->num_times_to_eats > 0 && all_ate_enough(philo))
		{
			break ;
		}
		while (i < philo->data->num_philos)
		{
			one_die = is_dead(&philo[i]);
			if (one_die)
				break ;
			i++;
		}
		if (one_die)
			break ;
	}
	return (NULL);
}
