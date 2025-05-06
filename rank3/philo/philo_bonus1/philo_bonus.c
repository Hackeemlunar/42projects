#include "philo_bonus.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

void run_philosopher(int id, t_sim_info *info)
{
    long long last_meal_time = info->start_time;
    int eat_count = 0;

    while (1) {
     
        // Check if this philosopher is dead
        long long now = get_timestamp_ms();
        if (now - last_meal_time > info->time_to_die)
        {
            write_log(id, "died", info);
            sem_post(info->death_sem);
            exit(EXIT_FAILURE);
        }

        // Take forks
        sem_wait(info->table_sem);
        sem_wait(info->forks_sem);
        sem_wait(info->forks_sem);

        // Log fork taken
        write_log(id, "has taken a fork", info);
        write_log(id, "has taken a fork", info);

        // Eat
        write_log(id, "is eating", info);
        last_meal_time = get_timestamp_ms();
        eat_count++;
        usleep(info->time_to_eat * 1000);

        // Check for num_eat condition
        if (info->num_eat != -1 && eat_count >= info->num_eat) {
            sem_post(info->death_sem); // Signal end of simulation
            exit(EXIT_SUCCESS);
        }

        // Release forks
        sem_post(info->forks_sem);
        sem_post(info->forks_sem);
        sem_post(info->table_sem);

        // Sleep
        write_log(id, "is sleeping", info);
        long long remaining = info->time_to_sleep;
        while (remaining > 0) {
            usleep(10000);
            remaining -= 10;
            now = get_timestamp_ms();
            if (now - last_meal_time > info->time_to_die) {
                write_log(id, "died", info);
                sem_post(info->death_sem);
                exit(EXIT_FAILURE);
            }
        }

        // Think
        write_log(id, "is thinking", info);
        now = get_timestamp_ms();
        if (now - last_meal_time > info->time_to_die) {
            write_log(id, "died", info);
            sem_post(info->death_sem);
            exit(EXIT_FAILURE);
        }
    }
}

int ft_atoi(const char *str)
{
    int sign;
    int result;

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

void init(t_sim_info *info, char **argv, int argc)
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
    info->forks_sem = sem_open("forks_sem", O_CREAT | O_EXCL, 0644, info->num_philos);
    info->write_sem = sem_open("write_sem", O_CREAT | O_EXCL, 0644, 1);
    info->death_sem = sem_open("death_sem", O_CREAT | O_EXCL, 0644, 0);
    info->table_sem = sem_open("table_sem", O_CREAT | O_EXCL, 0644, info->num_philos - 1);
    if (info->forks_sem == SEM_FAILED || info->write_sem == SEM_FAILED
            || info->death_sem == SEM_FAILED || info->table_sem == SEM_FAILED)
    {
        printf("sem_open");
        exit(EXIT_FAILURE);
    }
}

void start_simulation(t_sim_info *info, pid_t *pids)
{
    int i;
    pid_t pid;

    i = -1;
    while (++i < info->num_philos)
    {
        pid = fork();
        if (pid < 0)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            run_philosopher(i + 1, info);
            exit(EXIT_SUCCESS);
        }
        else
            pids[i] = pid;
    }
    sem_wait(info->death_sem);
    i = -1;
    while (++i < info->num_philos)
        kill(pids[i], SIGTERM);
    i = -1;
    while (++i < info->num_philos)
        waitpid(pids[i], NULL, 0);
 }

int main(int argc, char **argv)
{
    t_sim_info  info;
    pid_t       *pids;

    if (argc < 5 || argc > 6)
    {
        printf("Usage: %s num_philos time_to_die time_to_eat time_to_sleep [num_eat]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    init(&info, argv, argc);
    info.start_time = get_timestamp_ms();
    pids = malloc(info.num_philos * sizeof(pid_t));
    if (!pids)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
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
    return 0;
}
