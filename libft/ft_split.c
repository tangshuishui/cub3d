/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshi <yshi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 23:00:42 by yshi              #+#    #+#             */
/*   Updated: 2025/05/23 19:43:08 by yshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

size_t	count_str(char const *s, char c)
{
	size_t	count;
	size_t	str_flag;

	count = 0;
	str_flag = 0;
	while (*s)
	{
		if (!((*s) == c))
		{
			if (str_flag == 0)
				count++;
			str_flag = 1;
		}
		else
			str_flag = 0;
		s++;
	}
	return (count);
}

void	free_str_arr(char **arr, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		free(arr[i]);
		i ++;
	}
	free(arr);
}

int	process_sub(char **str_arr, const char *str, char c, size_t *i)
{
	char	*sub;
	size_t	len;

	len = 0;
	while (str[len] && !(str[len] == c))
		len++;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
	{
		free_str_arr(str_arr, *i);
		return (0);
	}
	ft_strlcpy(sub, str, len + 1);
	str_arr[*i] = sub;
	(*i)++;
	return (1);
}

int	process(const char *str, char c, char **str_arr)
{
	size_t	i;
	size_t	str_flag;

	i = 0;
	str_flag = 0;
	while (*str)
	{
		if (!(*str == c))
		{
			if (str_flag == 0)
				if (!process_sub(str_arr, str, c, &i))
					return (0);
			str_flag = 1;
		}
		else
			str_flag = 0;
		str++;
	}
	str_arr[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**str_arr;

	if (!s)
		return (NULL);
	str_arr = (char **)malloc(sizeof(char *) * (count_str(s, c) + 1));
	if (!str_arr)
		return (NULL);
	if (!process(s, c, str_arr))
		return (NULL);
	return (str_arr);
}
