/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:01:51 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/25 18:22:18 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	(void)philo;
	return (0);
}

static void	do_philo_actions(t_philo *philo)
{
	if (philo->action == THINKING)
		go_think(philo);
	if (philo->action == EATING)
		go_eat(philo);
	if (philo->action == SLEEPING)
		go_sleep(philo);
}

void	*do_philosophy(void *philosopher)
{
	t_philo		*philo;

	philo = (t_philo *)philosopher;
	philo->times_eaten = 0;
	philo->elapsed_time = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->info->stop_mutex);
		if (philo->info->stop_sim)
		{
			pthread_mutex_unlock(&philo->info->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->info->stop_mutex);
		if (is_dead(philo) || philo->times_eaten >= philo->info->total_meals)
		{
			pthread_mutex_lock(&philo->info->stop_mutex);
			philo->info->stop_sim = 1;
			pthread_mutex_unlock(&philo->info->stop_mutex);
			break ;
		}
		do_philo_actions(philo);
	}
	return (NULL);
}

void	cleanup(t_sim *sim, t_arena *arena)
{
	int		i;
	int		num_philo;

	i = 0;
	num_philo = sim->num_of_philo;
	while (i < num_philo)
	{
		pthread_mutex_destroy(&sim->info->forks_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&sim->info->stop_mutex);
	arena_destroy(arena);
}
