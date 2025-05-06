#ifndef PHILO_BONUS_H
#define PHILO_BONUS_H

#include <semaphore.h>
#include <sys/time.h>

typedef struct s_sim_info
{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_eat;
	int	num_philos;
	long long	start_time;
	sem_t	*forks_sem;
	sem_t	*write_sem;
	sem_t	*death_sem;
	sem_t	*table_sem;
}	t_sim_info;

void		write_log(int id, const char *msg, t_sim_info *info);
long long	get_timestamp_ms(void);
void 		run_philosopher(int id, t_sim_info *info);

#endif
