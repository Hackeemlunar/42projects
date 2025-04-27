/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:06:47 by hmensah-          #+#    #+#             */
/*   Updated: 2025/04/15 15:37:09 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *s)
{
	long	res;
	int		sign;
	int		i;

	res = 0;
	sign = 1;
	i = 0;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-')
		sign = -1;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + (s[i] - '0');
		i++;
	}
	return (sign * res);
}

void	go_sleep(t_philo *philo)
{
	long	relative_time;

	pthread_mutex_lock(&philo->info->print_mutex);
	relative_time = get_time_in_mil() - philo->info->start_time;
	printf("%13ld %d is sleeping\n", relative_time, philo->id);
	pthread_mutex_unlock(&philo->info->print_mutex);
	philo_usleep(philo->info->time_to_sleep);
	philo->action = THINKING;
}

void	go_think(t_philo *philo)
{
	long	relative_time;

	pthread_mutex_lock(&philo->info->print_mutex);
	relative_time = get_time_in_mil() - philo->info->start_time;
	printf("%13ld %d is thinking\n", relative_time, philo->id);
	pthread_mutex_unlock(&philo->info->print_mutex);
	philo->action = EATING;
	philo_usleep(1);
}

void	cleanup(t_sim *sim)
{
	int	i;
	int	num_philo;

	i = 0;
	num_philo = sim->info->num_of_philo;
	while (i < num_philo)
	{
		pthread_mutex_destroy(&sim->info->forks_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&sim->info->stop_mutex);
	pthread_mutex_destroy(&sim->info->print_mutex);
	pthread_mutex_destroy(&sim->info->eat_update_mutex);
	i = 0;
	while (i < num_philo)
	{
		free(sim->philos[i]);
		i++;
	}
	free(sim->philos);
	free(sim->info->forks_mutex);
	free(sim->info);
	free(sim);
}

long	get_time_in_mil(void)
{
	struct timeval	current_time;
	long			seconds;
	long			microseconds;
	long			milliseconds;

	if (gettimeofday(&current_time, NULL) == -1)
	{
		printf("Error: gettimeofday");
		return (1);
	}
	seconds = current_time.tv_sec;
	microseconds = current_time.tv_usec;
	milliseconds = seconds * 1000 + microseconds / 1000;
	return (milliseconds);
}
