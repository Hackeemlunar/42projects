/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:06:05 by hmensah-          #+#    #+#             */
/*   Updated: 2025/05/02 18:13:35 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	go_await_your_death(t_philo *philo)
{
	long	rel_time;
	long	current_time;

	go_think(philo);
	current_time = get_time_in_mil();
	rel_time = current_time - philo->info->start_time;
	write_event(philo->info, "has taken a fork", philo);
	philo_usleep(philo->info->time_to_die);
	current_time = get_time_in_mil();
	rel_time = current_time - philo->info->start_time;
	write_event(philo->info, "died", philo);
}

static void	take_left_fork_first(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks_mutex[philo->left_fork]);
	write_event(philo->info, "has taken a fork", philo);
	pthread_mutex_lock(&philo->info->forks_mutex[philo->right_fork]);
	write_event(philo->info, "has taken a fork", philo);
}

static void	take_right_fork_first(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks_mutex[philo->right_fork]);
	write_event(philo->info, "has taken a fork", philo);
	pthread_mutex_lock(&philo->info->forks_mutex[philo->left_fork]);
	write_event(philo->info, "has taken a fork", philo);
}

void	go_eat(t_philo *philo)
{
	long	current_time;

	if (philo->left_fork < philo->right_fork)
		take_left_fork_first(philo);
	else
		take_right_fork_first(philo);
	current_time = get_time_in_mil();
	pthread_mutex_lock(&philo->info->eat_update_mutex);
	philo->last_meal_time = current_time;
	pthread_mutex_unlock(&philo->info->eat_update_mutex);
	write_event(philo->info, "is eating", philo);
	philo_usleep(philo->info->time_to_eat);
	pthread_mutex_unlock(&philo->info->forks_mutex[philo->left_fork]);
	pthread_mutex_unlock(&philo->info->forks_mutex[philo->right_fork]);
	pthread_mutex_lock(&philo->info->eat_update_mutex);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->info->eat_update_mutex);
	philo->action = SLEEPING;
}
