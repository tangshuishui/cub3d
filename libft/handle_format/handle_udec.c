/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_udec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshi <yshi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:06:41 by yshi              #+#    #+#             */
/*   Updated: 2025/06/04 13:11:49 by yshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft/libft.h"
#include "handle_format.h"

char	*ft_utoa(unsigned int n)
{
	char			*str;
	int				len;
	unsigned int	tmp;

	tmp = n;
	len = 1;
	while (tmp / 10)
	{
		len++;
		tmp /= 10;
	}
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = '0' + (n % 10);
		n /= 10;
	}
	return (str);
}

int	handle_udec(unsigned int n)
{
	char	*str;
	int		len;

	str = ft_utoa(n);
	len = handle_str(str);
	free(str);
	return (len);
}
