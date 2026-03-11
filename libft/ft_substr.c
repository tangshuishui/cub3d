/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalishi <yalishi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:26:52 by yshi              #+#    #+#             */
/*   Updated: 2025/06/17 13:24:04 by yalishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	len_s;
	unsigned int	len_sub;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (start >= len_s)
		return (ft_strdup(""));
	if (len_s - start < len)
		len_sub = len_s - start;
	else
		len_sub = len;
	sub = (char *)malloc(sizeof(char) * (len_sub + 1));
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, s + start, len_sub + 1);
	return (sub);
}
