#include "philo.h"

void take_forks(t_philo *philo)
{
	if(philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
}
void leave_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void *routine(void *arg)
{
	t_philo *philo;

	philo = arg;
	while (1)
	{
		if(should_stop(philo))
			return NULL;
		print_log(philo,"is thinking" );
		take_forks(philo);
		pthread_mutex_lock(&philo->last_meal_mutex);
		philo->last_meal = current_time(philo);
		pthread_mutex_unlock(&philo->last_meal_mutex);
		print_log(philo, "has taken a fork");
		print_log(philo, "is eating");
		usleep(philo->data->time_to_eat * 1000);
		if(should_stop(philo))
			return NULL;
		leave_forks(philo);
		print_log(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
		if(should_stop(philo))
			return NULL;
	}
	return NULL;
}
