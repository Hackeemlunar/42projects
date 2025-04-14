/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:06:47 by hmensah-          #+#    #+#             */
/*   Updated: 2025/04/07 21:01:48 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	go_sleep(t_philo *philo)
{
	long	relative_time;

	pthread_mutex_lock(&philo->info->print_mutex);
	relative_time = get_time_in_mil() - philo->info->start_time;
	printf("%13ld %d is sleeping\n", relative_time, philo->id);
	pthread_mutex_unlock(&philo->info->print_mutex);
	philo_usleep(philo->info->time_to_sleep);
	philo->action = THINKING;
}

void	go_think(t_philo *philo)
{
	long	relative_time;

	pthread_mutex_lock(&philo->info->print_mutex);
	relative_time = get_time_in_mil() - philo->info->start_time;
	printf("%13ld %d is thinking\n", relative_time, philo->id);
	pthread_mutex_unlock(&philo->info->print_mutex);
	philo->action = EATING;
}

void	cleanup(t_sim *sim, t_arena *arena)
{
	int	i;
	int	num_philo;

	i = 0;
	num_philo = sim->info->num_of_philo;
	while (i < num_philo)
	{
		pthread_mutex_destroy(&sim->info->forks_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&sim->info->stop_mutex);
	pthread_mutex_destroy(&sim->info->print_mutex);
	arena_destroy(arena);
}

void	philo_usleep(size_t mls)
{
	size_t	start;
	size_t	elapsed;

	start = get_time_in_mil();
	while (1)
	{
		elapsed = get_time_in_mil() - start;
		if (elapsed >= mls)
			break ;
		usleep(500);
	}
}

long	get_time_in_mil(void)
{
	struct timeval	current_time;
	long			seconds;
	long			microseconds;
	long			milliseconds;

	if (gettimeofday(&current_time, NULL) == -1)
	{
		printf("Error: gettimeofday");
		return (1);
	}
	seconds = current_time.tv_sec;
	microseconds = current_time.tv_usec;
	milliseconds = seconds * 1000 + microseconds / 1000;
	return (milliseconds);
}
