/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerr <chguerr@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 23:34:01 by chguerr           #+#    #+#             */
/*   Updated: 2026/08/19 23:34:12 by chguerr          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philo;
	pthread_t	dog_watch;
	pthread_t	*threads;

	int			i;
	
	if (argc < 4 || argc > 5)
		return (1);
	i = 0;
	philo = NULL;
	dog_watch = NULL;
	if(!ini_data(&data, argv))
		return (1);
	philo = ini_philo(philo, &data);
	if(!philo)
		return 1;
	threads = create_threads(philo, data.num_philos, dog_watch);
	join_threads(&threads, philo, &dog_watch);
	while (i < data.num_philos)
	{
		pthread_mutex_destroy(&data.forks[i]);
		pthread_mutex_destroy(&philo[i].last_meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&data.print_log);
	free(philo);
	return (0);
}
