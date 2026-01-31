/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:02:05 by timurray          #+#    #+#             */
/*   Updated: 2026/01/31 17:04:04 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (!set_table(&table, ac, av))
	{
		print_usage();
		return (EXIT_FAILURE);
	}
	if (!init_table(&table))
	{
		destroy_table(&table);
		return (EXIT_FAILURE);
	}
	if (!start_table(&table))
	{	
		//TODO: clean!
		destroy_table(&table);
		return (EXIT_FAILURE);
	}
	// clean_table(&table);
	destroy_table(&table);
	return (EXIT_SUCCESS);
}

/*
./philo 200 130 60 60

SHOULD LIVE
./philo 5 610 200 100 10
./philo 5 800 200 200 10
./philo 5 610 200 200 10
./philo 200 130 60 60
./philo 5 600 150 150
./philo 199 610 200 200 10
./philo 131 610 200 100 10
./philo 3 200 65 65 5
./philo 198 800 200 200 10
./philo 200 130 60 60 10

SHOULD DIE
./philo 2 100 60 60 5
./philo 2 100 100 100 5
./philo 2 800 700 110 2
./philo 3 61 60 60 5
./philo 4 190 100 100 5
./philo 5 90 60 60 3
./philo 10 199 100 100 10

./philo 101 180 60 60 10

./philo 199 610 200 200 10

SHOULD DIE:
./philo 31 599 200 200 10

stagger with more
Then start with thinking

TODO: no exit allowed!!!

TODO: Error handling on mutex and thread function calls.
TODO: potential max duration?
TODO: Testing sessions
TODO: death detection delay
TODO: check unused fields
*/