/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 16:55:22 by timurray          #+#    #+#             */
/*   Updated: 2026/01/18 17:31:28 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void thread_error(int status)
{
	if (status == 0)
		return ;
	if (status == EDEADLK)
		exit_print("Thread deadlock");
}
