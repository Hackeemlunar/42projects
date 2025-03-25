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
	printf("Philosopher %d is eating\n", philo->id);
	usleep(philo->info->time_to_eat * 1000);
	philo->times_eaten++;
	philo->action = SLEEPING;
}
