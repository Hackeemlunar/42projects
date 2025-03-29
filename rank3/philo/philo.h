

#ifndef PHILO_H
# define PHILO_H

#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include "arena.h"

typedef enum e_philo_action
{
	SLEEPING,
	EATING,
	THINKING
}			t_philo_action;

typedef struct s_sim_info
{
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks_mutex;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	int				num_of_philo;
	int				*forks;
	int				total_meals;
	int				stop_sim;
}				t_sim_info;

typedef struct s_philo
{
	t_sim_info		*info;
	t_philo_action	action;
	pthread_t		thread;
	long			elapsed_time;
	int				id;
	int				times_eaten;
	int				left_fork;
	int				right_fork;
	long			last_meal_time;
}				t_philo;

typedef struct s_sim
{
	t_philo		**philos;
	t_sim_info	*info;
}				t_sim;

/* Function Prototypes */
void	go_eat(t_philo *philo);
void	go_think(t_philo *philo);
void	go_sleep(t_philo *philo);
void	*do_philosophy(void *sim);
int		is_dead(t_philo *philo);
long	ft_atol(const char *s);
void	cleanup(t_sim *sim, t_arena *arena);
long	get_time_in_mil(void);

#endif
