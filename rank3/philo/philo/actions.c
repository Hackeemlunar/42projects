/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:23:27 by hmensah-          #+#    #+#             */
/*   Updated: 2025/04/14 14:31:17 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	do_philo_action(t_philo *philo)
{
	if (philo->action == THINKING)
		go_think(philo);
	else if (philo->action == EATING)
		go_eat(philo);
	else if (philo->action == SLEEPING)
		go_sleep(philo);
}

static void    set_job_done(t_philo *philo)
{
    pthread_mutex_lock(&philo->info->done_mutex);
    philo->job_done = 1;
    pthread_mutex_unlock(&philo->info->done_mutex);
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
			set_job_done(philo);
			break ;
		}
		pthread_mutex_lock(&philo->info->stop_mutex);
		if (philo->info->stop_sim)
		{
			pthread_mutex_unlock(&philo->info->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->info->stop_mutex);
		do_philo_action(philo);
	}
	return (NULL);
}
