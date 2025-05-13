/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:12:30 by hmensah-          #+#    #+#             */
/*   Updated: 2025/05/13 17:26:20 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	write_death(int id, const char *msg, t_sim_info *info)
{
	long long	timestamp;

	timestamp = get_timestamp_ms() - info->start_time;
	sem_wait(info->write_sem);
	printf("% 13lld %d %s\n", timestamp, id, msg);
}

void	go_await_death(t_sim_info *info)
{
	write_log(1, "has taken a fork", info);
	usleep(info->time_to_die * 1000);
	write_log(1, "died", info);
}

void	*monitor_death(void *arg)
{
	t_death_monitor	*monitor;
	long long		now;

	monitor = (t_death_monitor *)arg;
	while (1)
	{
		pthread_mutex_lock(monitor->mutex);
		if (!(*(monitor->running)))
		{
			pthread_mutex_unlock(monitor->mutex);
			break ;
		}
		now = get_timestamp_ms();
		if (now - *(monitor->last_meal_time) > monitor->info->time_to_die)
		{
			write_death(monitor->id, "died", monitor->info);
			sem_post(monitor->info->death_sem);
			*(monitor->running) = 0;
			pthread_mutex_unlock(monitor->mutex);
			break ;
		}
		pthread_mutex_unlock(monitor->mutex);
		usleep(1000);
	}
	return (NULL);
}

int	run_philosopher(int id, t_sim_info *info)
{
	long long		last_meal_time;
	long long		now;
	int				eat_count;
	int				running;
	pthread_t		monitor_thd;
	t_death_monitor	monitor_data;
	pthread_mutex_t	data_mutex;

	if (pthread_mutex_init(&data_mutex, NULL) != 0)
		return (1);
	last_meal_time = get_timestamp_ms();
	eat_count = 0;
	running = 1;
	info->mutex_ptr = &data_mutex;
	monitor_data.info = info;
	monitor_data.last_meal_time = &last_meal_time;
	monitor_data.id = id;
	monitor_data.running = &running;
	monitor_data.mutex = &data_mutex;
	if (pthread_create(&monitor_thd, NULL, &monitor_death, &monitor_data) != 0)
		return (pthread_mutex_destroy(&data_mutex), 1);
	pthread_detach(monitor_thd);
	while (1)
	{
		pthread_mutex_lock(&data_mutex);
		if (!running)
		{
			pthread_mutex_unlock(&data_mutex);
			break ;
		}
		pthread_mutex_unlock(&data_mutex);
		if (go_eat(info, &last_meal_time, &now, id))
			return (pthread_mutex_destroy(&data_mutex), 1);
		eat_count++;
		if (info->num_eat != -1 && eat_count >= info->num_eat)
			return (pthread_mutex_destroy(&data_mutex), 0);
		do_others(id, info);
	}
	return (pthread_mutex_destroy(&data_mutex), 0);
}
