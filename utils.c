#include "philo.h"

unsigned long get_time_ms()
{
    struct timeval tv;
    unsigned long get_time;
    
    gettimeofday(&tv, NULL );
    get_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    return(get_time);
}