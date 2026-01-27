/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 11:52:43 by timurray          #+#    #+#             */
/*   Updated: 2026/01/27 15:57:48 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mx_print(char *text, t_philo *philo)
{
	t_uint	elapsed;

	if (philo->full)
		return ;
	if (end_table(philo->table))
		return ;
	mx_lock(&philo->table->write_lock);
	elapsed = get_time_ms() - philo->table->time_start;
	if (end_table(philo->table))
	{
		mx_unlock(&philo->table->write_lock);
		return ;
	}
	printf("%lu %lu %s\n", elapsed, philo->i, text);
	mx_unlock(&philo->table->write_lock);
}
