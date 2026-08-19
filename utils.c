#include "philo.h"

unsigned long	current_time(t_philo *philo)
{
	unsigned long c_time;
	c_time = (get_time_ms() - philo->data->start_time);
	return c_time;
}

unsigned long	get_time_ms(void)
{
	struct timeval tv;
	unsigned long get_time;
	
	gettimeofday(&tv, NULL );
	get_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return(get_time);
}

void mutexes_destroy(t_philo *philo, t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&philo[i].last_meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->print_log);
}
void	print_log(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->data->print_log);
	printf("%lu %d %s\n", current_time(philo), philo->id, message);
	pthread_mutex_unlock(&philo->data->print_log);
}