/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:02:08 by timurray          #+#    #+#             */
/*   Updated: 2025/12/07 14:20:08 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

#endif

/*
TOOLS for this project
SUMMARY OF FUNCTIONS + REQUIRED HEADERS

memset -------------- Sets a block of memory to a byte value.
	#include <string.h>

printf -------------- Formatted output to stdout.
	#include <stdio.h>

malloc -------------- Allocates memory on the heap.
free ---------------- Frees previously allocated memory.
	#include <stdlib.h>

write --------------- Low-level write to a file descriptor.
usleep -------------- Sleep for microseconds.
	#include <unistd.h>

gettimeofday -------- Get current time with microsecond precision.
	#include <sys/time.h>

pthread_create ------ Creates a new thread.
pthread_detach ------ Detaches a thread.
pthread_join -------- Waits for a thread to finish.
pthread_mutex_init -- Initializes a mutex.
pthread_mutex_destroy- Destroys a mutex.
pthread_mutex_lock -- Locks a mutex.
pthread_mutex_unlock- Unlocks a mutex.
	#include <pthread.h>

 */