/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:30:19 by hmensah-          #+#    #+#             */
/*   Updated: 2025/04/07 21:22:41 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_forks_sem(t_sim *sim)
{
	char	*sem_name;

	sem_unlink("/forks_sem");
	sem_name = "/forks_sem";
	sim->info->forks
		= sem_open(sem_name, O_CREAT, 0644, sim->info->num_of_philo);
	if (sim->info->forks == SEM_FAILED)
	{
		printf("Error: Could not create forks semaphore\n");
		return (1);
	}
	sem_unlink("/forks_sem");
	return (0);
}

int	init_print_sem(t_sim *sim)
{
	char	*sem_name;

	sem_unlink("/print_sem");
	sem_name = "/print_sem";
	sim->info->print_sem = sem_open(sem_name, O_CREAT, 0644, 1);
	if (sim->info->print_sem == SEM_FAILED)
	{
		printf("Error: Could not create print semaphore\n");
		return (1);
	}
	sem_unlink("/print_sem");
	return (0);
}

int	init_stop_sem(t_sim *sim)
{
	char	*sem_name;

	sem_unlink("/stop_sem");
	sem_name = "/stop_sem";
	sim->info->stop_sem = sem_open(sem_name, O_CREAT, 0644, 0);
	if (sim->info->stop_sem == SEM_FAILED)
	{
		printf("Error: Could not create stop semaphore\n");
		return (1);
	}
	sem_unlink("/stop_sem");
	return (0);
}
