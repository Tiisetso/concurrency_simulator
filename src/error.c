/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 17:15:46 by timurray          #+#    #+#             */
/*   Updated: 2026/01/27 14:31:51 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_print(const char *s)
{
	printf("%s\n", s);
	exit(EXIT_FAILURE);
}
void	print_usage(void)
{
	printf("Usage:\n");
	printf("./philo <n> <d> <e> <s> <v>\n");
	printf("n number of philosophers 1 - 200\n");
	printf("d time to die > 60 ms\n");
	printf("e time to eat> 60 ms\n");
	printf("s time to sleep > 60 ms\n");
	printf("v number of servings per philosopher > 0 (optional)\n");
}
