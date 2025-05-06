/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_bonus1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:33:55 by hmensah-          #+#    #+#             */
/*   Updated: 2025/05/02 19:50:00 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	go_await_your_death(t_philo *philo)
{
	long	relative_time;

	go_think(philo);
	relative_time = get_time_in_mil() - philo->info->start_time;
	printf("%13ld %d has taken a fork\n", relative_time, philo->id);
	usleep(philo->info->time_to_die * 1000);
	relative_time = get_time_in_mil() - philo->info->start_time;
	printf("%13ld %d died\n", relative_time, philo->id);
}

void	announce_death(t_philo *philo)
{
	long	relative_time;

	sem_wait(philo->info->print_sem);
	relative_time = get_time_in_mil() - philo->info->start_time;
	printf("%13ld %d died\n", relative_time, philo->id);
}

void	do_philosophy(t_philo *philo)
{
	philo->times_eaten = 0;
	if (philo->info->num_of_philo == 1)
		return (go_await_your_death(philo));
	while (1)
	{
		if (is_dead(philo))
		{
			announce_death(philo);
			return ;
		}
		if ((philo->times_eaten >= philo->info->total_meals
				&& philo->info->total_meals != -1))
			break ;
		if (philo->action == THINKING)
			go_think(philo);
		else if (philo->action == EATING)
			go_eat(philo);
		else if (philo->action == SLEEPING)
			go_sleep(philo);
	}
}

int	start_simulation(t_sim *sim)
{
	int		i;
	pid_t	pid;

	i = -1;
	sim->info->start_time = get_time_in_mil();
	while (++i < sim->info->num_of_philo)
	{
		pid = fork();
		if (pid < 0)
			return (printf("Error: fork failed\n"), 1);
		if (pid == 0)
		{
			do_philosophy(sim->philos[i]);
			sem_post(sim->info->stop_sem);
			exit(0);
		}
		else
			sim->philos[i]->pid = pid;
	}
	sem_wait(sim->info->stop_sem);
	kill_all_philo(sim);
	return (0);
}

void	cleanup(t_sim *sim, t_arena *arena)
{
	sem_close(sim->info->forks);
	sem_close(sim->info->print_sem);
	sem_close(sim->info->stop_sem);
	arena_destroy(arena);
}
