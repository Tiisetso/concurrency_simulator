/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_start_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 15:45:06 by timurray          #+#    #+#             */
/*   Updated: 2026/01/31 17:02:15 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_uint	end_table(t_table *table)
{
	return (mx_get_uint(&table->table_lock, &table->flag_end));
}

int	death_check(t_table *table, t_uint i)
{
	t_uint	current_time_ms;
	t_uint	elapsed;

	current_time_ms = get_time_ms();
	if (philo_death(table->philos + i, current_time_ms))
	{
		mx_lock(&table->write_lock);
		mx_set_uint(&table->table_lock, &table->flag_end, 1);
		elapsed = current_time_ms - table->time_start;
		printf("%lu %lu %s\n", elapsed, table->philos[i].i, DIE);
		mx_unlock(&table->write_lock);
		return (1);
	}
	return (0);
}

int	full_check(t_table *table, t_uint *full_count)
{
	if (*full_count == table->n_philo)
	{
		mx_set_uint(&table->table_lock, &table->flag_end, 1);
		return (1);
	}
	return (0);
}
