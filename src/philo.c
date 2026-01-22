/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:02:05 by timurray          #+#    #+#             */
/*   Updated: 2026/01/22 10:53:36 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (!((ac == 5) || (ac == 6)))
		return (EXIT_FAILURE);
	
	set_table(&table, av); //TODO: review number range
	init_table(&table);
	start_table(&table);
	// clean_table(&table);

	return (EXIT_SUCCESS);
}


/*
Atomics are essentially incorrect.
EAT
SLEEP
THINK // No time associated
DIE

min max values
servings min?
Error handling on mutex and thread function calls.
Clean exit
Testing?
*/