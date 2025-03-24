/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:32:16 by hmensah-          #+#    #+#             */
/*   Updated: 2025/03/20 20:32:18 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_args(t_arena *arena, t_sim *sim, char **argv, int argc)
{
	int		num_philo;

	num_philo = ft_atoi(argv[1]);
	sim = (t_sim *) arena_alloc(arena, sizeof(t_sim));
	if (!sim)
		return (printf("Error: Could not allocate memory\n"), 1);
	sim->num_of_philo = num_philo;
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		sim->total_eat_times = ft_atoi(argv[5]);
	else
		sim->total_eat_times = -1;
	sim->forks = (int *) arena_alloc(arena, sizeof(int) * num_philo);
	if (!sim->forks)
		return (printf("Error: Could not allocate memory\n"), 1);
	return (0);
}

int	init_philos(t_arena *arena, t_sim *sim)
{
	int		i;
	int		num_philo;

	i = 0;
	num_philo = sim->num_of_philo;
	sim->philos = (t_philo **)arena_alloc(arena, sizeof(t_philo *) * num_philo);
	if (!sim->philos)
		return (printf("Error: Could not allocate memory\n"), 1);
	while (i < num_philo)
	{
		sim->philos[i] = (t_philo *) arena_alloc(arena, sizeof(t_philo));
		if (!sim->philos[i])
			return (printf("Error: Could not allocate memory\n"), 1);
		sim->philos[i]->id = i;
		sim->philos[i]->action = THINKING;
		sim->philos[i]->elapsed_time = 0;
		sim->philos[i]->times_eaten = 0;
		sim->philos[i]->left_fork = i;
		sim->philos[i]->right_fork = (i + 1) % num_philo;
		i++;
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_sim		*sim;
	t_arena		*arena;
	int			num_philo;

	if (argc < 5 || argc > 6)
		return (printf("Error: ./philo arg1, arg2, arg3, arg4 [arg5] \n"), 1);
	num_philo = ft_atoi(argv[1]);
	if (num_philo < 1)
		return (printf("Error: invalid philosophers\n"), 1);
	arena = arena_create(sizeof(t_sim) + (sizeof(t_philo) * num_philo) * 5);
	if (!arena)
		return (printf("Error: Could not allocate memory\n"), 1);
	if (init_args(arena, sim, argv, argc))
		return (1);
	if (init_philos(arena, sim))
		return (1);
	return (0);
}