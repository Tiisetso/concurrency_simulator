/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:28:57 by timurray          #+#    #+#             */
/*   Updated: 2026/01/26 14:35:18 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *one_philo(void *av)
{
	t_philo *philo;

	philo = (t_philo *)av;
	wait_all_threads(philo->table);
	mx_set_uint(&philo->lock, &philo->last_meal_time, get_time_ms());
	increase_count(&philo->table->table_lock, &philo->table->thread_count);
	mx_print(FORK, philo);
	while(!end_table(philo->table))
		usleep(200);
	return (NULL);
}
