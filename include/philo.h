/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:02:08 by timurray          #+#    #+#             */
/*   Updated: 2026/01/31 16:13:22 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdarg.h>
# include <stdbool.h>
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

typedef struct s_philo
{
	t_uint				i;
	t_uint				servings;
	t_uint				last_meal_time_ms;
	t_uint				full;
	t_td				thread;
	t_mx				lock;
	t_mx				*right_fork;
	t_mx				*left_fork;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	t_uint				servings;
	t_uint				n_philo;
	t_uint				time_to_die_us;
	t_uint				time_to_eat_us;
	t_uint				time_to_nap_us;
	t_uint				time_to_cog_us;
	t_uint				time_start;
	t_uint				flag_end;
	t_mx				*forks;
	t_uint				n_fork_mx;
	t_philo				*philos;
	t_uint				n_philo_mx;
	t_uint				all_threads_ready;
	t_uint				n_thread;
	t_mx				write_lock;
	bool				write_lock_init;
	t_mx				table_lock;
	bool				table_lock_init;
	t_td				monitor;
}						t_table;

int						set_table(t_table *table, int ac, char **av);
int						init_table(t_table *table);
int						start_table(t_table *table);
void					clean_table(t_table *table);

void					destroy_table(t_table *table);

int						mx_destroy(t_mx *mutex);
int						mx_init(t_mx *mutex);
int						mx_unlock(t_mx *mutex);
int						mx_lock(t_mx *mutex);

void					mx_set_uint(t_mx *mutex, t_uint *dest, t_uint val);
t_uint					mx_get_uint(t_mx *mutex, t_uint *val);
t_uint					end_table(t_table *table);
int						td_create(t_td *thread, void *(*func)(void *),
							void *data);
int						td_join(t_td thread);
t_uint					end_table(t_table *table);
int						return_error(const char *s, int err);

void					wait_all_threads(t_table *table);

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
void					philo_sleep(t_philo *philo);
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