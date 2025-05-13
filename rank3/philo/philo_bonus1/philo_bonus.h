/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:14:22 by hmensah-          #+#    #+#             */
/*   Updated: 2025/05/13 16:52:56 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <pthread.h>

typedef struct s_sim_info
{
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_eat;
	int			num_philos;
	long long	start_time;
	sem_t		*forks_sem;
	sem_t		*write_sem;
	sem_t		*death_sem;
	sem_t		*table_sem;
	void		*mutex_ptr;
	int			current_philo_id;
}	t_sim_info;

typedef struct s_death_monitor
{
	t_sim_info		*info;
	long long		*last_meal_time;
	int				id;
	int				*running;
	pthread_mutex_t	*mutex;
}	t_death_monitor;

void		write_log(int id, const char *msg, t_sim_info *info);
void		write_death(int id, const char *msg, t_sim_info *info);
long long	get_timestamp_ms(void);
int			run_philosopher(int id, t_sim_info *info);
void		go_await_death(t_sim_info *info);
void		*monitor_death(void *arg);
int			go_eat(t_sim_info *info, long long *last, long long *now, int id);
void		do_others(int id, t_sim_info *info);
#endif
