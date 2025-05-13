/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:03:55 by hmensah-          #+#    #+#             */
/*   Updated: 2025/05/13 15:02:52 by hmensah-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * result);
}

void	init(t_sim_info *info, char **argv, int argc)
{
	info->num_philos = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->num_eat = -1;
	if (argc == 6)
		info->num_eat = ft_atoi(argv[5]);
	sem_unlink("forks_sem");
	sem_unlink("write_sem");
	sem_unlink("death_sem");
	sem_unlink("table_sem");
	info->forks_sem = sem_open("forks_sem", O_CREAT
			| O_EXCL, 0644, info->num_philos);
	info->write_sem = sem_open("write_sem", O_CREAT | O_EXCL, 0644, 1);
	info->death_sem = sem_open("death_sem", O_CREAT | O_EXCL, 0644, 0);
	info->table_sem = sem_open("table_sem", O_CREAT
			| O_EXCL, 0644, info->num_philos - 1);
	if (info->forks_sem == SEM_FAILED || info->write_sem == SEM_FAILED
		|| info->death_sem == SEM_FAILED || info->table_sem == SEM_FAILED)
	{
		printf("sem_open");
		exit(EXIT_FAILURE);
	}
}

static inline void	kill_and_wait(t_sim_info *info, pid_t *pids)
{
	int	i;

	i = -1;
	while (++i < info->num_philos)
	{
		if (kill(pids[i], 0) == 0)
			kill(pids[i], SIGTERM);
	}
	i = -1;
	while (++i < info->num_philos)
		waitpid(pids[i], NULL, 0);
}

int	start_simulation(t_sim_info *info, pid_t *pids)
{
	int		i;
	pid_t	pid;

	if (info->num_philos == 1)
		return (go_await_death(info), 1);
	i = -1;
	info->start_time = get_timestamp_ms();
	while (++i < info->num_philos)
	{
		pid = fork();
		if (pid < 0)
			return (printf("fork error"), 1);
		else if (pid == 0)
		{
			if (!run_philosopher(i + 1, info))
				usleep(info->time_to_die * 1000);
			sem_post(info->death_sem);
			exit(EXIT_SUCCESS);
		}
		else
			pids[i] = pid;
	}
	sem_wait(info->death_sem);
	kill_and_wait(info, pids);
	return (0);
}

int	main(int argc, char **argv)
{
	t_sim_info	info;
	pid_t		*pids;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s num_philos time_to_die time_to_eat time_to_sleep"
			"[num_eat]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	init(&info, argv, argc);
	pids = malloc(info.num_philos * sizeof(pid_t));
	if (!pids)
		return (printf("Memory allocation failed\n"), 1);
	start_simulation(&info, pids);
	sem_close(info.forks_sem);
	sem_close(info.write_sem);
	sem_close(info.death_sem);
	sem_close(info.table_sem);
	sem_unlink("forks_sem");
	sem_unlink("write_sem");
	sem_unlink("death_sem");
	sem_unlink("table_sem");
	free(pids);
	return (0);
}
