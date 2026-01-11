/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 17:03:53 by timurray          #+#    #+#             */
/*   Updated: 2026/01/11 17:01:22 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	ft_atoi(const *s)
// {
// 	int	i;
// 	int	sign;
// 	int	n;
// 	int	digit;

// 	i = 0;
// 	sign = 1;
// 	n = 0;
// 	while (ft_isspace(s[i]))
// 		i++;
// 	if (s[i] == '-' || s[i] == '+')
// 	{
// 		if (s[i++] == '-')
// 			sign = -1;
// 	}
// 	while (ft_isdigit(s[i]))
// 	{
// 		digit = s[i] - '0';
// 		if (n > INT_MAX / 10 || (n == INT_MAX / 10 && digit > INT_MAX % 10))
// 		{
// 			if (sign == 1)
// 				return (INT_MAX);
// 			else
// 				return (INT_MIN);
// 		}
// 		n = n * 10 + digit;
// 		i++;
// 	}
// 	return (n * sign);
// }

static int	limit_check(long long n, int sign, int digit);

uint	ft_atoi_check(const char *nptr, int *num)
{
	int			sign;
	long long	n;
	int			i;
	int			digit;

	sign = 1;
	n = 0;
	i = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i++] == '-')
			sign = -1;
	}
	while (ft_isdigit(nptr[i]))
	{
		digit = nptr[i++] - '0';
		if (!limit_check(n, sign, digit))
			return (0);
		n = (n * 10) + digit;
	}
	*num = (int)(sign * n);
	return (1);
}

static int	limit_check(long long n, int sign, int digit)
{
	long long	limit;

	if (sign > 0)
		limit = (long long)INT_MAX;
	else
		limit = -(long long)INT_MIN;
	if (n > (limit - digit) / 10)
		return (0);
	return (1);
}