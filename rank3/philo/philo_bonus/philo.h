/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:32:19 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/29 22:04:06 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>
# include "arena.h"

# define THINKING 0
# define EATING 1
# define SLEEPING 2

typedef struct s_sim_info
{
	int		num_of_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		total_meals;
	int		stop_sim;
	long	start_time;
	sem_t	*forks_sem;
	sem_t	*print_sem;
	sem_t	*stop_sem;
	pid_t	*pids;
}	t_sim_info;

typedef struct s_philo
{
	t_sim_info	*info;
	long		last_meal_time;
	int			id;
	int			action;
	int			times_eaten;
	int			job_done;
}	t_philo;

typedef struct s_sim
{
	t_sim_info	*info;
	t_philo		**philos;
}	t_sim;

// Philosopher actions
void	go_think(t_philo *philo);
void	go_eat(t_philo *philo);
void	go_sleep(t_philo *philo);

// Utility functions
long	ft_atol(const char *str);
long	get_time_in_mil(void);
int		is_dead(t_philo *philo);
void	philosopher_routine(t_philo *philo);
int		start_simulation(t_sim *sim);
int		cleanup(t_sim *sim, t_arena *arena);
void	death_monitor(t_philo *philo);

#endif
