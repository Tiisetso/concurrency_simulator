/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:02:05 by timurray          #+#    #+#             */
/*   Updated: 2026/01/27 14:32:53 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (!((ac == 5) || (ac == 6)))
	{
		print_usage();
		return (EXIT_FAILURE);
	}
	set_table(&table, av);
	init_table(&table);
	start_table(&table);
	clean_table(&table);
	return (EXIT_SUCCESS);
}

/*

./philo 5 610 200 100 10
./philo 5 800 200 200 10
./philo 5 610 200 200 10
PASSING
FAILING
./philo 199 610 200 200 10 
./philo 5 800 200 200 7
./philo 5 600 150 150
./philo 3 200 65 65 5
./philo 131 610 200 100 10
./philo 199 610 200 200 10
./philo 200 130 60 60

./philo 


TODO: Error handling on mutex and thread function calls.
TODO: Testing sessions
TODO: death detection delay
TODO: check unused fields
*/