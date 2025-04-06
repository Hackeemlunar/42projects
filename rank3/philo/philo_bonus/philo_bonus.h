/* ************************************************************************** */
/*                                 philo_bonus.h                              */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include "arena.h"

typedef enum e_philo_action
{
	SLEEPING,
	EATING,
	THINKING
}			t_philo_action;

typedef struct s_sim_info
{
	sem_t		*forks;
	sem_t		*print_sem;
	sem_t		*stop_sem;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		start_time;
	int			num_of_philo;
	int			total_meals;
}				t_sim_info;

typedef struct s_philo
{
	t_sim_info		*info;
	t_philo_action	action;
	pid_t			pid;
	long			last_meal_time;
	int				id;
	int				times_eaten;
}				t_philo;

typedef struct s_sim
{
	t_philo		**philos;
	t_sim_info	*info;
}				t_sim;

/* Function Prototypes */
void	go_eat(t_philo *philo);
void	go_sleep(t_philo *philo);
void	go_think(t_philo *philo);
int		start_simulation(t_sim *sim);
int		is_dead(t_philo *philo);
long	ft_atol(const char *s);
void	cleanup(t_sim *sim, t_arena *arena);
long	get_time_in_mil(void);
int		start_simulation(t_sim *sim);
int		init_forks_sem(t_sim *sim);
int		init_print_sem(t_sim *sim);
int		init_stop_sem(t_sim *sim);
void	kill_all_philo(t_sim *sim);


#endif
