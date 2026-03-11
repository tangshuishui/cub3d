/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hanle_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshi <yshi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:03:53 by yshi              #+#    #+#             */
/*   Updated: 2025/06/04 13:11:54 by yshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "handle_format.h"

int	handle_str(char *str)
{
	int	len;

	len = 0;
	if (str == NULL)
		str = "(null)";
	while (*str)
	{
		len += handle_char(*str);
		str++;
	}
	return (len);
}
