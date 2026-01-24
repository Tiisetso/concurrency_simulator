/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:02:05 by timurray          #+#    #+#             */
/*   Updated: 2026/01/23 18:03:24 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (!((ac == 5) || (ac == 6)))
		return (EXIT_FAILURE);
	
	set_table(&table, av);
	init_table(&table);
	start_table(&table);
	clean_table(&table);

	return (EXIT_SUCCESS);
}


/*

TODO: review number range
TODO: min max values
TODO: servings min?
TODO: Error handling on mutex and thread function calls.
TODO: Clean exit
TODO: Testing passthroughs
*/