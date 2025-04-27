/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:06:05 by hmensah-          #+#    #+#             */
/*   Updated: 2025/04/15 15:37:37 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	go_await_your_death(t_philo *philo)
{
	long	relative_time;
	long	current_time;

	go_think(philo);
	current_time = get_time_in_mil();
	relative_time = current_time - philo->info->start_time;
	pthread_mutex_lock(&philo->info->print_mutex);
	printf("%13ld %d has taken a fork\n", relative_time, philo->id);
	pthread_mutex_unlock(&philo->info->print_mutex);
	philo_usleep(philo->info->time_to_die);
	current_time = get_time_in_mil();
	relative_time = current_time - philo->info->start_time;
	pthread_mutex_lock(&philo->info->print_mutex);
	printf("%13ld %d died\n", relative_time, philo->id);
	pthread_mutex_unlock(&philo->info->print_mutex);
}

void	take_left_fork_first(t_philo *philo)
{
	long	relative_time;

	pthread_mutex_lock(&philo->info->forks_mutex[philo->left_fork]);
	pthread_mutex_lock(&philo->info->print_mutex);
	relative_time = get_time_in_mil() - philo->info->start_time;
	printf("%13ld %d has taken a fork\n", relative_time, philo->id);
	pthread_mutex_unlock(&philo->info->print_mutex);
	pthread_mutex_lock(&philo->info->forks_mutex[philo->right_fork]);
	pthread_mutex_lock(&philo->info->print_mutex);
	relative_time = get_time_in_mil() - philo->info->start_time;
	printf("%13ld %d has taken a fork\n", relative_time, philo->id);
	pthread_mutex_unlock(&philo->info->print_mutex);
}

void	take_right_fork_first(t_philo *philo)
{
	long	relative_time;

	pthread_mutex_lock(&philo->info->forks_mutex[philo->right_fork]);
	pthread_mutex_lock(&philo->info->print_mutex);
	relative_time = get_time_in_mil() - philo->info->start_time;
	printf("%13ld %d has taken a fork\n", relative_time, philo->id);
	pthread_mutex_unlock(&philo->info->print_mutex);
	pthread_mutex_lock(&philo->info->forks_mutex[philo->left_fork]);
	pthread_mutex_lock(&philo->info->print_mutex);
	relative_time = get_time_in_mil() - philo->info->start_time;
	printf("%13ld %d has taken a fork\n", relative_time, philo->id);
	pthread_mutex_unlock(&philo->info->print_mutex);
}

void	go_eat(t_philo *philo)
{
	long	current_time;
	long	relative_time;

	if (philo->left_fork < philo->right_fork)
		take_left_fork_first(philo);
	else
		take_right_fork_first(philo);
	current_time = get_time_in_mil();
	pthread_mutex_lock(&philo->info->eat_update_mutex);
	philo->last_meal_time = current_time;
	pthread_mutex_unlock(&philo->info->eat_update_mutex);
	pthread_mutex_lock(&philo->info->print_mutex);
	relative_time = current_time - philo->info->start_time;
	printf("%13ld %d is eating\n", relative_time, philo->id);
	pthread_mutex_unlock(&philo->info->print_mutex);
	philo_usleep(philo->info->time_to_eat);
	pthread_mutex_unlock(&philo->info->forks_mutex[philo->left_fork]);
	pthread_mutex_unlock(&philo->info->forks_mutex[philo->right_fork]);
	pthread_mutex_lock(&philo->info->eat_update_mutex);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->info->eat_update_mutex);
	philo->action = SLEEPING;
}
