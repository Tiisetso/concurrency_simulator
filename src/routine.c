/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:09:01 by timurray          #+#    #+#             */
/*   Updated: 2026/01/27 17:57:56 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	mx_lock(&philo->left_fork->fork);
	mx_print(FORK, philo);
	mx_lock(&philo->right_fork->fork);
	mx_print(FORK, philo);
	philo->servings++;
	mx_print(EAT, philo);
	mx_set_uint(&philo->lock, &philo->last_meal_time, get_time_ms());
	sleep_stage(philo->table->time_to_eat_us, philo->table);
	if (philo->table->servings > 0 && philo->servings == philo->table->servings)
		mx_set_uint(&philo->lock, &philo->full, 1);
	mx_unlock(&philo->left_fork->fork);
	mx_unlock(&philo->right_fork->fork);
}

void	think(t_philo *philo)
{
	mx_print(THINK, philo);
	sleep_stage(philo->table->time_to_cog_us, philo->table);
	// think = death - eat - sleep / 2
	// think = 
	// if (philo->table->n_philo % 2 != 0)
	// usleep(100);
}

t_uint	philo_death(t_philo *philo, t_uint current_time)
{
	t_uint	elapsed;
	t_uint	die_time_ms;

	if (mx_get_uint(&philo->lock, &philo->full))
		return (0);
	elapsed = current_time - mx_get_uint(&philo->lock, &philo->last_meal_time);
	die_time_ms = philo->table->time_to_die_us / 1000;
	if (elapsed > die_time_ms)
		return (1);
	return (0);
}
