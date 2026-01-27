/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:02:05 by timurray          #+#    #+#             */
/*   Updated: 2026/01/27 12:17:31 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (!((ac == 5) || (ac == 6)))
	{
		printf("Usage: ./philo philo_count etc.");
		return (EXIT_FAILURE);
	}
	set_table(&table, av);
	init_table(&table);
	start_table(&table);
	clean_table(&table);
	return (EXIT_SUCCESS);
}

/*
Edge test 

./philo 5 610 200 100 10

./philo 5 800 200 200 10
./philo 5 610 200 200 10
./philo 199 610 200 200 10 
./philo 5 800 200 200 7
./philo 5 600 150 150

./philo 131 610 200 100 10
./philo 199 610 200 200 10
./philo 

TODO: review number range, min max values
TODO: servings min?
TODO: Error handling on mutex and thread function calls.
TODO: Clean exit
TODO: Testing sessions
TODO: death detection delay
TODO: check unused fields
*/