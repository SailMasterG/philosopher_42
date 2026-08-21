/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chguerr <chguerr@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 00:34:40 by chguerr           #+#    #+#             */
/*   Updated: 2026/08/20 00:35:07 by chguerr          ###   ########.ch       */
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
	int				someone_died;
	unsigned long	start_time;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_log;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				times_eaten;
	int				is_eating;
	unsigned long	last_meal;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_data			*data;
}					t_philo;

int					ini_data(t_data *data, char **argv);
int					should_stop(t_philo *philo);
void				*ini_philo(t_philo *philo, t_data *data);
void				*create_threads(t_philo *philo, int num_philos,
						pthread_t *dog_watch);
void				join_threads(pthread_t *threads, t_philo *philo,
						pthread_t *dog_watch );
void				ft_usleep(unsigned long long time_in_ms, t_philo *philo);
void				mutexes_destroy(t_philo *philo, t_data *data);
void				*routine(void *arg);
void				*monitor(void *arg);
unsigned long long	get_time_ms(void);
unsigned long long	current_time(t_philo *philo);
void				print_log(t_philo *philo, char *message);

#endif
