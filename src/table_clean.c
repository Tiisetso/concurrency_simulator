/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 12:10:53 by timurray          #+#    #+#             */
/*   Updated: 2026/01/30 22:30:30 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_table(t_table *table)
{
	t_uint	i;

	if (!table)
		return ;
	i = 0;
	while (i < table->n_philo)
	{
		mx_destroy(&table->forks[i]);
		mx_destroy(&table->philosophers[i].lock);
		i++;
	}
	mx_destroy(&table->write_lock);
	mx_destroy(&table->table_lock);
	if (table->forks)
		free(table->forks);
	if (table->philosophers)
		free(table->philosophers);
}
