/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:06:47 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/29 22:04:04 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	go_sleep(t_philo *philo)
{
	long	relative_time;

	pthread_mutex_lock(&philo->info->print_mutex);
	relative_time = get_time_in_mil() - philo->info->start_time;
	printf("%013ld %d is sleeping\n", relative_time, philo->id);
	pthread_mutex_unlock(&philo->info->print_mutex);
	usleep(philo->info->time_to_sleep * 1000);
	philo->action = THINKING;
}

void	go_think(t_philo *philo)
{
	long	relative_time;

	pthread_mutex_lock(&philo->info->print_mutex);
	relative_time = get_time_in_mil() - philo->info->start_time;
	printf("%013ld %d is thinking\n", relative_time, philo->id);
	pthread_mutex_unlock(&philo->info->print_mutex);
	usleep(1000);
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

void	*do_monitor(void *simulation)
{
	int		i;
	long	rel_time;
	t_sim	*sim;

	sim = (t_sim *)simulation;
	while (1)
	{
		i = -1;
		while (++i < sim->info->num_of_philo)
		{
			if (is_dead(sim->philos[i]))
			{
				if ((!sim->philos[i]->job_done))
				{
					rel_time = get_time_in_mil() - sim->philos[i]->info->start_time;
					pthread_mutex_lock(&sim->info->print_mutex);
					printf("%013ld %d died\n", rel_time, sim->philos[i]->id);
					pthread_mutex_unlock(&sim->info->print_mutex);
				}
				return (NULL);
			}
		}
		usleep(1000);
	}
	return (NULL);
}

int	wait_monitor(t_sim *sim)
{
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, do_monitor, sim))
		return (printf("Error: Could not create thread\n"), 1);
	if (pthread_join(monitor, NULL))
		return (printf("Error: Could not join thread\n"), 1);
	return (0);
}
