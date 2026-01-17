/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 12:10:31 by timurray          #+#    #+#             */
/*   Updated: 2026/01/17 16:53:11 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void get_forks(t_philo *phill)

void init_philo(t_table *table)
{
	uint i;
	t_philo *philo;

	i = 0;
	while(i < table->n_philo)
	{
		philo = table->philosophers + i;
		philo->i = i + 1;
		philo->full = 0;
		philo->servings = 0;
		philo->table = table;

		get_forks(philo, table->forks, i);
	}

}

void init_table(t_table *table)
{
	uint i;

	table->flag_end = 0;
	table->philosophers = (t_philo *)malloc(sizeof(t_philo) * table->n_philo);
	table->forks = (t_fork *)malloc(sizeof(t_fork) * table->n_philo);
	i = 0;
	while (i < table->n_philo)
	{
		fork_init(&table->forks[i].fork);
		table->forks->i = i;
		i++;
	}
	init_philo(table);
}
