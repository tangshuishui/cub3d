/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 18:59:22 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/06 18:31:06 by hanwang          ###   ########.fr       */
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
		return (0x666666); // 墙：深灰
	if (c == 'D')
		return (0x8B4513); // 门：深棕
	if (c == 'O')
		return (0xDEB887); // 打开的门：浅棕
	if (c == 'A')
		return (0xFFD700); //animation
	return (0xCCCCCC); // 路：浅灰
}

static void	draw_tile(t_game *game, int x, int y, int color)
{
	int		i;
	int		j;
	double	fx;
	double	fy;
	int		px;
	int		py;

	// 提取小数部分，用于地图的平滑反向偏移
	fx = game->player.pos_x - floor(game->player.pos_x);
	fy = game->player.pos_y - floor(game->player.pos_y);
	i = 0;
	while (i < MMAP_TILE)
	{
		j = 0;
		while (j < MMAP_TILE)
		{
			// 计算当前像素将要画在屏幕上的绝对坐标 px, py
			px = MMAP_OFFSET + x * MMAP_TILE - (int)(fx * MMAP_TILE) + i;
			py = MMAP_OFFSET + y * MMAP_TILE - (int)(fy * MMAP_TILE) + j;
			//裁剪蒙版 Clipping Mask】,只有当这个像素完完全全落在这个固定的框框内部时，才允许它画上屏幕！
			if (px >= MMAP_OFFSET && px < MMAP_OFFSET + MMAP_SIZE 
				&& py >= MMAP_OFFSET && py < MMAP_OFFSET + MMAP_SIZE)
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
	double	ray_x;
	double	ray_y;
	double	x;
	double	y;

	r = 0;
	// 发射 30 根短射线来铺满扇形 (数值可根据你的喜好调整)
	while (r <= 30)
	{
		// 1. 计算这根射线在相机平面上的相对位置 (-1.0 到 1.0)
		cam_x = 2.0 * r / 30.0 - 1.0;
		
		// 2. 结合 dir 和 plane 算出这根射线的真实朝向
		ray_x = game->player.dir_x + game->player.plane_x * cam_x;
		ray_y = game->player.dir_y + game->player.plane_y * cam_x;
		
		i = 0;
		x = center_x;
		y = center_y;
		// 3. 顺着这个朝向画一条长 15 像素的线
		while (i < 15)
		{
			// 使用不同的颜色(比如黄色)区别于玩家本体的红色
			my_mlx_pixel_put(&game->screen, x, y, 0xFFFF00); 
			x += ray_x;
			y += ray_y;
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

	// 计算小地图正中心的像素坐标
	p_x = MMAP_OFFSET + (MMAP_VIEW * MMAP_TILE);
	p_y = MMAP_OFFSET + (MMAP_VIEW * MMAP_TILE);
	
	// 先画扇形视线（这样视线会被玩家的红点压在下面，更好看）
	draw_fov_fan(game, p_x, p_y);
	
	// 画一个 3x3 的红点代表玩家
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
	int y;
	int x;
	int color;

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
	draw_mmap_player(game); // 画玩家图标
}
