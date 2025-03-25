/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:06:30 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/23 21:06:35 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	go_think(t_philo *philo)
{
    printf("Philosopher %d is thinking\n", philo->id);
    usleep(philo->info->time_to_die * 1000);
    philo->action = EATING;
}