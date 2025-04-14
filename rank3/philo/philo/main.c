/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:16:46 by hmensah-          #+#    #+#             */
/*   Updated: 2025/04/14 16:43:57 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	eat_update_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks_mutex;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	int				num_of_philo;
	int				total_meals;
	int				stop_sim;
}				t_sim_info;

typedef struct s_philo
{
	t_sim_info		*info;
	t_philo_action	action;
	pthread_t		thread;
	long			elapsed_time;
	long			last_meal_time;
	int				id;
	int				job_done;
	int				times_eaten;
	int				left_fork;
	int				right_fork;
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
int		start_simulation(t_sim *sim);
void	*do_monitor(void *sim);
void	philo_usleep(size_t mls);
void	go_await_your_death(t_philo *philo);

void	go_sleep(t_philo *philo)
{
	long	relative_time;

	pthread_mutex_lock(&philo->info->print_mutex);
	relative_time = get_time_in_mil() - philo->info->start_time;
	printf("%13ld %d is sleeping\n", relative_time, philo->id);
	pthread_mutex_unlock(&philo->info->print_mutex);
	usleep(philo->info->time_to_sleep * 1000);
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
	usleep(1000);
}

void	cleanup(t_sim *sim, t_arena *arena)
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
	arena_destroy(arena);
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

void	go_await_your_death(t_philo *philo)
{
	long	relative_time;
	long	current_time;

	go_think(philo);
	current_time = get_time_in_mil();
	relative_time = current_time - philo->info->start_time;
	printf("%13ld %d has taken a fork\n", relative_time, philo->id);
	usleep(philo->info->time_to_die * 1000);
	current_time = get_time_in_mil();
	relative_time = current_time - philo->info->start_time;
	printf("%13ld %d died\n", relative_time, philo->id);
}

void	take_left_fork_first(t_philo *philo)
{
	long	relative_time;

	pthread_mutex_lock(&philo->info->forks_mutex[philo->left_fork]);
	pthread_mutex_lock(&philo->info->print_mutex);
	relative_time = get_time_in_mil() - philo->info->start_time;
	printf("%13ld %d has taken a fork\n", relative_time, philo->id);
	pthread_mutex_unlock(&philo->info->print_mutex);
	pthread_mutex_lock(&philo->info->forks_mutex[philo->right_fork]);
	pthread_mutex_lock(&philo->info->print_mutex);
	relative_time = get_time_in_mil() - philo->info->start_time;
	printf("%13ld %d has taken a fork\n", relative_time, philo->id);
	pthread_mutex_unlock(&philo->info->print_mutex);
}

void	take_right_fork_first(t_philo *philo)
{
	long	relative_time;

	pthread_mutex_lock(&philo->info->forks_mutex[philo->right_fork]);
	pthread_mutex_lock(&philo->info->print_mutex);
	relative_time = get_time_in_mil() - philo->info->start_time;
	printf("%13ld %d has taken a fork\n", relative_time, philo->id);
	pthread_mutex_unlock(&philo->info->print_mutex);
	pthread_mutex_lock(&philo->info->forks_mutex[philo->left_fork]);
	pthread_mutex_lock(&philo->info->print_mutex);
	relative_time = get_time_in_mil() - philo->info->start_time;
	printf("%13ld %d has taken a fork\n", relative_time, philo->id);
	pthread_mutex_unlock(&philo->info->print_mutex);
}

void	go_eat(t_philo *philo)
{
	long	current_time;
	long	relative_time;

	if (philo->left_fork < philo->right_fork)
		take_left_fork_first(philo);
	else
		take_right_fork_first(philo);
	current_time = get_time_in_mil();
	pthread_mutex_lock(&philo->info->eat_update_mutex);
	philo->last_meal_time = current_time;
	pthread_mutex_unlock(&philo->info->eat_update_mutex);
	pthread_mutex_lock(&philo->info->print_mutex);
	relative_time = current_time - philo->info->start_time;
	printf("%13ld %d is eating\n", relative_time, philo->id);
	pthread_mutex_unlock(&philo->info->print_mutex);
	usleep(philo->info->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->info->forks_mutex[philo->left_fork]);
	pthread_mutex_unlock(&philo->info->forks_mutex[philo->right_fork]);
	philo->times_eaten++;
	philo->action = SLEEPING;
}

void	*do_philosophy(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	philo->times_eaten = 0;
	if (philo->info->num_of_philo == 1)
		return (go_await_your_death(philo), NULL);
	while (1)
	{
        if (philo->action == THINKING)
		    go_think(philo);
	    else if (philo->action == EATING)
	    	go_eat(philo);
	    else if (philo->action == SLEEPING)
	    	go_sleep(philo);
		pthread_mutex_lock(&philo->info->stop_mutex);
		if (philo->info->stop_sim)
		{
			pthread_mutex_unlock(&philo->info->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->info->stop_mutex);
	}
	return (NULL);
}

int	is_dead(t_philo *philo)
{
	long	time_since_last_meal;

	pthread_mutex_lock(&philo->info->eat_update_mutex);
	time_since_last_meal = get_time_in_mil() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->info->eat_update_mutex);
	pthread_mutex_lock(&philo->info->stop_mutex);
	if (time_since_last_meal > philo->info->time_to_die)
	{
		philo->info->stop_sim = 1;
		pthread_mutex_unlock(&philo->info->stop_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->stop_mutex);
	return (0);
}



void	*do_monitor(void *simulation)
{
	int		i;
	long	rel_time;
	t_sim	*sim;

	sim = (t_sim *)simulation;
	while (1)
	{
		i = -1;
		while (++i < sim->info->num_of_philo)
		{
			if (is_dead(sim->philos[i]))
			{
				rel_time = get_time_in_mil()
					- sim->philos[i]->info->start_time;
				pthread_mutex_lock(&sim->info->print_mutex);
				printf("%13ld %d died\n", rel_time, sim->philos[i]->id);
				pthread_mutex_unlock(&sim->info->print_mutex);
				return (NULL);
			}
		}
	}
	return (NULL);
}

int	start_simulation(t_sim *sim)
{
	int			i;
	t_philo		**philos;
	pthread_t	monitor;

	i = -1;
	philos = sim->philos;
	sim->info->start_time = get_time_in_mil();
	if (sim->info->num_of_philo == 1)
		return (go_await_your_death(sim->philos[0]), 0);
	while (++i < sim->info->num_of_philo)
	{
		sim->philos[i]->last_meal_time = get_time_in_mil();
		if (pthread_create(&philos[i]->thread, NULL, do_philosophy, philos[i]))
			return (printf("Error: Could not create thread\n"), 1);
	}
	if (pthread_create(&monitor, NULL, do_monitor, sim))
		return (printf("Error: Could not create thread\n"), 1);
	if (pthread_join(monitor, NULL))
		return (printf("Error: Could not join thread\n"), 1);
	i = -1;
	while (++i < sim->info->num_of_philo)
		if (pthread_join(philos[i]->thread, NULL))
			return (printf("Error: Could not detach thread\n"), 1);
	return (0);
}


int	sanity_check(t_sim *sim)
{
	if (sim->info->time_to_die < 0 || sim->info->time_to_eat < 0
		|| sim->info->time_to_sleep < 0 || sim->info->num_of_philo < 1)
		return (printf("Error: invalid arguments\n"), 1);
	if (sim->info->total_meals == 0 || sim->info->total_meals < -1)
		return (printf("Error: invalid arguments\n"), 1);
	return (0);
}

int	init_args(t_arena *arena, t_sim **sim, char **argv, int argc)
{
	int	num_philo;

	num_philo = ft_atol(argv[1]);
	*sim = (t_sim *) arena_alloc(arena, sizeof(t_sim));
	(*sim)->info = (t_sim_info *) arena_alloc(arena, sizeof(t_sim_info));
	if (!sim || !(*sim)->info)
		return (printf("Error: Could not allocate memory\n"), 1);
	(*sim)->info->num_of_philo = num_philo;
	(*sim)->info->time_to_die = ft_atol(argv[2]);
	(*sim)->info->time_to_eat = ft_atol(argv[3]);
	(*sim)->info->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		(*sim)->info->total_meals = ft_atol(argv[5]);
	else
		(*sim)->info->total_meals = -1;
	(*sim)->info->stop_sim = 0;
	pthread_mutex_init(&(*sim)->info->stop_mutex, NULL);
	pthread_mutex_init(&(*sim)->info->eat_update_mutex, NULL);
	pthread_mutex_init(&(*sim)->info->print_mutex, NULL);
	return (sanity_check(*sim));
}

int	init_philos(t_arena *arena, t_sim *sim)
{
	int	i;
	int	num_philo;

	i = 0;
	num_philo = sim->info->num_of_philo;
	sim->philos = (t_philo **)arena_alloc(arena, sizeof(t_philo *) * num_philo);
	if (!sim->philos)
		return (printf("Error: Could not allocate memory\n"), 1);
	while (i < num_philo)
	{
		sim->philos[i] = (t_philo *) arena_alloc(arena, sizeof(t_philo));
		if (!sim->philos[i])
			return (printf("Error: Could not allocate memory\n"), 1);
		sim->philos[i]->info = sim->info;
		sim->philos[i]->id = i + 1;
		sim->philos[i]->action = THINKING;
		sim->philos[i]->job_done = 0;
		sim->philos[i]->left_fork = i;
		sim->philos[i]->right_fork = (i + 1) % num_philo;
		i++;
	}
	return (0);
}

int	init_forks_mutex(t_arena *arena, t_sim *sim)
{
	int	i;
	int	num_philo;

	i = 0;
	num_philo = sim->info->num_of_philo;
	sim->info->forks_mutex = (pthread_mutex_t *) arena_alloc(arena,
			sizeof(pthread_mutex_t) * num_philo);
	if (!sim->info->forks_mutex)
		return (printf("Error: Could not allocate memory\n"), 1);
	while (i < num_philo)
	{
		if (pthread_mutex_init(&sim->info->forks_mutex[i], NULL))
			return (printf("Error: Could not initialize mutex\n"), 1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_sim		*sim;
	t_arena		*arena;
	int			num_philo;

	if (argc < 5 || argc > 6)
		return (printf("Error: ./philo arg1, arg2, arg3, arg4 [arg5]\n"), 1);
	num_philo = ft_atol(argv[1]);
	if (num_philo < 1)
		return (printf("Error: invalid philosophers\n"), 1);
	arena = arena_create(sizeof(t_sim) + (sizeof(pthread_mutex_t) * num_philo)
			+ sizeof(t_sim_info) + (sizeof(t_philo) * num_philo) * 5);
	if (!arena)
		return (printf("Error: Could not allocate memory\n"), 1);
	if (init_args(arena, &sim, argv, argc))
		return (arena_destroy(arena), 1);
	if (init_philos(arena, sim))
		return (cleanup(sim, arena), 1);
	if (init_forks_mutex(arena, sim))
		return (cleanup(sim, arena), 1);
	if (start_simulation(sim))
		return (cleanup(sim, arena), 1);
	return (cleanup(sim, arena), 0);
}
