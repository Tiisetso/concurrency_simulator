/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 12:10:28 by timurray          #+#    #+#             */
/*   Updated: 2026/01/31 17:01:11 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*mealtime(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	if (philo->i % 2 == 0)
		usleep(5000);
	else if (philo->table->n_philo % 2 != 0 && philo->i == 1)
		usleep(5000);
	mx_set_uint(&philo->lock, &philo->last_meal_time_ms, get_time_ms());
	increase_count(&philo->table->table_lock, &philo->table->n_thread);
	while (!end_table(philo->table))
	{
		if (mx_get_uint(&philo->lock, &philo->full))
			return (NULL);
		eat(philo);
		philo_sleep(philo);
		think(philo);
	}
	return (NULL);
}

void	*monitor_meal(void *data)
{
	t_table	*table;
	t_uint	i;
	t_uint	full_count;

	table = (t_table *)data;
	while (mx_get_uint(&table->table_lock, &table->n_thread) < table->n_philo)
		usleep(1000);
	while (!end_table(table))
	{
		i = 0;
		full_count = 0;
		while (i < table->n_philo && !end_table(table))
		{
			if (death_check(table, i))
				return (NULL);
			if (mx_get_uint(&table->philos[i].lock, &table->philos[i].full))
				full_count++;
			i++;
		}
		if (full_check(table, &full_count))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

static int	create_philo_threads(t_table *t, t_uint *i)
{
	if (t->n_philo == 1)
	{
		if (td_create(&t->philos[0].thread, one_philo, &t->philos[0]) != 0)
			return (return_error("1 philosopher thread creation error.", 0));
		(*i)++;
	}
	else
	{
		while (*i < t->n_philo)
		{
			if (td_create(&t->philos[*i].thread, mealtime, &t->philos[*i]) != 0)
			{
				clean_failed_threads(t, *i);
				return (return_error("Philosopher thread creation error.", 0));
			}
			(*i)++;
		}
	}
	return (1);
}

int	start_table(t_table *table)
{
	t_uint	i;

	table->time_start = get_time_ms();
	i = 0;
	if (!create_philo_threads(table, &i))
		return (0);
	if (td_create(&table->monitor, monitor_meal, table) != 0)
	{
		clean_failed_threads(table, i);
		return (return_error("Monitor thread creation failure.", 0));
	}
	mx_set_uint(&table->table_lock, &table->all_threads_ready, 1);
	i = 0;
	while (i < table->n_philo)
	{
		td_join(table->philos[i].thread);
		i++;
	}
	td_join(table->monitor);
	return (0);
}
