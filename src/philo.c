/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:02:05 by timurray          #+#    #+#             */
/*   Updated: 2026/01/12 13:32:05 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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