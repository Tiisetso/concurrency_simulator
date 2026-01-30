/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 12:10:28 by timurray          #+#    #+#             */
/*   Updated: 2026/01/30 21:44:14 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_uint	end_table(t_table *table)
{
	return (mx_get_uint(&table->table_lock, &table->flag_end));
}



void	*mealtime(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	if (philo->table->n_philo < 50)
		usleep(1000 * philo->i);
	else
	{
		if (philo->i % 2 == 0)
			usleep(5000);
		else if (philo->table->n_philo % 2 != 0 && philo->i == 1)
			usleep(5000);
	}
	mx_set_uint(&philo->lock, &philo->last_meal_time, get_time_ms());
	increase_count(&philo->table->table_lock, &philo->table->thread_count);
	// think(philo); //TODO: improve on this.
	while (!end_table(philo->table))
	{
		if (philo->full)
			break ;
		// if(!end_table(philo->table))
		eat(philo);
		if(!end_table(philo->table))	
			philo_sleep(philo);
		if(!end_table(philo->table))	
			think(philo);
	}
	return (NULL);
}


void	*monitor_meal(void *data)
{
	t_table	*table;
	t_uint	i;
	t_uint	current_time;
	t_uint	full_count;
	t_uint elapsed;

	table = (t_table *)data;
	while(mx_get_uint(&table->table_lock, &table->thread_count) <  table->n_philo)
		usleep(1000);
	i = 0;
	while (!end_table(table))
	{
		i = 0;
		full_count = 0;
		current_time = get_time_ms();
		while (i < table->n_philo && !end_table(table))
		{
			if (philo_death(table->philosophers + i, current_time))
			{
				usleep(500);
				current_time = get_time_ms();
				if (philo_death(table->philosophers + i, current_time))
				{
					mx_lock(&table->write_lock);
					mx_set_uint(&table->table_lock, &table->flag_end, 1);
					elapsed = current_time - table->time_start;
					printf("%lu %lu %s\n", elapsed, table->philosophers[i].i,
						DIE);
					mx_unlock(&table->write_lock);
					return (NULL);
				}
			}
			if (mx_get_uint(&table->philosophers[i].lock,
					&table->philosophers[i].full))
				full_count++;
			i++;
		}
		if (full_count == table->n_philo)
		{
			mx_set_uint(&table->table_lock, &table->flag_end, 1);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

void clean_failed_threads(t_table *table, t_uint n)
{
	t_uint i;

	mx_set_uint(&table->table_lock, &table->flag_end, 1);
	mx_set_uint(&table->table_lock, &table->all_threads_ready, 1);

	i = 0;
	while(i < n)
	{
		pthread_join(table->philosophers[i].thread_i, NULL);
		i++;
	}
}


void	start_table(t_table *table)
{
	t_uint	i;

	table->time_start = get_time_ms();
	if (table->n_philo == 1)
	{
		if(pthread_create(&table->philosophers[0].thread_i, NULL, one_philo, &table->philosophers[0]) != 0)
			exit_print("Thread creation error.");
	}
	else
	{
		i = 0;
		while (i < table->n_philo)
		{
			if(pthread_create(&table->philosophers[i].thread_i, NULL, mealtime, &table->philosophers[i]) != 0)
			{
				clean_failed_threads(table, i);
				exit_print("Philosopher thread creation failure.");
			}
			i++;
		}
	}

	if(pthread_create(&table->monitor, NULL, monitor_meal, table) != 0)
	{
		clean_failed_threads(table, i);
		exit_print("Monitor thread creation failure.");
	}
	mx_set_uint(&table->table_lock, &table->all_threads_ready, 1);
	i = 0;
	while (i < table->n_philo)
	{
		pthread_join(table->philosophers[i].thread_i, NULL);
		i++;
	}
	pthread_join(table->monitor, NULL);
}
