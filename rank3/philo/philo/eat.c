/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:06:05 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/23 21:06:19 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	go_eat(t_philo *philo)
{
	if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_lock(&philo->info->forks_mutex[philo->left_fork]);
		printf("Philosopher %d has taken a fork\n", philo->id);
		pthread_mutex_lock(&philo->info->forks_mutex[philo->right_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->info->forks_mutex[philo->right_fork]);
		printf("Philosopher %d has taken a fork\n", philo->id);
		pthread_mutex_lock(&philo->info->forks_mutex[philo->left_fork]);
	}
	printf("Philosopher %d has taken a fork\n", philo->id);
	printf("Philosopher %d is eating\n", philo->id);
	usleep(philo->info->time_to_eat);
	pthread_mutex_unlock(&philo->info->forks_mutex[philo->left_fork]);
	pthread_mutex_unlock(&philo->info->forks_mutex[philo->right_fork]);
	philo->times_eaten++;
	philo->action = SLEEPING;
}
