/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshi <yshi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:05:00 by yshi              #+#    #+#             */
/*   Updated: 2025/06/04 13:11:13 by yshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "../libft/libft.h"
#include "handle_format.h"

int	handle_dec(int n)
{
	char	*str;
	int		len;

	str = ft_itoa(n);
	len = handle_str(str);
	free(str);
	return (len);
}
