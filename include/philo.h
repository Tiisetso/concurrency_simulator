/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:02:08 by timurray          #+#    #+#             */
/*   Updated: 2026/01/22 10:30:48 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_time_code
{
	SECOND,
	MILSECOND,
	MICSECOND
} t_time_code;

typedef enum e_status
{
	EAT,
	SLEEP,
	THINK,
	L_FORK,
	R_FORK,
	DIE
} t_status;

typedef unsigned int	uint;
typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

typedef struct s_fork
{
	pthread_mutex_t		fork;
	uint				i;
}						t_fork;
typedef struct s_philo
{
	uint				i;
	int				servings;
	uint				alive;
	uint				last_meal_time;
	uint				eating;
	uint				full;
	uint				life_left;
	pthread_t			thread_i;
	pthread_mutex_t		lock;
	t_fork				*right_fork;
	t_fork				*left_fork;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	uint				n_philo;
	uint				time_to_die;
	uint				time_to_eat;
	uint				time_to_nap;
	int					servings;
	uint				time_start;
	uint				flag_end;
	pthread_mutex_t	write_lock;
	t_fork				*forks;
	t_philo				*philosophers;
	uint				all_threads_ready;
	uint	thread_count;
	pthread_mutex_t 	table_lock;
	pthread_t			monitor;
}						t_table;



void					init_table(t_table *table);


void					fork_destroy(pthread_mutex_t *mutex);
void					fork_init(pthread_mutex_t *mutex);
void					fork_unlock(pthread_mutex_t *mutex);
void					fork_lock(pthread_mutex_t *mutex);

void write_uint(pthread_mutex_t *mutex, uint *dest, uint val);
uint read_uint(pthread_mutex_t *mutex, uint *val);
uint simulation_finished(t_table *table);
void					exit_print(const char *s);
void set_table(t_table *table, char **av);

void wait_all_threads(t_table *table);
uint gettime(t_time_code time_code);
void mprint(t_status status, t_philo *philo);
void start_table(t_table *table);

#endif

/*
TOOLS for this project
malloc -------------- Allocates memory on the heap.
free ---------------- Frees previously allocated memory.
write --------------- Low-level write to a file descriptor.
usleep -------------- Sleep for microseconds.

gettimeofday -------- Get current time with microsecond precision.

pthread_create ------ Creates a new thread.
pthread_detach ------ Detaches a thread.
pthread_join -------- Waits for a thread to finish.
pthread_mutex_init -- Initializes a mutex.
pthread_mutex_destroy- Destroys a mutex.
pthread_mutex_lock -- Locks a mutex.
pthread_mutex_unlock- Unlocks a mutex.

	*/