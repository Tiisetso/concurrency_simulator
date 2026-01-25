/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 16:55:22 by timurray          #+#    #+#             */
/*   Updated: 2026/01/24 13:29:47 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thread_error(int status)
{
	if (status == 0)
		return ;
	if (status == EDEADLK)
		exit_print("Thread deadlock");
}

void	wait_all_threads(t_table *table)
{
	while (!read_t_uint(&table->table_lock, &table->all_threads_ready))
		usleep(1000);
}
