/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 17:54:35 by timurray          #+#    #+#             */
/*   Updated: 2026/01/18 18:02:22 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void write_uint(pthread_mutex_t *mutex, uint *dest, uint val)
{
	pthread_mutex_lock(mutex);
	*dest = val;
	pthread_mutex_unlock(mutex);
}

uint read_uint(pthread_mutex_t *mutex, uint *val)
{
	uint x;
	pthread_mutex_lock(mutex);
	x = *val;
	pthread_mutex_unlock(mutex);
	return x;	 
}

uint simulation_finished(t_table *table)
{
	return (read_uint(&table->table_lock, &table->flag_end));
}
