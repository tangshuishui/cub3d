/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshi <yshi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:51:21 by yshi              #+#    #+#             */
/*   Updated: 2025/05/21 14:06:53 by yshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*src;

	src = (unsigned char *)s;
	while (n--)
	{
		if (*src == (unsigned char)c)
			return ((void *)src);
		src++;
	}
	return (NULL);
}
