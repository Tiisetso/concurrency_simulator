/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:02:08 by timurray          #+#    #+#             */
/*   Updated: 2026/01/12 16:07:48 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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

typedef unsigned int	uint;
typedef struct s_philosopher
{
	uint				i;
	uint				alive;
}						t_philosopher;

typedef struct s_table
{
	uint				philo_count;
	uint				time_to_die;
	uint				time_to_eat;
	uint				time_to_nap;
	uint				servings;
	uint				time_start;
	t_philosopher		*philosophers;
}						t_table;

// UTILS
int						ft_atoi_check(const char *nptr, int *num);
void					exit_print(const char *s);

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