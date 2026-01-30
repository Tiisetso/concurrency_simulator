/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 17:15:46 by timurray          #+#    #+#             */
/*   Updated: 2026/01/30 21:12:53 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_print(const char *s)
{
	printf("%s\n", s);
	exit(EXIT_FAILURE);
}

int	return_error(const char *s, int err)
{
	unsigned int	len;

	len = ft_strlen(s);
	write(2, s, len);
	write(2, "\n", 1);
	return (err);
}

void	print_usage(void)
{
	printf("Usage:\n\n");
	printf("./philo <np> <td> <te> <ts> <ns>\n\n");
	printf("<np> number of philosophers: 1 - 200\n");
	printf("<td> time to die: > 60 ms\n");
	printf("<te> time to eat: > 60 ms\n");
	printf("<ts> time to sleep: > 60 ms\n");
	printf("<nv> number of servings per philosopher (optional): > 0\n\n");
}
