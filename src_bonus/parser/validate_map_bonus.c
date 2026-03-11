/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 13:38:12 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/06 18:32:43 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	touches_space(t_game *game, int x, int y)
{
	char **grid;

	grid = game->map.grid;
	if (grid[y - 1][x] == ' ' || grid[y + 1][x] == ' ' 
		|| grid[y][x - 1] == ' ' || grid[y][x + 1] == ' ')
		return (1);
	return (0);
}

static void	check_elements(t_game *game, char **grid)
{
	int x;
	int y;
	int player_count;

	player_count = 0;
	y = -1;
	while (++y < game->map.height)
	{
		x = -1;
		while (++x < game->map.width)
		{
			if (!ft_strchr("01NSEWDA ", grid[y][x]))
				exit_err(game, "Invalid map character");
			if (is_player(grid[y][x]))
			{
				player_count++;
				init_player_position(game, x, y, grid[y][x]);
			}
		}
	}
	if (player_count != 1)
		exit_err(game, "Map must contain exactly 1 player");
}

static int	is_valid_door(t_game *game, int x, int y)
{
	char	**grid;

	grid = game->map.grid;
	// 1. 绝对边缘不能有门（防 Segfault）
	if (x == 0 || y == 0 || x == game->map.width - 1 || y == game->map.height - 1)
		return (0);

	// 2. 判断横向镶嵌：左边和右边都是墙 ('1')，且上方和下方是可以走的区域 ('0' 或其他)
	if ((grid[y][x - 1] == '1' || grid[y][x - 1] == 'A') && (grid[y][x + 1] == '1' || grid[y][x + 1] == 'A'))
	{
		if (grid[y - 1][x] == '0' || is_player(grid[y - 1][x]) 
		|| grid[y + 1][x] == '0' || is_player(grid[y + 1][x])) // 不是虚空
			return (1);
	}
	
	// 3. 判断纵向镶嵌：上方和下方都是墙 ('1')，且左边和右边是可以走的区域
	if ((grid[y - 1][x] == '1' || grid[y - 1][x] == 'A') && (grid[y + 1][x] == '1' || grid[y + 1][x] == 'A'))
	{
		if (grid[y][x - 1] == '0' || is_player(grid[y][x - 1]) 
		|| grid[y][x + 1] == '0' || is_player(grid[y][x + 1]))
			return (1);
	}

	// 如果都不满足，说明这是一扇乱造的门（比如悬空门、墙角门）
	return (0);
}

void	validate_map(t_game *game)
{
	int	x;
	int	y;

	check_elements(game, game->map.grid);
	y = -1;
	while (++y < game->map.height)
	{
		x = -1;
		while (++x < game->map.width)
		{
			if (game->map.grid[y][x] == '0' || is_player(game->map.grid[y][x]))
			{
				if (y == 0 || y == game->map.height - 1 || 
					x == 0 || x == game->map.width - 1)
					exit_err(game, "Map is open: floor reached grid edge");
				if (touches_space(game, x, y))
					exit_err(game, "Map is open: floor touches empty space");
			}
			if (game->map.grid[y][x] == 'D' && !is_valid_door(game, x, y))//判断门的位置
				exit_err(game, "Invalid door placement in map");
		}
	}
}
