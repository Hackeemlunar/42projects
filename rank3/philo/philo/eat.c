/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:06:05 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/27 21:39:20 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	go_eat(t_philo *philo)
{
	long	current_time;

	if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_lock(&philo->info->forks_mutex[philo->left_fork]);
		printf("%ld %d has taken a fork\n", get_time_in_mil(), philo->id);
		pthread_mutex_lock(&philo->info->forks_mutex[philo->right_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->info->forks_mutex[philo->right_fork]);
		printf("%ld %d has taken a fork\n", get_time_in_mil(), philo->id);
		pthread_mutex_lock(&philo->info->forks_mutex[philo->left_fork]);
	}
	current_time = get_time_in_mil();
	printf("%ld %d has taken a fork\n", current_time, philo->id);
	printf("%ld %d is eating\n", current_time, philo->id);
	usleep(philo->info->time_to_eat);
	pthread_mutex_unlock(&philo->info->forks_mutex[philo->left_fork]);
	pthread_mutex_unlock(&philo->info->forks_mutex[philo->right_fork]);
	philo->times_eaten++;
	philo->action = SLEEPING;
}
