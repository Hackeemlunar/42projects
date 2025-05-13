/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:23:00 by hmensah-          #+#    #+#             */
/*   Updated: 2025/05/13 16:52:16 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	write_log(int id, const char *msg, t_sim_info *info)
{
	long long	timestamp;

	timestamp = get_timestamp_ms() - info->start_time;
	sem_wait(info->write_sem);
	printf("% 13lld %d %s\n", timestamp, id, msg);
	sem_post(info->write_sem);
}

long long	get_timestamp_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	go_eat(t_sim_info *info, long long *last, long long *now, int id)
{
	pthread_mutex_t	*mutex;

	sem_wait(info->table_sem);
	sem_wait(info->forks_sem);
	write_log(id, "has taken a fork", info);
	sem_wait(info->forks_sem);
	write_log(id, "has taken a fork", info);
	mutex = (pthread_mutex_t *)info->mutex_ptr;
	pthread_mutex_lock(mutex);
	*now = get_timestamp_ms();
	if (*now - *last > info->time_to_die)
	{
		pthread_mutex_unlock(mutex);
		write_death(id, "died", info);
		sem_post(info->death_sem);
		return (1);
	}
	write_log(id, "is eating", info);
	*last = get_timestamp_ms();
	pthread_mutex_unlock(mutex);
	usleep(info->time_to_eat * 1000);
	sem_post(info->forks_sem);
	sem_post(info->forks_sem);
	sem_post(info->table_sem);
	return (0);
}

void	do_others(int id, t_sim_info *info)
{
	write_log(id, "is sleeping", info);
	usleep(info->time_to_sleep * 1000);
	write_log(id, "is thinking", info);
	usleep(1000);
}
