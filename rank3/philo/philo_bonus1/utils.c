/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:12:30 by hmensah-          #+#    #+#             */
/*   Updated: 2025/05/06 17:31:34 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

long long	get_timestamp_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	write_log(int id, const char *msg, t_sim_info *info)
{
	long long	timestamp;

	timestamp = get_timestamp_ms() - info->start_time;
	sem_wait(info->write_sem);
	printf("% 13lld %d %s\n", timestamp, id, msg);
	sem_post(info->write_sem);
}

void	go_await_death(t_sim_info *info)
{
	write_log(1, "has taken a fork", info);
	usleep(info->time_to_die * 1000);
	write_log(1, "died", info);
}

int	run_philosopher(int id, t_sim_info *info)
{
	long long	last_meal_time;
	long long	now;
	long long	remaining;
	int			eat_count;

	last_meal_time = info->start_time;
	eat_count = 0;
	while (1)
	{
		now = get_timestamp_ms();
		if (now - last_meal_time > info->time_to_die)
		{
			write_log(id, "died", info);
			sem_post(info->death_sem);
			return (1);
		}
		sem_wait(info->table_sem);
		sem_wait(info->forks_sem);
		write_log(id, "has taken a fork", info);
		sem_wait(info->forks_sem);
		write_log(id, "has taken a fork", info);
		now = get_timestamp_ms();
		if (now - last_meal_time > info->time_to_die)
		{
			write_log(id, "died", info);
			sem_post(info->death_sem);
			return (1);
		}
		write_log(id, "is eating", info);
		last_meal_time = get_timestamp_ms();
		eat_count++;
		usleep(info->time_to_eat * 1000);
		sem_post(info->forks_sem);
		sem_post(info->forks_sem);
		sem_post(info->table_sem);
		if (info->num_eat != -1 && eat_count >= info->num_eat)
			return (0);
		write_log(id, "is sleeping", info);
		remaining = info->time_to_sleep;
		usleep(info->time_to_sleep * 1000);
		write_log(id, "is thinking", info);
		usleep(1000);
	}
	return (0);
}
