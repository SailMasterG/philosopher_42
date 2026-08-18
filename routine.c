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
		pthread_mutex_lock(&philo->data->print_log);
		printf("%lu %d is thinking\n", current_time(philo), philo->id);
		pthread_mutex_unlock(&philo->data->print_log);
		take_forks(philo);
		pthread_mutex_lock(&philo->data->print_log);
		printf("%lu %d has taken a fork\n", current_time(philo), philo->id);
		pthread_mutex_unlock(&philo->data->print_log);
		pthread_mutex_lock(&philo->data->print_log);
		printf("%lu %d is eating\n",current_time(philo), philo->id);
		pthread_mutex_unlock(&philo->data->print_log);
		usleep(philo->data->time_to_eat * 1000);
		leave_forks(philo);
		pthread_mutex_lock(&philo->data->print_log);
		printf("%lu %d is sleeping\n",current_time(philo), philo->id);
		pthread_mutex_unlock(&philo->data->print_log);
		usleep(philo->data->time_to_sleep * 1000);
	}
	return NULL;
}
