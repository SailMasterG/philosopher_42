/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerr <chguerr@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 20:53:07 by chguerr           #+#    #+#             */
/*   Updated: 2026/08/19 20:53:40 by chguerr          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;
	int		i;
	
	if (argc < 4 || argc > 5)
		return (1);
	i = 0;
	philo = NULL;
	if(!ini_data(&data, argv))
		return (1);
	philo = ini_philo(philo, &data);
	if(!philo)
		return 1;
	create_threads(philo, data.num_philos);
	pthread_t dog_watch;
	pthread_create(&dog_watch, NULL,(void *)monitor, philo);
	pthread_join(dog_watch, NULL);
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
