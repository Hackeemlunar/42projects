/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:12:30 by hmensah-          #+#    #+#             */
/*   Updated: 2025/05/13 15:16:29 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void write_death(int id, const char *msg, t_sim_info *info)
{
	long long timestamp;

	timestamp = get_timestamp_ms() - info->start_time;
	sem_wait(info->write_sem);
	printf("% 13lld %d %s\n", timestamp, id, msg);
}

void go_await_death(t_sim_info *info)
{
	write_log(1, "has taken a fork", info);
	usleep(info->time_to_die * 1000);
	write_log(1, "died", info);
}

int go_eat(t_sim_info *info, long long *last, long long *now, int id)
{
	sem_wait(info->table_sem);
	sem_wait(info->forks_sem);
	write_log(id, "has taken a fork", info);
	sem_wait(info->forks_sem);
	write_log(id, "has taken a fork", info);
	*now = get_timestamp_ms();
	if (*now - *last > info->time_to_die)
	{
		write_death(id, "died", info);
		sem_post(info->death_sem);
		return (1);
	}
	write_log(id, "is eating", info);
	*last = get_timestamp_ms();
	usleep(info->time_to_eat * 1000);
	sem_post(info->forks_sem);
	sem_post(info->forks_sem);
	sem_post(info->table_sem);
	return (0);
}

void do_others(int id, t_sim_info *info)
{
	write_log(id, "is sleeping", info);
	usleep(info->time_to_sleep * 1000);
	write_log(id, "is thinking", info);
	usleep(1000);
}

int run_philosopher(int id, t_sim_info *info)
{
	long long last_meal_time;
	long long now;
	int eat_count;

	last_meal_time = info->start_time;
	eat_count = 0;
	while (1)
	{
		now = get_timestamp_ms();
		if (now - last_meal_time > info->time_to_die)
		{
			write_death(id, "died", info);
			sem_post(info->death_sem);
			return (1);
		}
		if (go_eat(info, &last_meal_time, &now, id))
			return (1);
		else
			eat_count++;
		if (info->num_eat != -1 && eat_count >= info->num_eat)
			return (0);
		do_others(id, info);
	}
	return (0);
}
