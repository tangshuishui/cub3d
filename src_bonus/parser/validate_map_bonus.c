/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 13:38:12 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/03 18:08:41 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

// 检查该地砖的四周是否有虚空 (空格)
static int	touches_space(t_game *game, int x, int y)
{
	char **grid;

	grid = game->map.grid;
	// 因为已经补成了矩形，只要不越界，就可以安全查水表
	if (grid[y - 1][x] == ' ' || grid[y + 1][x] == ' ' ||
		grid[y][x - 1] == ' ' || grid[y][x + 1] == ' ')
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
			if (!ft_strchr("01NSEW ", grid[y][x]))
				exit_err(game, "Invalid map character");
			
			// {
			// 	printf("Error\nInvalid map character: %c\n", grid[y][x]);
			// 	free(game);
			// 	exit (1);
			// }
			
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

//扫描地图
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
				// 2. 如果空地碰到了空格，判死刑
				if (touches_space(game, x, y))
					exit_err(game, "Map is open: floor touches empty space");
			}
		}
	}
}
