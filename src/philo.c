/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:02:05 by timurray          #+#    #+#             */
/*   Updated: 2026/01/31 17:13:54 by timurray         ###   ########.fr       */
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
		destroy_table(&table);
		return (EXIT_FAILURE);
	}
	destroy_table(&table);
	return (EXIT_SUCCESS);
}
