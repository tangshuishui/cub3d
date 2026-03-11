/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalishi <yalishi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:13:04 by yshi              #+#    #+#             */
/*   Updated: 2025/06/17 13:21:52 by yalishi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
