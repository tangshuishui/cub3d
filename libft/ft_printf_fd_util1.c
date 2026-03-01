/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd_util1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:42:00 by hanwang           #+#    #+#             */
/*   Updated: 2025/09/05 00:13:55 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_n_fd(int fd, int n)
{
	long	num;
	int		len;
	int		i;

	num = (long)n;
	i = 0;
	if (n < 0)
	{
		num *= -1;
		i += ft_putchar_n_fd(fd, '-');
	}
	len = 1;
	while (num / len >= 10)
		len *= 10;
	while (len > 0)
	{
		i += ft_putchar_n_fd(fd, num / len + '0');
		num %= len;
		len /= 10;
	}
	return (i);
}

int	ft_putnbr_unsig_n_fd(int fd, unsigned int num)
{
	long	len;
	int		i;

	len = 1;
	i = 0;
	while (num / len >= 10)
		len *= 10;
	while (len > 0)
	{
		i += ft_putchar_n_fd(fd, (num / len + '0'));
		num %= len;
		len /= 10;
	}
	return (i);
}

int	ft_puthex_n_fd(int fd, unsigned int num)
{
	const char	*base = "0123456789abcdef";
	int			i;

	i = 0;
	if (num >= 16)
		i += ft_puthex_n_fd(fd, num / 16);
	i += ft_putchar_n_fd(fd, base[num % 16]);
	return (i);
}

int	ft_puthexupp_n_fd(int fd, unsigned int num)
{
	const char	*base = "0123456789ABCDEF";
	int			i;

	i = 0;
	if (num >= 16)
		i += ft_puthexupp_n_fd(fd, num / 16);
	i += ft_putchar_n_fd(fd, base[num % 16]);
	return (i);
}
