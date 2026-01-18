/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 12:10:31 by timurray          #+#    #+#             */
/*   Updated: 2026/01/18 13:13:28 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void get_forks(t_philo *philo, t_fork *forks, uint i, uint n)
{
	philo->left_fork = &forks[(i + 1) % n];
	philo->right_fork = &forks[i];
	if(philo->i % 2)
	{
		philo->left_fork = &forks[i];
		philo->right_fork = &forks[(i + 1) % n];
	}
}

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
        i++;
		get_forks(philo, table->forks, i, table->n_philo);
	}

}

void init_table(t_table *table)
{
	uint i;

	table->flag_end = 0;
	table->philosophers = (t_philo *)malloc(sizeof(t_philo) * table->n_philo);
	if(!table->philosophers)
		exit_print("malloc error philosophers");
	table->forks = (t_fork *)malloc(sizeof(t_fork) * table->n_philo);
		if(!table->forks)
			exit_print("malloc error forks");
	i = 0;
	while (i < table->n_philo)
	{
		fork_init(&table->forks[i].fork);
		table->forks->i = i;
		i++;
	}
	init_philo(table);
}
