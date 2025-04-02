/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:01:51 by hmensah-          #+#    #+#             */
/*   Updated: 2025/04/02 19:53:47 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	is_dead(t_philo *philo)
{
	long	time_since_last_meal;

	pthread_mutex_lock(&philo->info->stop_mutex);
	time_since_last_meal = get_time_in_mil() - philo->last_meal_time;
	if (time_since_last_meal > philo->info->time_to_die)
	{
		philo->info->stop_sim = 1;
		pthread_mutex_unlock(&philo->info->stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->stop_mutex);
	return (0);
}

void	*do_philosophy(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	philo->times_eaten = 0;
	if (philo->info->num_of_philo == 1)
		return (go_await_your_death(philo), NULL);
	while (1)
	{
		if ((philo->times_eaten >= philo->info->total_meals
				&& philo->info->total_meals != -1))
		{
			philo->job_done = 1;
			break ;
		}
		if (philo->action == THINKING)
			go_think(philo);
		else if (philo->action == EATING)
			go_eat(philo);
		else if (philo->action == SLEEPING)
			go_sleep(philo);
	}
	return (NULL);
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
				if (!(sim->philos[i]->job_done))
				{
					rel_time = get_time_in_mil()
						- sim->philos[i]->info->start_time;
					pthread_mutex_lock(&sim->info->print_mutex);
					printf("%13ld %d died\n", rel_time, sim->philos[i]->id);
					pthread_mutex_unlock(&sim->info->print_mutex);
				}
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
