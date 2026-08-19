/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerr <chguerr@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 00:33:41 by chguerr           #+#    #+#             */
/*   Updated: 2026/08/20 00:34:14 by chguerr          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int should_stop(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->death_mutex);
		if(philo->data->someone_died)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			return 1;
		}
    return (0);
}

static int is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mutex);
	if(current_time(philo) - philo->last_meal > philo->data->time_to_die)
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
	t_philo *philo;
	int i;
	int one_die;

	philo = arg;
	while(1)
	{
		i = 0;
		while(i < philo->data->num_philos)
		{	
			one_die = is_dead(&philo[i]);
			if(one_die)
				break;
			i++;
		}
		if (one_die)
		{
			pthread_mutex_lock(&philo->data->death_mutex);
			philo->data->someone_died = 1;
			pthread_mutex_unlock(&philo->data->death_mutex);
			break;
		}
	}
	return NULL;
}