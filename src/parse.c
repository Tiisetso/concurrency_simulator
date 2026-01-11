/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 16:50:56 by timurray          #+#    #+#             */
/*   Updated: 2026/01/11 18:44:15 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || (c == 32))
		return (1);
	return (0);
}

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static const char	*valid_num(const char *s)
{
	uint len;
	const char *num;

	len = 0;
	while (ft_isspace(*s))
		s++;
	if (*s == '+')
		++s;
	else if (*s == '-')
		exit_print("Positive values only.");
	num = s;
	while(ft_isdigit(*s++))
		++len;
	if(len > 10)
		exit_print("Value is too large.");
	return (num);
}

