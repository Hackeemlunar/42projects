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
	// Intentionally not calling sem_post to block other output after death
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
	
	// Use mutex to protect shared data
	pthread_mutex_t *mutex = (pthread_mutex_t *)info->mutex_ptr;
	
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

void do_others(int id, t_sim_info *info)
{
	write_log(id, "is sleeping", info);
	usleep(info->time_to_sleep * 1000);
	write_log(id, "is thinking", info);
	usleep(1000);
}

void *monitor_death(void *arg)
{
	t_death_monitor *monitor;
	long long now;
	
	monitor = (t_death_monitor *)arg;
	while (1)
	{
		pthread_mutex_lock(monitor->mutex);
		if (!(*(monitor->running)))
		{
			pthread_mutex_unlock(monitor->mutex);
			break;
		}
		now = get_timestamp_ms();
		if (now - *(monitor->last_meal_time) > monitor->info->time_to_die)
		{
			write_death(monitor->id, "died", monitor->info);
			sem_post(monitor->info->death_sem);
			*(monitor->running) = 0;
			pthread_mutex_unlock(monitor->mutex);
			break;
		}
		pthread_mutex_unlock(monitor->mutex);
		// Check every 1ms for death
		usleep(1000);
	}
	return (NULL);
}

int run_philosopher(int id, t_sim_info *info)
{
	long long last_meal_time;
	long long now;
	int eat_count;
	pthread_t monitor_thread;
	t_death_monitor monitor_data;
	int running;
	pthread_mutex_t data_mutex;

	if (pthread_mutex_init(&data_mutex, NULL) != 0)
		return (1);
	last_meal_time = get_timestamp_ms(); // Initialize with current time, not start_time
	eat_count = 0;
	running = 1;
	
	// Set the mutex pointer in info for go_eat to use
	info->mutex_ptr = &data_mutex;
	
	// Set up death monitoring thread
	monitor_data.info = info;
	monitor_data.last_meal_time = &last_meal_time;
	monitor_data.id = id;
	monitor_data.running = &running;
	monitor_data.mutex = &data_mutex;
	
	// Create a thread to continuously check for death
	if (pthread_create(&monitor_thread, NULL, &monitor_death, &monitor_data) != 0)
	{
		pthread_mutex_destroy(&data_mutex);
		return (1);
	}
	pthread_detach(monitor_thread);
	
	while (1)
	{
		pthread_mutex_lock(&data_mutex);
		if (!running)
		{
			pthread_mutex_unlock(&data_mutex);
			break;
		}
		pthread_mutex_unlock(&data_mutex);
		
		if (go_eat(info, &last_meal_time, &now, id))
		{
			pthread_mutex_destroy(&data_mutex);
			return (1);
		}
		eat_count++;
		if (info->num_eat != -1 && eat_count >= info->num_eat)
		{
			pthread_mutex_destroy(&data_mutex);
			return (0);
		}
		do_others(id, info);
	}
	pthread_mutex_destroy(&data_mutex);
	return (0);
}
