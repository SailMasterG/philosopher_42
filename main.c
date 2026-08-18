/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerr <chguerr@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 15:25:20 by chguerr           #+#    #+#             */
/*   Updated: 2026/08/18 15:25:55 by chguerr          ###   ########.ch       */
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
	while (i < data.num_philos)
	{
		pthread_mutex_destroy(&data.forks[i]);
		i++;
	}
	return (0);
}
