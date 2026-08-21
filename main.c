/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerr <chguerr@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 00:19:50 by chguerr           #+#    #+#             */
/*   Updated: 2026/08/20 00:23:58 by chguerr          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philo;
	pthread_t	dog_watch;
	pthread_t	*threads;

	if (argc <= 4 || argc > 5)
		return (1);
	if (!validate_input(argc, argv))
		return (1);
	philo = NULL;
	if (!ini_data(&data, argv))
		return (1);
	philo = ini_philo(philo, &data);
	if (!philo)
		return (1);
	threads = create_threads(philo, data.num_philos, &dog_watch);
	join_threads(threads, philo, &dog_watch);
	mutexes_destroy(philo, &data);
	free(philo);
	free(data.forks);
	free(threads);
	return (0);
}
