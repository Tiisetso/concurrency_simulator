/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 12:10:28 by timurray          #+#    #+#             */
/*   Updated: 2026/01/22 11:50:56 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void accu_sleep(uint usec, t_table *table)
{
	uint start;
	uint elapsed;
	uint rem;

	start = gettime(MICSECOND);
	while(gettime(MICSECOND) - start < usec)
	{
		if(simulation_finished(table))
			break;
		elapsed = gettime(MICSECOND) - start;
		rem = usec - elapsed;
	}
	if(rem > 1000)
		usleep(usec/2);
	else
	{
		while(gettime(MICSECOND) - start < usec)
			;
	}
}

void eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	mprint(L_FORK, philo);
	pthread_mutex_lock(&philo->right_fork->fork);
	mprint(R_FORK, philo);
	
	write_uint(&philo->lock, &philo->last_meal_time,gettime(MILSECOND));
	philo->servings++;
	mprint(EAT, philo);
	accu_sleep(philo->table->time_to_eat, philo->table);
	if (philo->table->servings > 0 && philo->servings == philo->table->servings)
		write_uint(&philo->lock, &philo->full, 1);
	fork_unlock(&philo->left_fork->fork);
	fork_unlock(&philo->right_fork->fork);
}

void think(t_philo *philo)
{
	mprint(THINK, philo);
}

void increase_count(pthread_mutex_t *mutex, uint *num)
{
	pthread_mutex_lock(mutex);
	*num += 1;
	
	pthread_mutex_unlock(mutex);
}

void *mealtime(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;

	wait_all_threads(philo->table);

	write_uint(&philo->lock, &philo->last_meal_time, gettime(MILSECOND));

	increase_count(&philo->table->table_lock, &philo->table->thread_count);

	while(!simulation_finished(philo->table))
	{
		if(philo->full)
			break ;

		eat(philo);

		mprint(SLEEP, philo);
		accu_sleep(philo->table->time_to_nap, philo->table);
		
		think(philo);
	}
	
	return (NULL);
}

// void wait_all_threads(t_table *table)
// {
// 	while(!read_uint(&table->table_lock, &table->all_threads_ready))
// 	{
// 		;
// 	}
// }

uint all_threads_running(pthread_mutex_t *mutex, uint *threads, uint n_philo)
{
	uint val;

	val = 0;
	pthread_mutex_lock(mutex);
	if (*threads == n_philo)
		val = 1;
	pthread_mutex_unlock(mutex);
	return(val);
}

uint philo_death(t_philo *philo)
{
	uint elapsed;
	uint die_time;

	if (read_uint(&philo->lock, &philo->full))
		return (0);

	elapsed = gettime(MILSECOND) - read_uint(&philo->lock, &philo->last_meal_time);
	die_time = philo->table->time_to_die / 1000;
	if(elapsed > die_time)
		return (1);
	return (0);
}

void *monitor_meal(void *data)
{
	t_table *table;
	uint i;


	table = (t_table *)data;
	while(!all_threads_running(&table->table_lock,&table->thread_count, table->n_philo  ))
	{
		;
	}

	i = 0;
	while(!simulation_finished(table))
	{
		i = 0;
		uint full_count = 0;
		while(i < table->n_philo && !simulation_finished(table))
		{
			if (philo_death(table->philosophers + i))
			{
				write_uint(&table->table_lock, &table->flag_end, 1);
				mprint(DIE, table->philosophers + i);
			}
			if (read_uint(&table->philosophers[i].lock, &table->philosophers[i].full))
				full_count++;
			i++;
		}
		if (full_count == table->n_philo)
		{
			write_uint(&table->table_lock, &table->flag_end, 1);
			return (NULL);
		}
	}
	
	return (NULL);
}

void *one_philo(void *av)
{
	t_philo *philo;

	philo = (t_philo *)av;
	wait_all_threads(philo->table);
	write_uint(&philo->lock, &philo->last_meal_time, gettime(MILSECOND));
	increase_count(&philo->table->table_lock, &philo->table->thread_count);
	mprint(L_FORK, philo);
	while(!simulation_finished(philo->table))
		usleep(200);
	return (NULL);
}

void start_table(t_table *table)
{
	uint i;

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

	table->time_start = gettime(MILSECOND);

	write_uint(&table->table_lock, &table->all_threads_ready, 1);

	i = -1;
	while(++i < table->n_philo)
	{
		pthread_join(table->philosophers[i].thread_i, NULL);
	}
	pthread_join(table->monitor, NULL);
	
}