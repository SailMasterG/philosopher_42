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

void	*monitor(void *arg)
{
	t_philo *philo;
	int i;

	philo = arg;
	while(1)
	{
		i = 0;
		while(i < philo->data->num_philos)
		{	pthread_mutex_lock(&philo->last_meal_mutex);
			if(current_time(&philo[i]) - philo[i].last_meal > philo->data->time_to_die)
			{	
			pthread_mutex_unlock(&philo->last_meal_mutex);
			print_log(&philo[i],"Has die!!...");
			break;
		}
		i++;
		}
	}
	//Limpieza de todo.
	return NULL;
}

void *routine(void *arg)
{
	t_philo *philo;

	philo = arg;
	while (1)
	{
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
