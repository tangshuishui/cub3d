/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshi <yshi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:04:22 by yshi              #+#    #+#             */
/*   Updated: 2025/06/04 13:11:42 by yshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "../libft/libft.h"

void	itoa_hex(uintptr_t num, int *len)
{
	char	*base;

	base = "0123456789abcdef";
	if (num < 16)
	{
		ft_putchar_fd(base[num], 1);
		(*len)++;
	}
	else
	{
		itoa_hex(num / 16, len);
		itoa_hex(num % 16, len);
	}
}

int	handle_ptr(uintptr_t add)
{
	int	len;

	if (add == 0)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	len = 2;
	ft_putstr_fd("0x", 1);
	itoa_hex(add, &len);
	return (len);
}
