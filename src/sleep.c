/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 19:11:41 by timurray          #+#    #+#             */
/*   Updated: 2026/01/25 19:17:48 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	micro_sleep(t_uint usec, t_table *table)
{
	t_uint	start;
	t_uint	now;

	start = get_time_us();
	while (1)
	{
		if (simulation_finished(table))
			break ;
		now = get_time_us();
		if (now - start >= usec)
			break ;
		usleep(500);
	}
}
