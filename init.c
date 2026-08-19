#include "philo.h"

void join_threads(pthread_t *threads, t_philo *philo, pthread_t *dog_watch )
{
	int i;

	i = 0;
	pthread_join(*dog_watch, NULL);
	while(i < philo[i].data->num_philos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

void *create_threads(t_philo *philo, int num_philos, pthread_t *dog_watch)
{
	pthread_t	*thread;
	int			i;

	thread = malloc(sizeof(pthread_t) * num_philos);
	if(!thread)
	{
		//creo que tengo que liberar todo data.fork y philos.
		return NULL ;
	}
	pthread_create(dog_watch, NULL,(void *)monitor, philo);	
	i = 0;
	while(i < num_philos)
	{
		pthread_create(&thread[i], NULL, (void *)routine, &philo[i]);
		i++;
	}
	return thread;
}

int	ini_data(t_data *data, char **argv)
{
	int	num_philos;
	int	i;

	data->start_time = get_time_ms();
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	data->num_philos = atoi(argv[1]);
	data->someone_died = 0;
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
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->print_log, NULL);
	return 1;
}


void	*ini_philo(t_philo *philo, t_data *data)
{
	int	i;
	int	num_philo = data->num_philos;

	philo = malloc(sizeof(t_philo) * data->num_philos);
	if (!philo)
		return (NULL);
	i = 0;
	while(i <num_philo)
	{
		philo[i].id = i + 1;
		philo[i].right_fork = &data->forks[i];
		philo[i].left_fork = &data->forks[(i - 1 + data->num_philos) % data->num_philos];
		philo[i].last_meal = 0;
		philo[i].data = data;
		pthread_mutex_init(&philo[i].last_meal_mutex, NULL);
		i++;
	}
	return philo;
}


