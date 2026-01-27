/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:50:56 by timurray          #+#    #+#             */
/*   Updated: 2026/01/27 19:11:43 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_valid_num(char *s)
{
	unsigned int	i;
	int				num;

	i = 0;
	while (i < ft_strlen(s))
	{
		if (!(s[i] == '-' || s[i] == '+' || ft_isdigit(s[i])))
			exit_print("Integers only.");
		i++;
	}
	if (ft_atoi_check(s, &num) == 0)
	{
		print_usage();
		exit(EXIT_FAILURE);
	}
	return (num);
}

static t_uint	get_philo_count(int n)
{
	if (n > PHILO_MAX)
		exit_print("Maximum 200 philosophers.");
	if (n < PHILO_MIN)
		exit_print("At least 1 philosopher.");
	return ((t_uint)n);
}

static t_uint	get_param_us(int num)
{
	t_uint	time_us;

	if (num < DURATION_MIN)
		exit_print("Parameter duration: >= 60 ms.");
	time_us = (t_uint)num * 1000;
	return (time_us);
}

static t_uint get_cognition_us(t_table *table)
{
	t_uint time_to_think_us;

	time_to_think_us = (table->time_to_die_us - table->time_to_eat_us - table->time_to_nap_us) / 2;
	if (time_to_think_us < 0)
		time_to_think_us = 0;
	return (time_to_think_us);
}

void	set_table(t_table *table, char **av)
{
	table->n_philo = get_philo_count(get_valid_num(av[1]));
	table->time_to_die_us = get_param_us(get_valid_num(av[2]));
	table->time_to_eat_us = get_param_us(get_valid_num(av[3]));
	table->time_to_nap_us = get_param_us(get_valid_num(av[4]));
	table->time_to_cog_us = get_cognition_us(table);
	if (av[5])
		table->servings = (t_uint)get_valid_num(av[5]);
	else
		table->servings = 0;
}
