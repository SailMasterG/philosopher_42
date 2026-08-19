/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerr <chguerr@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 23:50:52 by chguerr           #+#    #+#             */
/*   Updated: 2026/08/19 23:50:57 by chguerr          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int				num_philos;
	int				num_times_to_eats;
	unsigned long	start_time;
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
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_data *data;
}	t_philo;

int				ini_data(t_data *data, char **argv);
void			*ini_philo(t_philo *philo, t_data *data);
void			*create_threads(t_philo *philo, int num_philos, pthread_t *dog_watch);
void			join_threads(pthread_t *threads, t_philo *philo, pthread_t *dog_watch );
void			mutexes_destroy(t_philo *philo, t_data *data);
void			*routine(void *arg);
void			*monitor(void *arg);
unsigned long	get_time_ms(void);
unsigned long	current_time(t_philo *philo);
void			print_log(t_philo *philo, char *message);

#endif