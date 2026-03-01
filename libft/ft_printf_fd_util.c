/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:51:05 by hanwang           #+#    #+#             */
/*   Updated: 2025/09/05 00:26:10 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_n_fd(int fd, int c)
{
	return (write(fd, &c, 1));
}

int	ft_putstr_n_fd(int fd, char *s)
{
	if (!s)
		return (write(fd, "(null)", 6));
	return (write(fd, s, ft_strlen(s)));
}

static int	ft_putptrhex_n_fd(int fd, uintptr_t num)
{
	const char	*base = "0123456789abcdef";
	int			i;

	i = 0;
	if (num >= 16)
		i += ft_putptrhex_n_fd(fd, num / 16);
	i += ft_putchar_n_fd(fd, base[num % 16]);
	return (i);
}

int	ft_print_ptr_n_fd(int fd, void *ptr)
{
	int	i;

	if (!ptr)
		return (ft_putstr_n_fd(fd, "(nil)"));
	i = 0;
	i += ft_putstr_n_fd(fd, "0x");
	i += ft_putptrhex_n_fd(fd, (uintptr_t)ptr);
	return (i);
}
