/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerre <chguerre@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 12:16:44 by chguerre          #+#    #+#             */
/*   Updated: 2026/08/20 14:43:57 by chguerre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
	/*f (philo->data->num_philos == philo->id)
		{
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(philo->right_fork);
			return ;
		}
	*/
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
}

void	leave_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static int	routine_should_stop(t_philo *philo)
{
	if (should_stop(philo))
	{
		if (philo->is_eating)
			leave_forks(philo);
		return (1);
	}
	return (0);
}

void	routine_eat(t_philo *philo)
{
	take_forks(philo);
	philo->is_eating = 1;
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = current_time(philo);
	pthread_mutex_unlock(&philo->last_meal_mutex);
	if (routine_should_stop(philo))
		return ;
	print_log(philo, "has taken a fork");
	print_log(philo, "is eating");
	usleep(philo->data->time_to_eat * 1000);
	if (routine_should_stop(philo))
		return ;
	leave_forks(philo);
	philo->is_eating = 0;
	philo->times_eaten++;
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (1)
	{
		if (should_stop(philo))
			return (NULL);
		print_log(philo, "is thinking" );
		if (!(philo->data->num_philos == 1))
		{
			routine_eat(philo);
			if (should_stop(philo))
				return (NULL);
		}
		print_log(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
		if (should_stop(philo))
			return (NULL);
	}
	return (NULL);
}
