#include "philo_bonus.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

long long get_timestamp_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

void write_log(int id, const char *msg, t_sim_info *info)
{
    long long timestamp = get_timestamp_ms() - info->start_time;
    sem_wait(info->write_sem);
    printf("%lld %d %s\n", timestamp, id, msg);
    sem_post(info->write_sem);
}
