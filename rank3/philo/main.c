#include "philo.h"

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
	pthread_mutex_init(&(*sim)->info->print_mutex, NULL);
	(*sim)->info->forks = (int *) arena_alloc(arena, sizeof(int) * num_philo);
	if (!(*sim)->info->forks)
		return (printf("Error: Could not allocate memory\n"), 1);
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
		sim->philos[i]->left_fork = i;
		sim->philos[i]->right_fork = (i + 1) % num_philo;
		i++;
	}
	return (0);
}

int	start_simulation(t_sim *sim)
{
	int		i;
	int		num_philo;
	t_philo	**philos;

	i = 0;
	num_philo = sim->info->num_of_philo;
	philos = sim->philos;
	sim->info->start_time = get_time_in_mil();
	while (i < num_philo)
	{
		sim->philos[i]->last_meal_time = sim->info->start_time;
		if (pthread_create(&philos[i]->thread, NULL, do_philosophy, philos[i]))
			return (printf("Error: Could not create thread\n"), 1);
		i++;
	}
	i = 0;
	while (i < num_philo)
	{
		if (pthread_join(philos[i]->thread, NULL))
			return (printf("Error: Could not join thread\n"), 1);
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
			+ sizeof(t_sim_info) + (sizeof(t_philo) * num_philo) * 20);
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

int	is_dead(t_philo *philo)
{
	long	current_time;
	long	time_since_last_meal;
	long	relative_time;

	current_time = get_time_in_mil();
	pthread_mutex_lock(&philo->info->stop_mutex);
	time_since_last_meal = current_time - philo->last_meal_time;
	if (time_since_last_meal > philo->info->time_to_die)
	{
		philo->info->stop_sim = 1;
		pthread_mutex_unlock(&philo->info->stop_mutex);
		pthread_mutex_lock(&philo->info->print_mutex);
		relative_time = current_time - philo->info->start_time;
		printf("%13ld %d died\n", relative_time, philo->id);
		pthread_mutex_unlock(&philo->info->print_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->stop_mutex);
	return (0);
}

static void	do_philo_actions(t_philo *philo)
{
	if (philo->action == THINKING)
		go_think(philo);
	if (philo->action == EATING)
		go_eat(philo);
	if (philo->action == SLEEPING)
		go_sleep(philo);
}

void	*do_philosophy(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	philo->times_eaten = 0;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&philo->info->stop_mutex);
		if (philo->info->stop_sim ||
			(philo->times_eaten >= philo->info->total_meals && philo->info->total_meals != -1))
		{
			pthread_mutex_unlock(&philo->info->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->info->stop_mutex);
		if (is_dead(philo))
			break;
		do_philo_actions(philo);
	}
	return (NULL);
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

void	go_eat(t_philo *philo)
{
	long	current_time;
	long	relative_time;

	if (philo->left_fork < philo->right_fork)
	{
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
	else
	{
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
	if (is_dead(philo))
	{
		pthread_mutex_unlock(&philo->info->forks_mutex[philo->left_fork]);
		pthread_mutex_unlock(&philo->info->forks_mutex[philo->right_fork]);
		return ;
	}
	current_time = get_time_in_mil();
	pthread_mutex_lock(&philo->info->print_mutex);
	relative_time = current_time - philo->info->start_time;
	printf("%13ld %d is eating\n", relative_time, philo->id);
	pthread_mutex_unlock(&philo->info->print_mutex);
	philo->last_meal_time = current_time;
	usleep(philo->info->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->info->forks_mutex[philo->left_fork]);
	pthread_mutex_unlock(&philo->info->forks_mutex[philo->right_fork]);
	philo->times_eaten++;
	philo->action = SLEEPING;
}

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
	usleep(1000);
	philo->action = EATING;
}
