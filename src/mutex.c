/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 12:51:10 by timurray          #+#    #+#             */
/*   Updated: 2026/01/23 18:08:57 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_error(int status)
{
	if (status == 0)
		return ;
	else if (status == EBUSY)
		exit_print("mutex is locked");
	else if (status == EDEADLK)
		exit_print("mutex is deadlocked");
	else
		exit_print("mutex error");
}

void	mx_lock(t_mx *mutex)
{
	mutex_error(pthread_mutex_lock(mutex));
}

void	mx_unlock(t_mx *mutex)
{
	mutex_error(pthread_mutex_unlock(mutex));
}

void	mx_init(t_mx *mutex)
{
	mutex_error(pthread_mutex_init(mutex, NULL));
}

void	mx_destroy(t_mx *mutex)
{
	mutex_error(pthread_mutex_destroy(mutex));
}
