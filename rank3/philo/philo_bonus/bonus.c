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

	sem_unlink("/forks_sem");
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

void	go_sleep(t_philo *philo)
{
	long	relative_time;

	sem_wait(philo->info->print_sem);
	relative_time = get_time_in_mil() - philo->info->start_time;
	printf("%13ld %d is sleeping\n", relative_time, philo->id);
	sem_post(philo->info->print_sem);
	usleep(philo->info->time_to_sleep * 1000);
	philo->action = THINKING;
}

void	go_think(t_philo *philo)
{
	long	relative_time;

	sem_wait(philo->info->print_sem);
	relative_time = get_time_in_mil() - philo->info->start_time;
	printf("%13ld %d is thinking\n", relative_time, philo->id);
	sem_post(philo->info->print_sem);
	philo->action = EATING;
}
int	is_dead(t_philo *philo)
{
	long	time_since_last_meal;

	time_since_last_meal = get_time_in_mil() - philo->last_meal_time;
	if (time_since_last_meal > philo->info->time_to_die)
		return (1);
	return (0);
}
void	kill_all_philo(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->info->num_of_philo)
	{
		if (kill(sim->philos[i]->pid, 0) == 0)
			kill(sim->philos[i]->pid, SIGKILL);
		i++;
	}
	
}

void	go_eat(t_philo *philo)
{
	long	current_time;
	long	relative_time;

	sem_wait(philo->info->forks);
	current_time = get_time_in_mil();
	relative_time = current_time - philo->info->start_time;
	sem_wait(philo->info->print_sem);
	printf("%13ld %d has taken a fork\n", relative_time, philo->id);
	sem_post(philo->info->print_sem);
	sem_wait(philo->info->forks);
	current_time = get_time_in_mil();
	relative_time = current_time - philo->info->start_time;
	printf("%13ld %d has taken a fork\n", relative_time, philo->id);
	if (is_dead(philo))
		return ;
	current_time = get_time_in_mil();
	philo->last_meal_time = current_time;
	relative_time = current_time - philo->info->start_time;
	sem_wait(philo->info->print_sem);
	printf("%13ld %d is eating\n", relative_time, philo->id);
	sem_post(philo->info->print_sem);
	usleep(philo->info->time_to_eat * 1000);
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
	philo->times_eaten++;
	philo->action = SLEEPING;
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

void	announce_death(t_philo *philo)
{
	long	relative_time;
	relative_time = get_time_in_mil() - philo->info->start_time;
	sem_wait(philo->info->print_sem);
	printf("%13ld %d died\n", relative_time, philo->id);
	sem_post(philo->info->stop_sem);
}

void	do_philosophy(t_philo *philo)
{
	philo->times_eaten = 0;
	if (philo->info->num_of_philo == 1)
	{
		go_await_your_death(philo);
		return ;
	}
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
			exit(0);
		}
		else
			sim->philos[i]->pid = pid;
	}
	sem_wait(sim->info->stop_sem);
	kill_all_philo(sim);
	sem_post(sim->info->stop_sem);
	return (0);
}

void	cleanup(t_sim *sim, t_arena *arena)
{
	sem_close(sim->info->forks);
	sem_close(sim->info->print_sem);
	sem_close(sim->info->stop_sem);
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
	if (init_stop_sem(sim))
		return (cleanup(sim, arena), 1);
	if (start_simulation(sim))
		return (cleanup(sim, arena), 1);
	return (cleanup(sim, arena), 0);
}
