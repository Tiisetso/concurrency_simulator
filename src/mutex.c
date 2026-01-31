/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 12:51:10 by timurray          #+#    #+#             */
/*   Updated: 2026/01/31 11:18:16 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	mutex_error(int status)
{
	if (status == 0)
		return (1);
	else if (status == EBUSY)
		return (return_error("mutex is locked", 0));
	else if (status == EDEADLK)
		return (return_error("mutex is deadlocked", 0));
	else
		return (return_error("mutex error", 0));
}

int	mx_lock(t_mx *mutex)
{
	return (mutex_error(pthread_mutex_lock(mutex)));
}

int	mx_unlock(t_mx *mutex)
{
	return (mutex_error(pthread_mutex_unlock(mutex)));
}

int	mx_init(t_mx *mutex)
{
	return (mutex_error(pthread_mutex_init(mutex, NULL)));
}

int	mx_destroy(t_mx *mutex)
{
	return (mutex_error(pthread_mutex_destroy(mutex)));
}
