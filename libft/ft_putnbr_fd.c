/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshi <yshi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:31:36 by yshi              #+#    #+#             */
/*   Updated: 2025/05/23 19:42:41 by yshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	ch;
	long	num;

	num = (long)n;
	if (num < 0)
	{
		write(fd, "-", 1);
		num *= -1;
	}
	if (num <= 9)
	{
		ch = num + '0';
		write(fd, &ch, 1);
	}
	else
	{
		ft_putnbr_fd(num / 10, fd);
		ft_putnbr_fd(num % 10, fd);
	}
}
