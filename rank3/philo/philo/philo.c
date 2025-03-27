/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:32:16 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/25 18:20:32 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_args(t_arena *arena, t_sim **sim, char **argv, int argc)
{
	int		num_philo;

	num_philo = ft_atol(argv[1]);
	*sim = (t_sim *) arena_alloc(arena, sizeof(t_sim));
	(*sim)->info = (t_sim_info *) arena_alloc(arena, sizeof(t_sim_info));
	if (!sim || !(*sim)->info)
		return (printf("Error: Could not allocate memory\n"), 1);
	(*sim)->num_of_philo = num_philo;
	(*sim)->info->time_to_die = ft_atol(argv[2]);
	(*sim)->info->time_to_eat = ft_atol(argv[3]);
	(*sim)->info->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		(*sim)->info->total_meals = ft_atol(argv[5]);
	else
		(*sim)->info->total_meals = -1;
	(*sim)->info->stop_sim = 0;
	pthread_mutex_init(&(*sim)->info->stop_mutex, NULL);
	(*sim)->info->forks = (int *) arena_alloc(arena, sizeof(int) * num_philo);
	if (!(*sim)->info->forks)
		return (printf("Error: Could not allocate memory\n"), 1);
	return (0);
}

int	init_philos(t_arena *arena, t_sim *sim)
{
	int		i;
	int		num_philo;

	i = -1;
	num_philo = sim->num_of_philo;
	sim->philos = (t_philo **)arena_alloc(arena, sizeof(t_philo *) * num_philo);
	if (!sim->philos)
		return (printf("Error: Could not allocate memory\n"), 1);
	while (++i < num_philo)
	{
		sim->philos[i] = (t_philo *) arena_alloc(arena, sizeof(t_philo));
		if (!sim->philos[i])
			return (printf("Error: Could not allocate memory\n"), 1);
		sim->philos[i]->info = sim->info;
		sim->philos[i]->id = i + 1;
		if (i % 3 == 1)
			sim->philos[i]->action = EATING;
		else if (i % 3 == 2)
			sim->philos[i]->action = THINKING;
		else
			sim->philos[i]->action = SLEEPING;
		sim->philos[i]->left_fork = i;
		sim->philos[i]->right_fork = (i + 1) % num_philo;
	}
	return (0);
}

int	start_simulation(t_sim *sim)
{
	int		i;
	int		num_philo;
	t_philo	**philos;

	i = 0;
	num_philo = sim->num_of_philo;
	philos = sim->philos;
	while (i < num_philo)
	{
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
	int		i;
	int		num_philo;

	i = 0;
	num_philo = sim->num_of_philo;
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
		return (printf("Error: ./philo arg1, arg2, arg3, arg4 [arg5] \n"), 1);
	num_philo = ft_atol(argv[1]);
	if (num_philo < 1)
		return (printf("Error: invalid philosophers\n"), 1);
	arena = arena_create(sizeof(t_sim) + (sizeof(pthread_mutex_t) * num_philo)
			+ (sizeof(t_philo) * num_philo) * 20);
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
