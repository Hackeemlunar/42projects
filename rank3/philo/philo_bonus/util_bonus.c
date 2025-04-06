/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:32:52 by hmensah-          #+#    #+#             */
/*   Updated: 2025/04/06 19:07:06 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	go_sleep(t_philo *philo)
{
	long	relative_time;

	sem_wait(philo->info->print_sem);
	relative_time = get_time_in_mil() - philo->info->start_time;
	printf("%13ld %d is sleeping\n", relative_time, philo->id);
	sem_post(philo->info->print_sem);
	usleep(philo->info->time_to_sleep * 1000);
	philo->action = THINKING;
}

void	go_think(t_philo *philo)
{
	long	relative_time;

	sem_wait(philo->info->print_sem);
	relative_time = get_time_in_mil() - philo->info->start_time;
	printf("%13ld %d is thinking\n", relative_time, philo->id);
	sem_post(philo->info->print_sem);
	philo->action = EATING;
}

int	is_dead(t_philo *philo)
{
	long	time_since_last_meal;

	time_since_last_meal = get_time_in_mil() - philo->last_meal_time;
	if (time_since_last_meal > philo->info->time_to_die)
		return (1);
	return (0);
}

void	kill_all_philo(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->info->num_of_philo)
	{
		if (kill(sim->philos[i]->pid, 0) == 0)
			kill(sim->philos[i]->pid, SIGKILL);
		i++;
	}
}

void	go_eat(t_philo *philo)
{
	long	current_time;
	long	relative_time;

	sem_wait(philo->info->forks);
	current_time = get_time_in_mil();
	relative_time = current_time - philo->info->start_time;
	sem_wait(philo->info->print_sem);
	printf("%13ld %d has taken a fork\n", relative_time, philo->id);
	sem_post(philo->info->print_sem);
	sem_wait(philo->info->forks);
	relative_time = get_time_in_mil() - philo->info->start_time;
	printf("%13ld %d has taken a fork\n", relative_time, philo->id);
	if (is_dead(philo))
		return ;
	current_time = get_time_in_mil();
	philo->last_meal_time = current_time;
	relative_time = current_time - philo->info->start_time;
	sem_wait(philo->info->print_sem);
	printf("%13ld %d is eating\n", relative_time, philo->id);
	sem_post(philo->info->print_sem);
	usleep(philo->info->time_to_eat * 1000);
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
	philo->times_eaten++;
	philo->action = SLEEPING;
}
