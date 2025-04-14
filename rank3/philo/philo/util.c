/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:01:51 by hmensah-          #+#    #+#             */
/*   Updated: 2025/04/14 15:39:21 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	long	time_since_last_meal;

	pthread_mutex_lock(&philo->info->eat_update_mutex);
	time_since_last_meal = get_time_in_mil() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->info->eat_update_mutex);
	pthread_mutex_lock(&philo->info->stop_mutex);
	if (time_since_last_meal > philo->info->time_to_die)
	{
		philo->info->stop_sim = 1;
		pthread_mutex_unlock(&philo->info->stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->stop_mutex);
	return (0);
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
				rel_time = get_time_in_mil()
					- sim->philos[i]->info->start_time;
				pthread_mutex_lock(&sim->info->print_mutex);
				printf("%13ld %d died\n", rel_time, sim->philos[i]->id);
				pthread_mutex_unlock(&sim->info->print_mutex);
				return (NULL);
			}
		}
	}
	return (NULL);
}

int	start_simulation(t_sim *sim)
{
	int			i;
	t_philo		**philos;
	pthread_t	monitor;

	i = -1;
	philos = sim->philos;
	sim->info->start_time = get_time_in_mil();
	if (sim->info->num_of_philo == 1)
		return (go_await_your_death(sim->philos[0]), 0);
	while (++i < sim->info->num_of_philo)
	{
		sim->philos[i]->last_meal_time = get_time_in_mil();
		if (pthread_create(&philos[i]->thread, NULL, do_philosophy, philos[i]))
			return (printf("Error: Could not create thread\n"), 1);
	}
	if (pthread_create(&monitor, NULL, do_monitor, sim))
		return (printf("Error: Could not create thread\n"), 1);
	if (pthread_join(monitor, NULL))
		return (printf("Error: Could not join thread\n"), 1);
	i = -1;
	while (++i < sim->info->num_of_philo)
		if (pthread_detach(philos[i]->thread))
			return (printf("Error: Could not detach thread\n"), 1);
	return (0);
}
