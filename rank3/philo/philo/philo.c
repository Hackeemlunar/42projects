/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:32:16 by hmensah-          #+#    #+#             */
/*   Updated: 2025/05/02 17:49:19 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	i = -1;
	num_philo = sim->info->num_of_philo;
	sim->philos = (t_philo **)malloc(sizeof(t_philo *) * num_philo);
	if (!sim->philos)
		return (printf("Error: Could not allocate memory\n"), 1);
	while (++i < num_philo)
	{
		sim->philos[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!sim->philos[i])
		{
			while (--i >= 0)
				free(sim->philos[i]);
			free(sim->philos);
			return (printf("Error: Could not allocate memory\n"), 1);
		}
		sim->philos[i]->info = sim->info;
		sim->philos[i]->id = i + 1;
		sim->philos[i]->action = THINKING;
		sim->philos[i]->left_fork = i;
		sim->philos[i]->right_fork = (i + 1) % num_philo;
	}
	return (0);
}

int	init_forks_mutex(t_sim *sim)
{
	int	i;
	int	num_philo;

	i = 0;
	num_philo = sim->info->num_of_philo;
	sim->info->forks_mutex = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * num_philo);
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
