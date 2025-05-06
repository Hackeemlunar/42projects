/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:01:51 by hmensah-          #+#    #+#             */
/*   Updated: 2025/05/02 18:16:33 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_event(t_sim_info *info, char *msg, t_philo *philo)
{
	long	rel_time;

	pthread_mutex_lock(&info->stop_mutex);
	if (!info->stop_sim)
	{
		pthread_mutex_unlock(&info->stop_mutex);
		pthread_mutex_lock(&info->print_mutex);
		rel_time = get_time_in_mil() - info->start_time;
		printf("%13ld %d %s\n", rel_time, philo->id, msg);
		pthread_mutex_unlock(&info->print_mutex);
		return ;
	}
	pthread_mutex_unlock(&info->stop_mutex);
}

int	is_dead(t_sim *sim, t_philo *philo)
{
	long	time_since_last_meal;

	pthread_mutex_lock(&sim->info->eat_update_mutex);
	time_since_last_meal = get_time_in_mil() - philo->last_meal_time;
	pthread_mutex_unlock(&sim->info->eat_update_mutex);
	pthread_mutex_lock(&sim->info->stop_mutex);
	if (time_since_last_meal > sim->info->time_to_die)
	{
		sim->info->stop_sim = 1;
		pthread_mutex_unlock(&sim->info->stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(&sim->info->stop_mutex);
	return (0);
}

static int	check_philos(t_sim *sim, int *all_done)
{
	int		i;
	long	rel_time;

	i = 0;
	while (i < sim->info->num_of_philo)
	{
		if (is_dead(sim, sim->philos[i]))
		{
			rel_time = get_time_in_mil() - sim->info->start_time;
			pthread_mutex_lock(&sim->info->print_mutex);
			printf("%13ld %d died\n", rel_time, sim->philos[i]->id);
			pthread_mutex_unlock(&sim->info->print_mutex);
			return (1);
		}
		if (sim->info->total_meals != -1)
		{
			pthread_mutex_lock(&sim->info->eat_update_mutex);
			if (sim->philos[i]->times_eaten < sim->info->total_meals)
				*all_done = 0;
			pthread_mutex_unlock(&sim->info->eat_update_mutex);
		}
		i++;
	}
	return (0);
}

void	*do_monitor(void *simulation)
{
	t_sim	*sim;
	int		all_done;

	sim = (t_sim *)simulation;
	while (1)
	{
		all_done = 1;
		if (check_philos(sim, &all_done))
			return (NULL);
		if (sim->info->total_meals != -1 && all_done)
		{
			pthread_mutex_lock(&sim->info->stop_mutex);
			sim->info->stop_sim = 1;
			pthread_mutex_unlock(&sim->info->stop_mutex);
			return (NULL);
		}
		usleep(1000);
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
		if (pthread_join(philos[i]->thread, NULL))
			return (printf("Error: Could not join thread\n"), 1);
	return (0);
}
