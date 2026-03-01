/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalishi <yalishi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:07:12 by yshi              #+#    #+#             */
/*   Updated: 2025/06/20 13:25:53 by yalishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_space(char c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	num;

	sign = 1;
	num = 0;
	while (ft_is_space(*nptr))
		nptr ++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr ++;
	}
	while (ft_isdigit(*nptr))
	{
		num = num * 10 + (*nptr - '0');
		nptr ++;
	}
	return (sign * num);
}
