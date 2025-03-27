/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:06:30 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/27 21:26:26 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	go_think(t_philo *philo)
{
	printf("%ld %d is thinking\n", get_time_in_mil(), philo->id);
	usleep(philo->info->time_to_die * 1000);
	philo->action = EATING;
}
