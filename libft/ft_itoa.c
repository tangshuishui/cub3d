/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshi <yshi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:58:03 by yshi              #+#    #+#             */
/*   Updated: 2025/05/22 18:09:01 by yshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	count_digit(long n)
{
	size_t	len;

	len = 1;
	if (n < 0)
	{
		len ++;
		n *= -1;
	}
	while (n / 10 >= 1)
	{
		len ++;
		n = n / 10;
	}
	return (len);
}

void	itoa(char **str, long num)
{
	if (num < 0)
	{
		**str = '-';
		num *= -1;
		(*str)++;
	}
	if (num <= 9)
	{
		**str = num + '0';
		(*str)++;
	}
	else
	{
		itoa(str, num / 10);
		itoa(str, num % 10);
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	char	*ptr;
	long	num;

	num = (long)n;
	str = (char *)malloc(sizeof(char) * (count_digit(num) + 1));
	if (!str)
		return (NULL);
	ptr = str;
	itoa(&ptr, num);
	*ptr = '\0';
	return (str);
}
