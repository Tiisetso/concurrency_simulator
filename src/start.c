/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 12:10:28 by timurray          #+#    #+#             */
/*   Updated: 2026/01/26 00:29:57 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void eat(t_philo *philo)
{
	mx_lock(&philo->left_fork->fork);
	mx_print(FORK, philo);
	mx_lock(&philo->right_fork->fork);
	mx_print(FORK, philo);
	
	mx_set_uint(&philo->lock, &philo->last_meal_time, get_time_ms());
	philo->servings++;
	mx_print(EAT, philo);
	micro_sleep(philo->table->time_to_eat, philo->table);
	if (philo->table->servings > 0 && philo->servings == philo->table->servings)
		mx_set_uint(&philo->lock, &philo->full, 1);
	mx_unlock(&philo->left_fork->fork);
	mx_unlock(&philo->right_fork->fork);
}

void think(t_philo *philo)
{
	mx_print(THINK, philo);
}

void increase_count(t_mx *mutex, t_uint *num)
{
	mx_lock(mutex);
	*num += 1;
	mx_unlock(mutex);
}

void *mealtime(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;

	wait_all_threads(philo->table);
	if (philo->table->n_philo < 50)
		usleep(1000 * philo->i);
	else if (philo->i % 2 == 0)
		usleep(5000);

	mx_set_uint(&philo->lock, &philo->last_meal_time, get_time_ms());

	increase_count(&philo->table->table_lock, &philo->table->thread_count);

	think(philo); //TODO: improve on this.
	while(!simulation_finished(philo->table))
	{
		if(philo->full)
			break ;

		eat(philo);

		mx_print(SLEEP, philo);
		micro_sleep(philo->table->time_to_nap, philo->table);
		
		think(philo);
	}
	
	return (NULL);
}

t_uint all_threads_running(t_mx *mutex, t_uint *threads, t_uint n_philo)
{
	t_uint val;

	val = 0;
	mx_lock(mutex);
	if (*threads == n_philo)
		val = 1;
	mx_unlock(mutex);
	return(val);
}

t_uint philo_death(t_philo *philo, t_uint current_time)
{
	t_uint elapsed;
	t_uint die_time;

	if (mx_get_uint(&philo->lock, &philo->full))
		return (0);

	elapsed = current_time - mx_get_uint(&philo->lock, &philo->last_meal_time);
	die_time = philo->table->time_to_die / 1000;
	if(elapsed > die_time)
		return (1);
	return (0);
}

void *monitor_meal(void *data)
{
	t_table *table;
	t_uint i;
	t_uint current_time;

	table = (t_table *)data;
	while(!all_threads_running(&table->table_lock,&table->thread_count, table->n_philo  ))
	{
		usleep(1000); // TODO: replace with usleep
	}

	i = 0;
	while(!simulation_finished(table))
	{
		i = 0;
		t_uint full_count = 0;
		current_time = get_time_ms();
		while(i < table->n_philo && !simulation_finished(table))
		{
			if (philo_death(table->philosophers + i, current_time))
			{
				usleep(500);
				current_time = get_time_ms();
				if (philo_death(table->philosophers + i, current_time))
				{
					mx_lock(&table->write_lock);
					mx_set_uint(&table->table_lock, &table->flag_end, 1);
					t_uint elapsed;
					elapsed = current_time - table->time_start;
					printf("%llu %llu %s\n", elapsed, table->philosophers[i].i, DIE);
					mx_unlock(&table->write_lock);
				}
			}
			if (mx_get_uint(&table->philosophers[i].lock, &table->philosophers[i].full))
				full_count++;
			i++;
		}
		if (full_count == table->n_philo)
		{
			mx_set_uint(&table->table_lock, &table->flag_end, 1);
			return (NULL);
		}
		usleep(500); // TODO: check value
	}
	
	return (NULL);
}

void *one_philo(void *av)
{
	t_philo *philo;

	philo = (t_philo *)av;
	wait_all_threads(philo->table);
	mx_set_uint(&philo->lock, &philo->last_meal_time, get_time_ms());
	increase_count(&philo->table->table_lock, &philo->table->thread_count);
	mx_print(FORK, philo);
	while(!simulation_finished(philo->table))
		usleep(200);
	return (NULL);
}

void start_table(t_table *table)
{
	t_uint i;

	i = 0;
	if (table->servings == 0)
		return ;
	else if (table->n_philo == 1)
		pthread_create(&table->philosophers[0].thread_i, NULL, one_philo, &table->philosophers[0]);
	else
	{
		while (i < table->n_philo)
		{
			pthread_create(&table->philosophers[i].thread_i, NULL, mealtime, &table->philosophers[i]);
			i++;
		}
	}

	pthread_create(&table->monitor, NULL, monitor_meal, table);
 
	table->time_start = get_time_ms();

	mx_set_uint(&table->table_lock, &table->all_threads_ready, 1);

	i = -1;
	while(++i < table->n_philo)
	{
		pthread_join(table->philosophers[i].thread_i, NULL);
	}
	pthread_join(table->monitor, NULL);
	
}
