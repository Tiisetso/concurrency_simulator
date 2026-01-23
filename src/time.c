/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 13:30:31 by timurray          #+#    #+#             */
/*   Updated: 2026/01/23 18:01:27 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint	gettime(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		exit_print("time of day failed");
	if (SECOND == time_code)
		return (tv.tv_sec + (tv.tv_sec / 1000000));
	else if (MILSECOND == time_code)
		return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	else if (MICSECOND == time_code)
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	else
		exit_print("gettime failure");
	return (0);
}
