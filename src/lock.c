/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 17:54:35 by timurray          #+#    #+#             */
/*   Updated: 2026/01/25 17:22:34 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mx_set_uint(t_mx *mx, t_uint *dest, t_uint val)
{
	mx_lock(mx);
	*dest = val;
	mx_unlock(mx);
}

t_uint	mx_get_uint(t_mx *mx, t_uint *val)
{
	t_uint	x;

	mx_lock(mx);
	x = *val;
	mx_unlock(mx);
	return (x);
}

t_uint	simulation_finished(t_table *table)
{
	return (mx_get_uint(&table->table_lock, &table->flag_end));
}
