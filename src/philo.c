/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:02:05 by timurray          #+#    #+#             */
/*   Updated: 2026/01/11 18:44:58 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_table(t_table *table, char **av)
{
	if (!ft_atoi_check(av[1], &table->number_of_philosophers))
		return (0);
	if (!ft_atoi_check(av[2], &table->time_to_die))
		return (0);
	if (!ft_atoi_check(av[3], &table->time_to_eat))
		return (0);
	if (!ft_atoi_check(av[4], &table->time_to_sleep))
		return (0);
	table->servings = 0;
	if (av[5])
	{
		if (!ft_atoi_check(av[1], &table->servings))
			return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (!((ac == 5) || (ac == 6)))
		return (EXIT_FAILURE);
	
	set_table(&table, av);
	// init_table(&table);
	// start_table(&table);
	// clean_table(&table);

	return (EXIT_SUCCESS);
}


/*
Everything needs to be locked and unlocked before changing. 
Mutexes are used for locking and unlocking.
Atomics are essentially incorrect.
*/