/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:50:56 by timurray          #+#    #+#             */
/*   Updated: 2026/01/27 12:23:27 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static const char	*valid_num(const char *s)
{
	t_uint		len;
	const char	*num;

	len = 0;
	while (ft_isspace(*s))
		s++;
	if (*s == '+')
		++s;
	else if (*s == '-')
		exit_print("Positive values only.");
	num = s;
	while (ft_isdigit(*s++))
		++len;
	if (len > 10)
		exit_print("Value is too large.");
	return (num);
}

static t_uint	ft_atoi(const char *s)
{
	t_uint	num;

	num = 0;
	s = valid_num(s);
	while (ft_isdigit(*s))
		num = (num * 10) + (*s++ - 48);
	if (num > INT_MAX) // TODO: make this smaller, INTMAX is unnecessary
		exit_print("INT MAX is the limit");
	return (num);
}

void	set_table(t_table *table, char **av)
{
	table->n_philo = ft_atoi(av[1]);
	table->time_to_die_us = ft_atoi(av[2]) * 1000;
	table->time_to_eat_us = ft_atoi(av[3]) * 1000;
	table->time_to_nap_us = ft_atoi(av[4]) * 1000;
	if (av[5])
		table->servings = ft_atoi(av[5]);
	else
		table->servings = -1;
}
