/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:32:19 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/23 21:04:24 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <string.h>
# include <limits.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include "arena.h"

typedef enum e_philo_action
{
	SLEEPING,
	EATING,
	THINKING
}			t_philo_action;

typedef struct s_sim_info
{
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		*forks;
	int		total_eat_times;
}				t_sim_info;

typedef struct s_philo
{
	t_sim_info		*info;
	t_philo_action	action;
	pthread_t		thread;
	int				id;
	int				elapsed_time;
	int				times_eaten;
	int				left_fork;
	int				right_fork;
}				t_philo;

typedef struct s_sim
{
	t_philo		**philos;
	int			num_of_philo;
	t_sim_info	*info;
}				t_sim;

void	go_eat(t_philo *philo);
void	go_think(t_philo *philo);
void	go_sleep(t_philo *philo);
void	*do_philosophy(void *sim);
int		is_dead(t_philo *philo);
int		ft_atoi(const char *s);

#endif