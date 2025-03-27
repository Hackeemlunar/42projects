/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:06:47 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/27 21:26:01 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	go_sleep(t_philo *philo)
{
	printf("%ld %d is sleeping\n", get_time_in_mil(), philo->id);
	usleep(philo->info->time_to_sleep * 1000);
	philo->action = THINKING;
}
