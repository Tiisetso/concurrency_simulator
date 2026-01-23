/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 12:51:10 by timurray          #+#    #+#             */
/*   Updated: 2026/01/23 18:00:40 by timurray         ###   ########.fr       */
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

void	fork_lock(pthread_mutex_t *mutex)
{
	mutex_error(pthread_mutex_lock(mutex));
}

void	fork_unlock(pthread_mutex_t *mutex)
{
	mutex_error(pthread_mutex_unlock(mutex));
}

void	fork_init(pthread_mutex_t *mutex)
{
	mutex_error(pthread_mutex_init(mutex, NULL));
}

void	fork_destroy(pthread_mutex_t *mutex)
{
	mutex_error(pthread_mutex_destroy(mutex));
}
