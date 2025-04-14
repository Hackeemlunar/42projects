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
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

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
void	cleanup(t_sim *sim);
long	get_time_in_mil(void);
int		start_simulation(t_sim *sim);
void	*do_monitor(void *sim);
void	philo_usleep(size_t mls);
void	go_await_your_death(t_philo *philo);

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
	philo_usleep(1); // Just a tiny wait to avoid CPU burning
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

void	go_await_your_death(t_philo *philo)
{
	long	relative_time;
	long	current_time;

	go_think(philo);
	current_time = get_time_in_mil();
	relative_time = current_time - philo->info->start_time;
	pthread_mutex_lock(&philo->info->print_mutex);
	printf("%13ld %d has taken a fork\n", relative_time, philo->id);
	pthread_mutex_unlock(&philo->info->print_mutex);
	philo_usleep(philo->info->time_to_die);
	current_time = get_time_in_mil();
	relative_time = current_time - philo->info->start_time;
	pthread_mutex_lock(&philo->info->print_mutex);
	printf("%13ld %d died\n", relative_time, philo->id);
	pthread_mutex_unlock(&philo->info->print_mutex);
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
	philo_usleep(philo->info->time_to_eat);
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
		{
	    	go_sleep(philo);
		}
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
	int		all_done;

	sim = (t_sim *)simulation;
	while (1)
	{
		i = -1;
		all_done = 1;
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
			if (sim->info->total_meals != -1)
			{
				pthread_mutex_lock(&sim->info->eat_update_mutex);
				if (sim->philos[i]->times_eaten < sim->info->total_meals)
					all_done = 0;
				pthread_mutex_unlock(&sim->info->eat_update_mutex);
			}
		}
		if (sim->info->total_meals != -1 && all_done)
		{
			pthread_mutex_lock(&sim->info->stop_mutex);
			sim->info->stop_sim = 1;
			pthread_mutex_unlock(&sim->info->stop_mutex);
			return (NULL);
		}
		usleep(1000); // Small sleep to prevent CPU hogging
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

int	init_args(t_sim **sim, char **argv, int argc)
{
	int	num_philo;

	num_philo = ft_atol(argv[1]);
	*sim = (t_sim *) malloc(sizeof(t_sim));
	if (!*sim)
		return (printf("Error: Could not allocate memory\n"), 1);

	(*sim)->info = (t_sim_info *) malloc(sizeof(t_sim_info));
	if (!(*sim)->info)
	{
		free(*sim);
		return (printf("Error: Could not allocate memory\n"), 1);
	}

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

int	init_philos(t_sim *sim)
{
	int	i;
	int	num_philo;

	i = 0;
	num_philo = sim->info->num_of_philo;
	sim->philos = (t_philo **)malloc(sizeof(t_philo *) * num_philo);
	if (!sim->philos)
		return (printf("Error: Could not allocate memory\n"), 1);
	while (i < num_philo)
	{
		sim->philos[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!sim->philos[i])
		{
			// Free previously allocated memory
			while (--i >= 0)
				free(sim->philos[i]);
			free(sim->philos);
			return (printf("Error: Could not allocate memory\n"), 1);
		}
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

int	init_forks_mutex(t_sim *sim)
{
	int	i;
	int	num_philo;

	i = 0;
	num_philo = sim->info->num_of_philo;
	sim->info->forks_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num_philo);
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

void	philo_usleep(size_t ms)
{
	long	start;
	long	current;

	start = get_time_in_mil();
	current = start;
	while (current - start < (long)ms)
	{
		usleep(500);
		current = get_time_in_mil();
	}
}

int	main(int argc, char **argv)
{
	t_sim		*sim;
	int			num_philo;

	if (argc < 5 || argc > 6)
		return (printf("Error: ./philo arg1, arg2, arg3, arg4 [arg5]\n"), 1);
	num_philo = ft_atol(argv[1]);
	if (num_philo < 1)
		return (printf("Error: invalid philosophers\n"), 1);

	if (init_args(&sim, argv, argc))
		return (1);
	if (init_philos(sim))
		return (cleanup(sim), 1);
	if (init_forks_mutex(sim))
		return (cleanup(sim), 1);
	if (start_simulation(sim))
		return (cleanup(sim), 1);
	cleanup(sim);
	return (0);
}
