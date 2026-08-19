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
		}
	}
	return NULL;
}

void *routine(void *arg)
{
	t_philo *philo;

	philo = arg;
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if(philo->data->someone_died)
		{
			pthread_mutex_unlock(&philo->data->death_mutex);
			return NULL;
		}
		print_log(philo,"is thinking" );
		take_forks(philo);
		pthread_mutex_lock(&philo->last_meal_mutex);
		philo->last_meal = current_time(philo);
		pthread_mutex_unlock(&philo->last_meal_mutex);
		print_log(philo, "has taken a fork");
		print_log(philo, "is eating");
		usleep(philo->data->time_to_eat * 1000);
		leave_forks(philo);
		print_log(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
	}
	return NULL;
}
