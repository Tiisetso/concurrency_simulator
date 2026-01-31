/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 12:10:53 by timurray          #+#    #+#             */
/*   Updated: 2026/01/31 17:06:25 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_table(t_table *table)
{
	if (table->philos)
	{
		while (table->n_philo_mx > 0)
			mx_destroy(&table->philos[--table->n_philo_mx].lock);
	}
	if (table->forks)
	{
		while (table->n_fork_mx > 0)
			mx_destroy(&table->forks[--table->n_fork_mx]);
	}
	if (table->table_lock_init)
		mx_destroy(&table->table_lock);
	if (table->write_lock_init)
		mx_destroy(&table->write_lock);
	if (table->forks)
	{
		free(table->forks);
		table->forks = NULL;
	}
	if (table->philos)
	{
		free(table->philos);
		table->philos = NULL;
	}
}
