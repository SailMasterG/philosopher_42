/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerr <chguerr@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 19:36:56 by chguerr           #+#    #+#             */
/*   Updated: 2026/08/18 19:37:16 by chguerr          ###   ########.ch       */
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
	while (i < data.num_philos)
	{
		pthread_mutex_destroy(&data.forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data.print_log);
	return (0);
}
