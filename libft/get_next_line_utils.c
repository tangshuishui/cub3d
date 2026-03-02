/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 11:53:22 by yshi              #+#    #+#             */
/*   Updated: 2026/03/02 16:04:36 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strchr(const char *s, int c)
// {
// 	if (!s)
// 		return (NULL);
// 	while (*s)
// 	{
// 		if (*s == (unsigned char)c)
// 			return ((char *)s);
// 		s++;
// 	}
// 	if ((unsigned char)c == '\0')
// 		return ((char *)s);
// 	return (NULL);
// }

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;

	join = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
		return (NULL);
	join[0] = '\0';
	if (s1)
		ft_strlcpy(join, s1, ft_strlen(s1) + 1);
	if (s2)
		ft_strlcpy(&join[ft_strlen(s1)], s2, ft_strlen(s2) + 1);
	return (join);
}

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char			*sub;
// 	unsigned int	len_s;
// 	unsigned int	len_sub;

// 	if (!s)
// 		return (NULL);
// 	len_s = ft_strlen(s);
// 	if (start >= len_s)
// 	{
// 		sub = (char *)malloc(sizeof(char));
// 		if (!sub)
// 			return (NULL);
// 		sub[0] = '\0';
// 		return (sub);
// 	}
// 	if (len_s - start < len)
// 		len_sub = len_s - start;
// 	else
// 		len_sub = len;
// 	sub = (char *)malloc(sizeof(char) * (len_sub + 1));
// 	if (sub)
// 		ft_strlcpy(sub, &s[start], len_sub + 1);
// 	else
// 		return (NULL);
// 	return (sub);
// }
