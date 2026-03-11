/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshi <yshi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:23:21 by yalishi           #+#    #+#             */
/*   Updated: 2026/02/22 14:42:20 by yshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *nptr)
{
	int		sign;
	long	num;

	sign = 1;
	num = 0;
	while (ft_is_space(*nptr))
		nptr ++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr++ == '-')
			sign *= -1;
	}
	while (ft_isdigit(*nptr))
	{
		if (num > (LONG_MAX - (*nptr - '0')) / 10)
		{
			if (sign == 1)
				return (LONG_MAX);
			else
				return (LONG_MIN);
		}
		num = num * 10 + (*nptr - '0');
		nptr ++;
	}
	return (sign * num);
}
