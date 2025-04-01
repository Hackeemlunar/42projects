/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:06:05 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/29 22:04:13 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	go_await_your_death(t_philo *philo)
{
	long	relative_time;
	long	current_time;

	current_time = get_time_in_mil();
	relative_time = current_time - philo->info->start_time;
	printf("%013ld %d has taken a fork\n", relative_time, philo->id);
	usleep((unsigned)(philo->info->time_to_die - relative_time) * 1000);
	current_time = get_time_in_mil();
	relative_time = current_time - philo->info->start_time;
	printf("%013ld %d died\n", relative_time, philo->id);
	philo->info->stop_sim = 1;
}

void	take_left_fork_first(t_philo *philo)
{
	long	relative_time;

	pthread_mutex_lock(&philo->info->forks_mutex[philo->left_fork]);
	pthread_mutex_lock(&philo->info->print_mutex);
	relative_time = get_time_in_mil() - philo->info->start_time;
	printf("%013ld %d has taken a fork\n", relative_time, philo->id);
	pthread_mutex_unlock(&philo->info->print_mutex);
	pthread_mutex_lock(&philo->info->forks_mutex[philo->right_fork]);
	pthread_mutex_lock(&philo->info->print_mutex);
	relative_time = get_time_in_mil() - philo->info->start_time;
	printf("%013ld %d has taken a fork\n", relative_time, philo->id);
	pthread_mutex_unlock(&philo->info->print_mutex);
}

void	take_right_fork_first(t_philo *philo)
{
	long	relative_time;

	pthread_mutex_lock(&philo->info->forks_mutex[philo->right_fork]);
	pthread_mutex_lock(&philo->info->print_mutex);
	relative_time = get_time_in_mil() - philo->info->start_time;
	printf("%013ld %d has taken a fork\n", relative_time, philo->id);
	pthread_mutex_unlock(&philo->info->print_mutex);
	pthread_mutex_lock(&philo->info->forks_mutex[philo->left_fork]);
	pthread_mutex_lock(&philo->info->print_mutex);
	relative_time = get_time_in_mil() - philo->info->start_time;
	printf("%013ld %d has taken a fork\n", relative_time, philo->id);
	pthread_mutex_unlock(&philo->info->print_mutex);
}

void	go_eat(t_philo *philo)
{
	long	current_time;
	long	relative_time;

	if (philo->info->num_of_philo == 1)
		return (go_await_your_death(philo));
	if (philo->left_fork < philo->right_fork)
		take_left_fork_first(philo);
	else
		take_right_fork_first(philo);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(&philo->info->forks_mutex[philo->left_fork]);
		pthread_mutex_unlock(&philo->info->forks_mutex[philo->right_fork]);
		return ;
	}
	current_time = get_time_in_mil();
	philo->last_meal_time = current_time;
	pthread_mutex_lock(&philo->info->print_mutex);
	relative_time = current_time - philo->info->start_time;
	printf("%013ld %d is eating\n", relative_time, philo->id);
	pthread_mutex_unlock(&philo->info->print_mutex);
	usleep(philo->info->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->info->forks_mutex[philo->left_fork]);
	pthread_mutex_unlock(&philo->info->forks_mutex[philo->right_fork]);
	philo->action = SLEEPING;
}
