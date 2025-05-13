/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:23:00 by hmensah-          #+#    #+#             */
/*   Updated: 2025/05/13 15:15:25 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	write_log(int id, const char *msg, t_sim_info *info)
{
	long long	timestamp;

	timestamp = get_timestamp_ms() - info->start_time;
	sem_wait(info->write_sem);
	printf("% 13lld %d %s\n", timestamp, id, msg);
	sem_post(info->write_sem);
}

long long	get_timestamp_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
