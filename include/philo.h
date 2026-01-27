/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:02:08 by timurray          #+#    #+#             */
/*   Updated: 2026/01/27 17:51:48 by timurray         ###   ########.fr       */
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

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

# define PHILO_MAX 200
# define PHILO_MIN 1
# define DURATION_MIN 60

typedef uint64_t		t_uint;
typedef pthread_mutex_t	t_mx;
typedef pthread_t		t_td;

typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

typedef struct s_fork
{
	pthread_mutex_t		fork;
	t_uint				i;
}						t_fork;
typedef struct s_philo
{
	t_uint				i;
	int					servings;
	t_uint				last_meal_time;
	t_uint				full;
	t_td				thread_i;
	t_mx				lock;
	t_fork				*right_fork;
	t_fork				*left_fork;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	int					servings;
	t_uint				n_philo;
	t_uint				time_to_die_us;
	t_uint				time_to_eat_us;
	t_uint				time_to_nap_us;
	t_uint				time_to_cog_us;
	t_uint				time_start;
	t_uint				flag_end;
	t_fork				*forks;
	t_philo				*philosophers;
	t_uint				all_threads_ready;
	t_uint				thread_count;
	t_mx				write_lock;
	t_mx				table_lock;
	t_td				monitor;
}						t_table;

void					init_table(t_table *table);

void					mx_destroy(t_mx *mutex);
void					mx_init(t_mx *mutex);
void					mx_unlock(t_mx *mutex);
void					mx_lock(t_mx *mutex);

void					mx_set_uint(t_mx *mutex, t_uint *dest, t_uint val);
t_uint					mx_get_uint(t_mx *mutex, t_uint *val);
t_uint					end_table(t_table *table);
void					exit_print(const char *s);
void					set_table(t_table *table, char **av);

void					wait_all_threads(t_table *table);

void					start_table(t_table *table);
void					clean_table(t_table *table);

void					mx_print(char *text, t_philo *philo);

t_uint					get_time_ms(void);
t_uint					get_time_us(void);

void					sleep_stage(t_uint duration_us, t_table *table);
void					increase_count(t_mx *mutex, t_uint *num);
t_uint					philo_death(t_philo *philo, t_uint current_time);

void					*one_philo(void *av);
void					eat(t_philo *philo);
void					think(t_philo *philo);

int						ft_isspace(char c);
int						ft_isdigit(char c);
unsigned int			ft_strlen(const char *s);
int						ft_atoi_check(const char *nptr, int *num);
unsigned int			ft_strlen(const char *s);
void					print_usage(void);

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