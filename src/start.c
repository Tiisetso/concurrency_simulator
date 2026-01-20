/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 12:10:28 by timurray          #+#    #+#             */
/*   Updated: 2026/01/20 14:43:13 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *mealtime(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;

	wait_all_threads(philo->table);
	
	return (NULL);
}

void start_table(t_table *table)
{
	uint i;

	if (table->servings == 0)
		return ;
	else if (table->servings == 1)
		;
	else
	{
		while (i < table->n_philo)
		{
				pthread_create(&table->philosophers[i].thread_i, NULL, &table->philosophers[i], mealtime);
				i++;
		}
	}
	table->time_start = gettime(MILSECOND);

	write_uint(&table->table_lock, &table->all_threads_ready, 1);

	i = -1;
	while(++i < table->n_philo)
	{
		pthread_join(&table->philosophers[i].thread_i, NULL);
	}
	
}