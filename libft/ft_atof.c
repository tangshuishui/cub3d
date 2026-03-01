/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalishi <yalishi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 16:39:13 by yalishi           #+#    #+#             */
/*   Updated: 2025/07/07 15:44:25 by yalishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	process_digits(const char *nptr)
{
	double	res;
	double	divisor;

	res = 0.0;
	divisor = 10.0;
	while (ft_isdigit(*nptr))
	{
		res = res * 10 + (*nptr - '0');
		nptr ++;
	}
	if (*nptr == '.')
	{
		nptr++;
		while (ft_isdigit(*nptr))
		{
			res += (*nptr - '0') / divisor;
			divisor *= 10.0;
			nptr++;
		}
	}
	return (res);
}

double	ft_atof(const char	*nptr)
{
	double	res;
	int		sign;

	sign = 1;
	while (ft_is_space(*nptr))
		nptr ++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr ++;
	}
	res = process_digits(nptr);
	return (sign * res);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char str[] = "-42.00123";

// 	printf("test: %f\n", atof(str));
// }
