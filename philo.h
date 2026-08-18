/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.json                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerr <chguerr@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 14:52:33 by chguerr           #+#    #+#             */
/*   Updated: 2026/08/18 15:15:49 by chguerr          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_data
{
	int				num_philos;
	int				num_times_to_eats;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_log;
}	t_data;

typedef struct s_philo
{
	int				id;
	unsigned long	last_meal;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_data *data;
}	t_philo;

int	*ini_data(t_data *data, char **argv);
int	*ini_philo(t_philo *philo, t_data *data);
#endif