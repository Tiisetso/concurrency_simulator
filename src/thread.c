/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 16:55:22 by timurray          #+#    #+#             */
/*   Updated: 2026/01/31 16:37:20 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_table *table)
{
	while (!mx_get_uint(&table->table_lock, &table->all_threads_ready))
		usleep(50);
}

int td_create(t_td *thread, void *(*func)(void *), void *data)
{
	if (pthread_create(thread, NULL, func, data) != 0)
		return (1);
	return (0);
}

int	td_join(t_td thread)
{
	if (pthread_join(thread, NULL) != 0)
		return (1);
	return (0);
}
void	clean_failed_threads(t_table *table, t_uint n)
{
	t_uint	i;

	mx_set_uint(&table->table_lock, &table->flag_end, 1);
	mx_set_uint(&table->table_lock, &table->all_threads_ready, 1);
	i = 0;
	while (i < n)
	{
		td_join(table->philos[i].thread);
		i++;
	}
}