/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 12:10:28 by timurray          #+#    #+#             */
/*   Updated: 2026/01/21 16:38:10 by timurray         ###   ########.fr       */
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

void *mealtime(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;

	wait_all_threads(philo->table);

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

void start_table(t_table *table)
{
	uint i;

	i = 0;
	if (table->servings == 0)
		return ;
	else if (table->servings == 1)
		;
	else
	{
		while (i < table->n_philo)
		{
				pthread_create(&table->philosophers[i].thread_i, NULL, mealtime, &table->philosophers[i]);
				i++;
		}
	}
	table->time_start = gettime(MILSECOND);

	write_uint(&table->table_lock, &table->all_threads_ready, 1);

	i = -1;
	while(++i < table->n_philo)
	{
		pthread_join(table->philosophers[i].thread_i, NULL);
	}
	
}