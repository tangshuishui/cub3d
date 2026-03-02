/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 12:58:56 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/02 13:38:36 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_max_width(t_map *map)
{
	int	max;
	int	len;
	int	i;

	max = 0;
	i = 0;
	while (i < map->height)
	{
		len = 0;
		while (map->grid[i][len])
			len++;
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

static char	*pad_row(char *old_row, int max_width)
{
	char	*new_row;
	int		i;

	new_row = malloc(sizeof(char) * (max_width + 1));
	if (!new_row)
		return (NULL);
	i = 0;
	while (old_row[i])
	{
		new_row[i] = old_row[i];
		i++;
	}
	while (i < max_width)
	{
		new_row[i] = ' '; // 用空格补齐
		i++;
	}
	new_row[max_width] = '\0';
	free(old_row); // 释放旧的短字符串
	return (new_row);
}

void	format_map(t_game *game)
{
	int 	i;
	char	*new_row;

	//将地图矩形化
	game->map.width = get_max_width(&game->map);
	i = 0;
	while (i < game->map.height)
	{
		new_row = pad_row(game->map.grid[i], game->map.width);
		if (!new_row)
			exit_err(game, "Malloc failed during map padding");
		game->map.grid[i] = new_row;
		i++;
	}
}
