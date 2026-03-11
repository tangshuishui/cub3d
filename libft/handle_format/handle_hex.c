/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshi <yshi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:07:29 by yshi              #+#    #+#             */
/*   Updated: 2025/06/04 14:02:36 by yshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "../libft/libft.h"
#include "handle_format.h"

char	*ft_htoa_lower(unsigned int n)
{
	char			*str;
	char			*base;
	int				len;
	unsigned int	tmp;

	base = "0123456789abcdef";
	tmp = n;
	len = 1;
	while (tmp / 16)
	{
		len++;
		tmp /= 16;
	}
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = base[n % 16];
		n /= 16;
	}
	return (str);
}

int	handle_hex_l(int n)
{
	char			*str;
	int				len;
	unsigned int	val;

	val = (unsigned int)n;
	str = ft_htoa_lower(val);
	len = handle_str(str);
	free(str);
	return (len);
}

int	handle_hex_u(int n)
{
	char			*str;
	unsigned int	val;
	int				len;
	int				i;

	i = 0;
	val = (unsigned int)n;
	str = ft_htoa_lower(val);
	while (str[i])
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
	len = handle_str(str);
	free(str);
	return (len);
}
