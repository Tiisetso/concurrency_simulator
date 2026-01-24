/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 17:54:35 by timurray          #+#    #+#             */
/*   Updated: 2026/01/23 18:08:36 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_uint(t_mx *mx, uint *dest, uint val)
{
	mx_lock(mx);
	*dest = val;
	mx_unlock(mx);
}

uint	read_uint(t_mx *mx, uint *val)
{
	uint	x;

	mx_lock(mx);
	x = *val;
	mx_unlock(mx);
	return (x);
}

uint	simulation_finished(t_table *table)
{
	return (read_uint(&table->table_lock, &table->flag_end));
}
