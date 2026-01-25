/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 11:52:43 by timurray          #+#    #+#             */
/*   Updated: 2026/01/26 00:29:42 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void mx_print(char *text, t_philo *philo)
{
	t_uint elapsed;

	if (philo->full)
		return ;

	if (simulation_finished(philo->table))
		return ;
	mx_lock(&philo->table->write_lock);
	elapsed = get_time_ms() - philo->table->time_start;
	if (simulation_finished(philo->table))
	{
		mx_unlock(&philo->table->write_lock);
		return ;
	}
	printf("%llu %llu %s\n", elapsed, philo->i, text);
	mx_unlock(&philo->table->write_lock);
}
