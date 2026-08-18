#include "philo.h"

void take_forks(t_philo *philo)
{
    if(philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(philo->right_fork);
    }
    else
    {
        pthread_mutex_lock(philo->right_fork);
        pthread_mutex_lock(philo->left_fork);
    }
}
void leave_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}

void *routine(void *arg)
{
    t_philo *philo;

    philo = arg;
    while (1)
    {
        take_forks(philo);
        printf("Hola soy el philosofo id: %d\n", philo->id);
        leave_forks(philo);
        break;
    }
    return NULL;
}