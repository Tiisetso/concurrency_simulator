/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 19:11:41 by timurray          #+#    #+#             */
/*   Updated: 2026/01/27 15:58:00 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_stage(t_uint duration_us, t_table *table)
{
	t_uint	start_us;
	t_uint	now_us;

	start_us = get_time_us();
	while (1)
	{
		if (end_table(table))
			break ;
		now_us = get_time_us();
		if (now_us - start_us >= duration_us)
			break ;
		usleep(200);
	}
}
