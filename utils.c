#include "philo.h"

unsigned long current_time(t_philo *philo)
{
    unsigned long c_time;
    c_time = (get_time_ms() - philo->data->start_time);
    return c_time;
}

unsigned long get_time_ms(void)
{
    struct timeval tv;
    unsigned long get_time;
    
    gettimeofday(&tv, NULL );
    get_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    return(get_time);
}