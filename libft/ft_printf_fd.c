/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:40:57 by hanwang           #+#    #+#             */
/*   Updated: 2025/09/05 00:34:30 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_format_fd(int fd, const char c, va_list args)
{
	int	len;

	len = 0;
	if (c == 'c')
		len += ft_putchar_n_fd(fd, va_arg(args, int));
	else if (c == 's')
		len += ft_putstr_n_fd(fd, va_arg(args, char *));
	else if (c == 'p')
		len += ft_print_ptr_n_fd(fd, va_arg(args, void *));
	else if (c == 'd' || c == 'i')
		len += ft_putnbr_n_fd(fd, va_arg(args, int));
	else if (c == 'u')
		len += ft_putnbr_unsig_n_fd(fd, va_arg(args, unsigned int));
	else if (c == 'x')
		len += ft_puthex_n_fd(fd, va_arg(args, unsigned int));
	else if (c == 'X')
		len += ft_puthexupp_n_fd(fd, va_arg(args, unsigned int));
	else if (c == '%')
		len += ft_putchar_n_fd(fd, '%');
	else
		len += ft_putchar_n_fd(fd, c);
	return (len);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	va_list	args;
	int		i;
	int		len;

	if (format == NULL)
		return (-1);
	i = 0;
	len = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			len += ft_format_fd(fd, format[i + 1], args);
			i += 2;
		}
		else if (format[i] != '%')
			len += ft_putchar_n_fd(fd, format[i++]);
		else
			i++;
	}
	va_end(args);
	return (len);
}
