/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalishi <yalishi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:16:56 by yalishi           #+#    #+#             */
/*   Updated: 2025/06/17 13:47:38 by yalishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "handle_format/handle_format.h"

int	handle_format(char *format, va_list args)
{
	if (*format == 'c')
		return (handle_char(va_arg(args, int)));
	if (*format == 's')
		return (handle_str(va_arg(args, char *)));
	if (*format == 'p')
		return (handle_ptr(va_arg(args, void *)));
	if (*format == 'd' || *format == 'i')
		return (handle_dec(va_arg(args, int)));
	if (*format == 'u')
		return (handle_udec(va_arg(args, unsigned int)));
	if (*format == 'x')
		return (handle_hex_l(va_arg(args, int)));
	if (*format == 'X')
		return (handle_hex_u(va_arg(args, int)));
	if (*format == '%')
		return (handle_pct());
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			count += handle_format((char *)format, args);
		}
		else
		{
			ft_putchar_fd(*format, 1);
			count++;
		}
		format++;
	}
	va_end(args);
	return (count);
}
// #include <stdio.h>
// #include <limits.h>
// int	main(void)
// {
// 	int x, y;
// 	int	num = -1;
// 	unsigned int nbr= 0;

// 	x = printf		("%c | %s | %p | %d | %i | %u | %x | %X | %%\n",
// 					0, (char *)0, NULL, num, num, nbr, num, num);
// 	y = ft_printf	("%c | %s | %p | %d | %i | %u | %x | %X | %%\n",
// 					0, (char *)0, NULL, num, num, nbr, num, num);
// 	printf("%d | %d\n", x, y);
// }
