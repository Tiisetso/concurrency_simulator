/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:50:56 by timurray          #+#    #+#             */
/*   Updated: 2026/01/31 13:56:32 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_valid_num(char *s)
{
	unsigned int	i;
	int				num;

	if (!s || s[0] == '\0')
		return (-1);
	i = 0;
	if (s[i] == '+')
		i++;
	else if (s[i] == '-')
		return (-1);
	if (s[i] == '\0' || !ft_isdigit(s[i]))
		return (-1);
	while (s[i] != '\0')
	{
		if (!ft_isdigit(s[i]))
			return (-1);
		i++;
	}
	if (ft_atoi_check(s, &num) == 0)
		return (-1);
	return (num);
}

static int	get_philo_count(t_uint *param, int n)
{
	if (n < 0)
		return (return_error("Positive integers only.", 0));
	if (n > PHILO_MAX)
		return (return_error("Maximum 200 philosophers.", 0));
	if (n < PHILO_MIN)
		return (return_error("At least 1 philosopher.", 0));
	*param = (t_uint)n;
	return (1);
}

static int	get_param_us(t_uint *param, int n)
{
	if (n < 0)
		return (return_error("Positive integers only.", 0));
	if (n < DURATION_MIN)
		return (return_error("Parameter duration: >= 60 ms.", 0));
	*param = (t_uint)n * 1000;
	return (1);
}

static t_uint	get_cognition_us(t_table *table)
{
	t_uint	time_to_think_us;

	if (table->n_philo % 2 == 0)
	{
		time_to_think_us = 0;
		return (time_to_think_us);
	}
	time_to_think_us = table->time_to_die_us;
	if (time_to_think_us <= table->time_to_eat_us)
		return (0);
	time_to_think_us -= table->time_to_eat_us;
	if (time_to_think_us <= table->time_to_nap_us)
		return (0);
	time_to_think_us -= table->time_to_nap_us;
	return (time_to_think_us / 2);
}

int	set_table(t_table *table, int ac, char **av)
{
	int	servings;

	if (!((ac == 5) || (ac == 6)))
		return (0);
	if (!get_philo_count(&table->n_philo, get_valid_num(av[1])))
		return (0);
	if (!get_param_us(&table->time_to_die_us, get_valid_num(av[2])))
		return (0);
	if (!get_param_us(&table->time_to_eat_us, get_valid_num(av[3])))
		return (0);
	if (!get_param_us(&table->time_to_nap_us, get_valid_num(av[4])))
		return (0);
	table->time_to_cog_us = get_cognition_us(table);
	if (av[5] != NULL)
	{
		servings = get_valid_num(av[5]);
		if (servings < 1)
			return (return_error("Optional servings: 1 or more.", 0));
		table->servings = (t_uint)servings;
	}
	else
		table->servings = (t_uint)0;
	return (1);
}
