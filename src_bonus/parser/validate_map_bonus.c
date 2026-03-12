/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshi <yshi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 13:38:12 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/12 17:41:48 by yshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	touches_space(t_game *game, int x, int y)
{
	char	**grid;

	grid = game->map.grid;
	if (grid[y - 1][x] == ' ' || grid[y + 1][x] == ' '
		|| grid[y][x - 1] == ' ' || grid[y][x + 1] == ' ')
		return (1);
	return (0);
}

static void	check_elements(t_game *game, char **grid)
{
	int	x;
	int	y;
	int	player_count;

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
	if (x == 0 || y == 0 || x == game->map.width - 1
		|| y == game->map.height - 1)
		return (0);
	if ((grid[y][x - 1] == '1' || grid[y][x - 1] == 'A')
		&& (grid[y][x + 1] == '1' || grid[y][x + 1] == 'A'))
	{
		if (grid[y - 1][x] == '0' || is_player(grid[y - 1][x])
		|| grid[y + 1][x] == '0' || is_player(grid[y + 1][x]))
			return (1);
	}
	if ((grid[y - 1][x] == '1' || grid[y - 1][x] == 'A')
		&& (grid[y + 1][x] == '1' || grid[y + 1][x] == 'A'))
	{
		if (grid[y][x - 1] == '0' || is_player(grid[y][x - 1])
		|| grid[y][x + 1] == '0' || is_player(grid[y][x + 1]))
			return (1);
	}
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
				if (y == 0 || y == game->map.height - 1
					|| x == 0 || x == game->map.width - 1)
					exit_err(game, "Map is open: floor reached grid edge");
				if (touches_space(game, x, y))
					exit_err(game, "Map is open: floor touches empty space");
			}
			if (game->map.grid[y][x] == 'D' && !is_valid_door(game, x, y))
				exit_err(game, "Invalid door placement in map");
		}
	}
}
