/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 17:54:35 by timurray          #+#    #+#             */
/*   Updated: 2026/01/27 15:57:39 by timurray         ###   ########.fr       */
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

void	increase_count(t_mx *mutex, t_uint *num)
{
	mx_lock(mutex);
	*num += 1;
	mx_unlock(mutex);
}
