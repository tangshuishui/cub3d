/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshi <yshi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 18:59:22 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/12 17:58:48 by yshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	get_mmp_color(t_game *game, int x, int y)
{
	int		map_x;
	int		map_y;
	char	c;

	map_x = (int)game->player.pos_x + x;
	map_y = (int)game->player.pos_y + y;
	if (map_x < 0 || map_y < 0 || map_x >= game->map.width
		|| map_y >= game->map.height || game->map.grid[map_y][map_x] == ' ')
		return (0x000000);
	c = game->map.grid[map_y][map_x];
	if (c == '1')
		return (0x666666);
	if (c == 'D')
		return (0xFFD700);
	if (c == 'O')
		return (0xDEB887);
	if (c == 'A')
		return (0x8B4513);
	return (0xCCCCCC);
}

static void	draw_tile(t_game *game, int x, int y, int color)
{
	int		i;
	int		j;
	double	f[2];
	int		px;
	int		py;

	f[0] = game->player.pos_x - floor(game->player.pos_x);
	f[1] = game->player.pos_y - floor(game->player.pos_y);
	i = 0;
	while (i < MMAP_TILE)
	{
		j = 0;
		while (j < MMAP_TILE)
		{
			px = MMAP_OFFSET + x * MMAP_TILE - (int)(f[0] * MMAP_TILE) + i;
			py = MMAP_OFFSET + y * MMAP_TILE - (int)(f[1] * MMAP_TILE) + j;
			if (px >= MMAP_OFFSET && px < MMAP_OFFSET
				+ ((2 * MMAP_VIEW + 1) * MMAP_TILE) && py >= MMAP_OFFSET
				&& py < MMAP_OFFSET + ((2 * MMAP_VIEW + 1) * MMAP_TILE))
				my_mlx_pixel_put(&game->screen, px, py, color);
			j++;
		}
		i++;
	}
}

// //初始简单版本，格子跳跃（Grid Snapping）
// static void	draw_tile(t_game *game, int x, int y, int color)
// {
// 	int		i;
// 	int		j;

// 	i = 0;
// 	while (i < MMAP_TILE)
// 	{
// 		j = 0;
// 		while (j < MMAP_TILE)
// 		{
// 			// 加上 MMAP_OFFSET，让小地图贴在左上角有一定边距
// 			my_mlx_pixel_put(&game->screen,
// 				MMAP_OFFSET + x * MMAP_TILE + i,
// 				MMAP_OFFSET + y * MMAP_TILE + j,
// 				color);
// 			j++;
// 		}
// 		i++;
// 	}
// }

/*
** 绘制代表玩家视野的扇形 (FOV Fan)
** center_x, center_y: 玩家在小地图上的绝对中心坐标
*/
static void	draw_fov_fan(t_game *game, double center_x, double center_y)
{
	int		i;
	int		r;
	double	cam_x;
	double	ray_xy[2];
	double	xy[2];

	r = 0;
	while (r <= 30)
	{
		cam_x = 2.0 * r / 30.0 - 1.0;
		ray_xy[0] = game->player.dir_x + game->player.plane_x * cam_x;
		ray_xy[1] = game->player.dir_y + game->player.plane_y * cam_x;
		i = 0;
		xy[0] = center_x;
		xy[1] = center_y;
		while (i < 15)
		{
			my_mlx_pixel_put(&game->screen, xy[0], xy[1], 0xFFFF00);
			xy[0] += ray_xy[0];
			xy[1] += ray_xy[1];
			i++;
		}
		r++;
	}
}

static void	draw_mmap_player(t_game *game)
{
	int		i;
	int		j;
	double	p_x;
	double	p_y;

	p_x = MMAP_OFFSET + (MMAP_VIEW * MMAP_TILE);
	p_y = MMAP_OFFSET + (MMAP_VIEW * MMAP_TILE);
	draw_fov_fan(game, p_x, p_y);
	i = -2;
	while (++i <= 1)
	{
		j = -2;
		while (++j <= 1)
			my_mlx_pixel_put(&game->screen, p_x + i, p_y + j, 0xFF0000);
	}
}

void	draw_minimap(t_game *game)
{
	int	y;
	int	x;
	int	color;

	y = -MMAP_VIEW - 1;
	while (y <= MMAP_VIEW + 1)
	{
		x = -MMAP_VIEW - 1;
		while (x <= MMAP_VIEW + 1)
		{
			color = get_mmp_color(game, x, y);
			draw_tile(game, x + MMAP_VIEW, y + MMAP_VIEW, color);
			x++;
		}
		y++;
	}
	draw_mmap_player(game);
}
