/* ************************************************************************** */
/*                               philo_bonus.c                              */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>

long	get_time_in_mil(void)
{
	struct timeval	current_time;
	long			seconds;
	long			microseconds;
	long			milliseconds;

	if (gettimeofday(&current_time, NULL) == -1)
	{
		printf("Error: gettimeofday\n");
		return (1);
	}
	seconds = current_time.tv_sec;
	microseconds = current_time.tv_usec;
	milliseconds = seconds * 1000 + microseconds / 1000;
	return (milliseconds);
}

/*
 * ft_atol: simple conversion function.
 */
long	ft_atol(const char *s)
{
	long	num;
	int		sign;

	num = 0;
	sign = 1;
	while (*s && (*s == ' ' || (*s >= 9 && *s <= 13)))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s && *s >= '0' && *s <= '9')
	{
		num = num * 10 + (*s - '0');
		s++;
	}
	return (num * sign);
}

/*
 * Initialization functions.
 */
int	sanity_check(t_sim *sim)
{
	if (sim->info->time_to_die < 0 || sim->info->time_to_eat < 0 ||
		sim->info->time_to_sleep < 0 || sim->info->num_of_philo < 1)
	{
		printf("Error: invalid arguments\n");
		return (1);
	}
	if (sim->info->total_meals == 0 || sim->info->total_meals < -1)
	{
		printf("Error: invalid arguments\n");
		return (1);
	}
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
	(*sim)->info->start_time = get_time_in_mil();
	return (sanity_check(*sim));
}

int	init_philos(t_arena *arena, t_sim *sim)
{
	int	i;
	int	num_philo;

	i = 0;
	num_philo = sim->info->num_of_philo;
	sim->philos = (t_philo **) arena_alloc(arena, sizeof(t_philo *) * num_philo);
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
		sim->philos[i]->times_eaten = 0;
		sim->philos[i]->last_meal_time = sim->info->start_time;
		i++;
	}
	return (0);
}

int	init_forks_sem(t_sim *sim)
{
	char	*sem_name;

	sem_unlink("/forks_sem"); /* Ensure no previous instance */
	sem_name = "/forks_sem";
	sim->info->forks = sem_open(sem_name, O_CREAT, 0644, sim->info->num_of_philo);
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

void	do_philosophy(t_philo *philo)
{
	while (1)
	{
		sem_wait(philo->info->forks);
		sem_wait(philo->info->print_sem);
		printf("%ld %d has taken a fork\n", get_time_in_mil() - philo->info->start_time, philo->id);
		sem_post(philo->info->print_sem);

		sem_wait(philo->info->forks);
		sem_wait(philo->info->print_sem);
		printf("%ld %d has taken a fork\n", get_time_in_mil() - philo->info->start_time, philo->id);
		sem_post(philo->info->print_sem);

		/* Eating */
		sem_wait(philo->info->print_sem);
		printf("%ld %d is eating\n", get_time_in_mil() - philo->info->start_time, philo->id);
		sem_post(philo->info->print_sem);
		philo->last_meal_time = get_time_in_mil();
		usleep(philo->info->time_to_eat * 1000);
		philo->times_eaten++;
		if (philo->info->total_meals != -1 && philo->times_eaten >= philo->info->total_meals)
			exit(0);
		/* Release forks */
		sem_post(philo->info->forks);
		sem_post(philo->info->forks);
		/* Sleeping */
		sem_wait(philo->info->print_sem);
		printf("%ld %d is sleeping\n", get_time_in_mil() - philo->info->start_time, philo->id);
		sem_post(philo->info->print_sem);
		usleep(philo->info->time_to_sleep * 1000);
		/* Thinking */
		sem_wait(philo->info->print_sem);
		printf("%ld %d is thinking\n", get_time_in_mil() - philo->info->start_time, philo->id);
		sem_post(philo->info->print_sem);
		usleep(1000);
	}
}

void	monitor_philos(t_sim *sim)
{
	int		i;
	long	now;
	int		philosophers_done;

	while (1)
	{
		i = 0;
		philosophers_done = 0;
		while (i < sim->info->num_of_philo)
		{
			now = get_time_in_mil();
			if ((now - sim->philos[i]->last_meal_time) > sim->info->time_to_die)
			{
				sem_wait(sim->info->print_sem);
				printf("%ld %d died\n", now - sim->info->start_time, sim->philos[i]->id);
				sem_post(sim->info->print_sem);
				i = 0;
				while (i < sim->info->num_of_philo)
				{
					kill(sim->philos[i]->pid, SIGKILL);
					i++;
				}
				return;
			}
			i++;
		}
		usleep(1000);

		if (sim->info->total_meals != -1)
		{
			i = 0;
			philosophers_done = 0;
			while (i < sim->info->num_of_philo)
			{
				if (waitpid(sim->philos[i]->pid, NULL, WNOHANG) > 0)
					philosophers_done++;
				i++;
			}
			if (philosophers_done == sim->info->num_of_philo)
				return;
		}
	}
}

int	start_simulation(t_sim *sim)
{
	int		i;
	pid_t	pid;

	i = 0;
	sim->info->start_time = get_time_in_mil();
	while (i < sim->info->num_of_philo)
	{
		pid = fork();
		if (pid < 0)
			return (printf("Error: fork failed\n"), 1);
		if (pid == 0)
		{
			do_philosophy(sim->philos[i]);
			exit(0);
		}
		else
			sim->philos[i]->pid = pid;
		i++;
	}
	monitor_philos(sim);
	i = 0;
	while (i < sim->info->num_of_philo)
	{
		waitpid(sim->philos[i]->pid, NULL, 0);
		i++;
	}
	return (0);
}

void	cleanup(t_sim *sim, t_arena *arena)
{
	sem_close(sim->info->forks);
	sem_close(sim->info->print_sem);
	arena_destroy(arena);
}

int	main(int argc, char **argv)
{
	t_sim		*sim;
	t_arena		*arena;

	if (argc < 5 || argc > 6)
		return (printf("Error: ./philo_bonus arg1 arg2 arg3 arg4 [arg5]\n"), 1);
	arena = arena_create(sizeof(t_sim) +
		(sizeof(t_sim_info)) + (sizeof(t_philo) * ft_atol(argv[1]) * 5));
	if (!arena)
		return (printf("Error: Could not allocate memory\n"), 1);
	if (init_args(arena, &sim, argv, argc))
		return (arena_destroy(arena), 1);
	if (init_philos(arena, sim))
		return (cleanup(sim, arena), 1);
	if (init_forks_sem(sim))
		return (cleanup(sim, arena), 1);
	if (init_print_sem(sim))
		return (cleanup(sim, arena), 1);
	if (start_simulation(sim))
		return (cleanup(sim, arena), 1);
	return (cleanup(sim, arena), 0);
}
