/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 11:52:43 by timurray          #+#    #+#             */
/*   Updated: 2026/01/24 13:30:48 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void mprint(t_status status, t_philo *philo)
{
	t_uint elapsed;

	elapsed = gettime(MILSECOND);
	if (philo->full)
		return ;

	mx_lock(&philo->table->write_lock);
	if ((status == L_FORK || status == R_FORK) && !simulation_finished(philo->table))
		printf("%lu %lu has taken a fork\n", elapsed - philo->table->time_start, philo->i);
	else if ((status == EAT && !simulation_finished(philo->table)))
		printf("%lu %lu is eating\n", elapsed - philo->table->time_start, philo->i);
	else if ((status == SLEEP && !simulation_finished(philo->table)))
		printf("%lu %lu is sleeping\n", elapsed - philo->table->time_start, philo->i);
	else if ((status == THINK && !simulation_finished(philo->table)))
		printf("%lu %lu is thinking\n", elapsed - philo->table->time_start, philo->i);
	else if (status == DIE)
		printf("%lu %lu died\n", elapsed - philo->table->time_start, philo->i);

	mx_unlock(&philo->table->write_lock);
}