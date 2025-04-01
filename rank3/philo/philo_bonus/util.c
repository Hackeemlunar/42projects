/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:01:51 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/29 22:08:04 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static void	do_philo_actions(t_philo *philo)
{
	if (philo->action == THINKING)
		go_think(philo);
	else if (philo->action == EATING)
	{
		go_eat(philo);
		philo->times_eaten++;
	}
	else if (philo->action == SLEEPING)
		go_sleep(philo);
}

void	*do_philosophy(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	philo->times_eaten = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->info->stop_mutex);
		if (philo->info->stop_sim || (philo->times_eaten
			>= philo->info->total_meals && philo->info->total_meals != -1))
		{
			pthread_mutex_unlock(&philo->info->stop_mutex);
			philo->job_done = 1;
			break ;
		}
		pthread_mutex_unlock(&philo->info->stop_mutex);
		do_philo_actions(philo);
	}
	return (NULL);
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

int	start_simulation(t_sim *sim)
{
	int		i;
	int		num_philo;
	t_philo	**philos;

	i = 0;
	num_philo = sim->info->num_of_philo;
	philos = sim->philos;
	sim->info->start_time = get_time_in_mil();
	while (i < num_philo)
	{
		sim->philos[i]->last_meal_time = sim->info->start_time;
		if (pthread_create(&philos[i]->thread, NULL, do_philosophy, philos[i]))
			return (printf("Error: Could not create thread\n"), 1);
		i++;
	}
	i = 0;
	while (i < num_philo)
	{
		if (pthread_detach(philos[i]->thread))
			return (printf("Error: Could not detach thread\n"), 1);
		i++;
	}
	wait_monitor(sim);
	return (0);
}
