/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 12:10:31 by timurray          #+#    #+#             */
/*   Updated: 2026/01/31 15:06:25 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_mx *forks, t_uint i, t_uint n)
{
	if (i < (i + 1) % n)
	{
		philo->left_fork = &forks[i];
		philo->right_fork = &forks[(i + 1) % n];
	}
	else
	{
		philo->left_fork = &forks[(i + 1) % n];
		philo->right_fork = &forks[i];
	}
}

static int	init_philo(t_table *table)
{
	t_uint	i;

	i = 0;
	while (i < table->n_philo)
	{
		table->philos[i].i = i + 1;
		table->philos[i].full = 0;
		table->philos[i].servings = 0;
		table->philos[i].table = table;
		if (!mx_init(&table->philos[i].lock))
			return (return_error("Philosopher mutex init fail.", 0));
		table->n_philo_mx++;
		assign_forks(&table->philos[i], table->forks, i, table->n_philo);
		i++;
	}
	return (1);
}

static int	init_forks(t_table *table)
{
	t_uint	i;

	i = 0;
	while (i < table->n_philo)
	{
		if (!mx_init(&table->forks[i]))
			return (0);
		table->n_fork_mx++;
		i++;
	}
	return (1);
}

static void	init_table_values(t_table *table)
{
	table->flag_end = 0;
	table->all_threads_ready = 0;
	table->n_thread = 0;
	table->philos = NULL;
	table->n_philo_mx = 0;
	table->forks = NULL;
	table->n_fork_mx = 0;
	table->table_lock_init = false;
	table->write_lock_init = false;
}

int	init_table(t_table *table)
{
	init_table_values(table);
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->n_philo);
	if (!table->philos)
		return (return_error("malloc error philosophers", 0));
	if (!mx_init(&table->table_lock))
		return (return_error("Table mutex init fail", 0));
	table->table_lock_init = true;
	if (!mx_init(&table->write_lock))
		return (return_error("Table write mutex init fail", 0));
	table->write_lock_init = true;
	table->forks = (t_mx *)malloc(sizeof(t_mx) * table->n_philo);
	if (!table->forks)
		return (return_error("malloc error forks", 0));
	if (!init_forks(table))
		return (return_error("Fork mutexes init fail", 0));
	if (!init_philo(table))
		return (return_error("Init philo failed.", 0));
	return (1);
}
