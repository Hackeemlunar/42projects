#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <semaphore.h>
#include <sys/wait.h>

#include "arena.h" // You might need to adapt this or remove it

typedef enum e_philo_action {
    SLEEPING,
    EATING,
    THINKING
} t_philo_action;

typedef struct s_sim_info {
    sem_t *forks_sem; // Semaphore for forks
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long start_time;
    int num_of_philo;
    int total_meals;
    int stop_sim;
} t_sim_info;

typedef struct s_philo {
    t_sim_info *info;
    t_philo_action action;
    pid_t pid; // Process ID instead of thread
    long elapsed_time;
    int id;
    int times_eaten;
    long last_meal_time;
} t_philo;

typedef struct s_sim {
    t_philo **philos;
    t_sim_info *info;
} t_sim;

/* Function Prototypes */
void go_eat(t_philo *philo);
void go_think(t_philo *philo);
void go_sleep(t_philo *philo);
void do_philosophy(t_philo *philo); // Pass philo directly
int is_dead(t_philo *philo);
long ft_atol(const char *s);
void cleanup(t_sim *sim); // Arena cleanup might not be needed
long get_time_in_mil(void);
int init_args(t_sim_info **info, char **argv, int argc);
int init_philos(t_sim_info *info, t_philo ***philos);

int main(int argc, char **argv) {
    t_sim_info *info;
    t_philo **philos;
    int i;
    int num_philo;

    if (argc < 5 || argc > 6) {
        printf("Error: ./philo_bonus arg1, arg2, arg3, arg4 [arg5]\n");
        return 1;
    }

    if (init_args(&info, argv, argc))
        return 1;

    if (init_philos(info, &philos)) {
        //cleanup(sim); // Cleanup adapted
        return 1;
    }

    num_philo = info->num_of_philo;
    info->start_time = get_time_in_mil();

    // Create philosopher processes
    for (i = 0; i < num_philo; i++) {
        philos[i]->last_meal_time = info->start_time;
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            return 1;
        } else if (pid == 0) {
            // Child process (philosopher)
            do_philosophy(philos[i]);
            exit(0); // Child process must exit
        } else {
            philos[i]->pid = pid;
        }
    }

    // Parent process: Wait for children (philosophers)
    for (i = 0; i < num_philo; i++) {
        int status;
        waitpid(philos[i]->pid, &status, 0);
        if (WIFEXITED(status)) {
           // printf("Philosopher %d exited with status %d\n", i + 1, WEXITSTATUS(status));
        }
    }

    // Cleanup in the main process
    sem_close(info->forks_sem);
    sem_unlink("/forks_sem"); // Unlink the semaphore
    free(info);
    free(philos);
    return 0;
}

int init_args(t_sim_info **info, char **argv, int argc) {
    int num_philo;

    num_philo = ft_atol(argv[1]);
    if (num_philo < 1)
    {
        printf("Error: invalid philosophers\n");
        return (1);
    }
    *info = (t_sim_info *)malloc(sizeof(t_sim_info));
    if (!*info)
        return (printf("Error: Could not allocate memory\n"), 1);
    (*info)->num_of_philo = num_philo;
    (*info)->time_to_die = ft_atol(argv[2]);
    (*info)->time_to_eat = ft_atol(argv[3]);
    (*info)->time_to_sleep = ft_atol(argv[4]);
    if (argc == 6)
        (*info)->total_meals = ft_atol(argv[5]);
    else
        (*info)->total_meals = -1;
    (*info)->stop_sim = 0;

    // Initialize the semaphore
    sem_unlink("/forks_sem"); // Ensure no leftover semaphore
    (*info)->forks_sem = sem_open("/forks_sem", O_CREAT, 0644, num_philo);
    if ((*info)->forks_sem == SEM_FAILED) {
        perror("sem_open");
        return 1;
    }
    return 0;
}

int init_philos(t_sim_info *info, t_philo ***philos) {
    int i;
    int num_philo;

    i = 0;
    num_philo = info->num_of_philo;
    *philos = (t_philo **)malloc(sizeof(t_philo *) * num_philo);
    if (!*philos)
        return (printf("Error: Could not allocate memory\n"), 1);
    while (i < num_philo) {
        (*philos)[i] = (t_philo *)malloc(sizeof(t_philo));
        if (!(*philos)[i])
            return (printf("Error: Could not allocate memory\n"), 1);
        (*philos)[i]->info = info;
        (*philos)[i]->id = i + 1;
        (*philos)[i]->action = THINKING;
        (*philos)[i]->times_eaten = 0;
        i++;
    }
    return 0;
}

void do_philosophy(t_philo *philo) {
    long current_time;
    long relative_time;

    if (philo->id % 2 == 0)
        usleep(1000);

    while (1) {
        // Check for death
        if (is_dead(philo)) {
            break;
        }

        // Check if all philosophers ate enough
        if (philo->info->total_meals != -1 && philo->times_eaten >= philo->info->total_meals) {
            break;
        }

        go_think(philo);

        // Take forks (using semaphore)
        sem_wait(philo->info->forks_sem);
        sem_wait(philo->info->forks_sem);

        current_time = get_time_in_mil();
        relative_time = current_time - philo->info->start_time;
        printf("%13ld %d has taken a fork\n", relative_time, philo->id);
        printf("%13ld %d has taken a fork\n", relative_time, philo->id);

        philo->action = EATING;
        go_eat(philo);

        // Release forks
        sem_post(philo->info->forks_sem);
        sem_post(philo->info->forks_sem);

        philo->action = SLEEPING;
        go_sleep(philo);
    }
    exit(0); // Ensure child process exits
}

int is_dead(t_philo *philo) {
    long current_time;
    long time_since_last_meal;
    long relative_time;

    current_time = get_time_in_mil();
    time_since_last_meal = current_time - philo->last_meal_time;
    if (time_since_last_meal > philo->info->time_to_die) {
        philo->info->stop_sim = 1;
        relative_time = current_time - philo->info->start_time;
        printf("%13ld %d died\n", relative_time, philo->id);
        return 1;
    }
    return 0;
}

void go_eat(t_philo *philo) {
    long current_time;
    long relative_time;

    current_time = get_time_in_mil();
    relative_time = current_time - philo->info->start_time;
    printf("%13ld %d is eating\n", relative_time, philo->id);
    philo->last_meal_time = current_time;
    usleep(philo->info->time_to_eat * 1000);
    philo->times_eaten++;
}

void go_sleep(t_philo *philo) {
    long relative_time;

    relative_time = get_time_in_mil() - philo->info->start_time;
    printf("%13ld %d is sleeping\n", relative_time, philo->id);
    usleep(philo->info->time_to_sleep * 1000);
}

void go_think(t_philo *philo) {
    long relative_time;

    relative_time = get_time_in_mil() - philo->info->start_time;
    printf("%13ld %d is thinking\n", relative_time, philo->id);
    usleep(1000);
}

long get_time_in_mil(void) {
    struct timeval current_time;
    long seconds;
    long microseconds;
    long milliseconds;

    if (gettimeofday(&current_time, NULL) == -1) {
        perror("gettimeofday");
        return 1;
    }
    seconds = current_time.tv_sec;
    microseconds = current_time.tv_usec;
    milliseconds = seconds * 1000 + microseconds / 1000;
    return milliseconds;
}

void cleanup(t_sim *sim) {
    // Cleanup semaphore and free memory
    sem_close(sim->info->forks_sem);
    sem_unlink("/forks_sem");
    free(sim->info);
    free(sim->philos);
    free(sim);
}