/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:30:31 by timurray          #+#    #+#             */
/*   Updated: 2026/01/25 18:16:33 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_uint	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		exit_print("time of day failed");
	return ((t_uint)tv.tv_sec * 1000 + (t_uint)tv.tv_usec / 1000);
}

t_uint	get_time_us(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		exit_print("time of day failed");
	return ((t_uint)tv.tv_sec * 1000000 + (t_uint)tv.tv_usec);
}
