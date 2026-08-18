#include "philo.h"


int	*ini_data(t_data *data, char **argv)
{
	int	num_philos;
	int	i;

	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	data->num_philos = atoi(argv[1]);
	num_philos = data->num_philos;
	data->forks = malloc(sizeof(pthread_mutex_t) * num_philos);
	if(!data->forks)
		return 0;
	i = 0;
	while (i < num_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print_log, NULL);
	return 1;
}


int	*ini_philo(t_philo *philo, t_data *data)
{
	int	i;
	int	num_philo = data->num_philos;

	philo = malloc(sizeof(t_philo) * data->num_philos);
	if (!philo)
	{
		free(philo);
		return (0);
	}
	i = 0;
	while(i <num_philo)
	{
		philo->id = i + 1;
		philo->right_fork = &data->forks[i];
		philo->left_fork = &data->forks[(i - 1 + data->num_philos) % data->num_philos];
		philo->last_meal = 0;
		i++;
	}
	return 1;
}
