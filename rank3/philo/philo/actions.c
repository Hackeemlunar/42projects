/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:23:27 by hmensah-          #+#    #+#             */
/*   Updated: 2025/05/02 18:17:46 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*do_philosophy(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	pthread_mutex_lock(&philo->info->eat_update_mutex);
	philo->times_eaten = 0;
	pthread_mutex_unlock(&philo->info->eat_update_mutex);
	if (philo->info->num_of_philo == 1)
		return (go_await_your_death(philo), NULL);
	while (1)
	{
		if (philo->action == THINKING)
			go_think(philo);
		else if (philo->action == EATING)
			go_eat(philo);
		else
			go_sleep(philo);
		pthread_mutex_lock(&philo->info->stop_mutex);
		if (philo->info->stop_sim)
		{
			pthread_mutex_unlock(&philo->info->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->info->stop_mutex);
	}
	return (NULL);
}

inline void	go_sleep(t_philo *philo)
{
	write_event(philo->info, "is sleeping", philo);
	philo_usleep(philo->info->time_to_sleep);
	philo->action = THINKING;
}

inline void	go_think(t_philo *philo)
{
	write_event(philo->info, "is thinking", philo);
	philo->action = EATING;
	philo_usleep(1);
}
