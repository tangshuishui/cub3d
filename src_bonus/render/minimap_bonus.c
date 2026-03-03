/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 18:59:22 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/03 19:32:15 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_tile(t_game *game, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	while (i < MMAP_TILE)
	{
		j = 0;
		while (j < MMAP_TILE)
		{
			// 加上 MMAP_OFFSET，让小地图贴在左上角有一定边距
			my_mlx_pixel_put(&game->screen, 
				MMAP_OFFSET + x * MMAP_TILE + i, 
				MMAP_OFFSET + y * MMAP_TILE + j, 
				color);
			j++;
		}
		i++;
	}
}

static void	draw_mmap_player(t_game *game)
{
	int		i;
	int		j;
	double	p_x;
	double	p_y;
	double	k;

	// 计算小地图正中心的像素坐标
	p_x = MMAP_OFFSET + (MMAP_VIEW * MMAP_TILE) + (MMAP_TILE / 2);
	p_y = MMAP_OFFSET + (MMAP_VIEW * MMAP_TILE) + (MMAP_TILE / 2);
	
	// 画一个 3x3 的红点代表玩家
	i = -2;
	while (++i <= 1)
	{
		j = -2;
		while (++j <= 1)
			my_mlx_pixel_put(&game->screen, p_x + i, p_y + j, 0xFF0000);
	}

	// [Bonus] 额外画一条方向线：表示玩家在看哪
	k = 0;
	while (k < 10.0) // 长度为 10 像素的方向线
	{
		my_mlx_pixel_put(&game->screen, 
			p_x + game->player.dir_x * k, 
			p_y + game->player.dir_y * k, 0xFF0000);
		k += 0.5;
	}
}

void	draw_minimap(t_game *game)
{
	int y;
	int x;
	int map_x;
	int map_y;

	y = -MMAP_VIEW;
	while (y <= MMAP_VIEW)
	{
		x = -MMAP_VIEW;
		while (x <= MMAP_VIEW)
		{
			map_x = (int)game->player.pos_x + x;
			map_y = (int)game->player.pos_y + y;
			// 越界检测：如果超出地图范围，画成黑色
			if (map_x < 0 || map_y < 0 || map_x >= game->map.width 
				|| map_y >= game->map.height || game->map.grid[map_y][map_x] == ' ')
				draw_tile(game, x + MMAP_VIEW, y + MMAP_VIEW, 0x000000);
			else if (game->map.grid[map_y][map_x] == '1')
				draw_tile(game, x + MMAP_VIEW, y + MMAP_VIEW, 0x666666); // 墙：深灰
			else
				draw_tile(game, x + MMAP_VIEW, y + MMAP_VIEW, 0xCCCCCC); // 路：浅灰
			x++;
		}
		y++;
	}
	draw_mmap_player(game); // 画玩家图标
}


// // 1. 绘制色块：现在接收的是绝对屏幕坐标 s_x 和 s_y
// static void draw_tile(t_game *game, int s_x, int s_y, int color)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	while (i < MMAP_TILE_SIZE)
// 	{
// 		j = 0;
// 		while (j < MMAP_TILE_SIZE)
// 		{
// 			my_mlx_pixel_put(&game->screen, s_x + i, s_y + j, color);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// // 2. 核心：带子像素平滑(Sub-pixel)的地图扫描
// void draw_minimap(t_game *game)
// {
// 	int     x;
// 	int     y;
// 	int     map_x;
// 	int     map_y;
// 	double  fx; // 玩家位置的小数部分 X
// 	double  fy; // 玩家位置的小数部分 Y

// 	// 提取小数部分，用于地图的平滑反向偏移
// 	fx = game->player.pos_x - floor(game->player.pos_x);
// 	fy = game->player.pos_y - floor(game->player.pos_y);

// 	// 循环范围多加 1 圈 (-5 到 5)，防止地图边缘在平滑滑动时出现闪烁的黑边
// 	y = -MMAP_VIEW_DIST - 1; 
// 	while (y <= MMAP_VIEW_DIST + 1)
// 	{
// 		x = -MMAP_VIEW_DIST - 1;
// 		while (x <= MMAP_VIEW_DIST + 1)
// 		{
// 			map_x = (int)game->player.pos_x + x;
// 			map_y = (int)game->player.pos_y + y;
			
// 			// 【核心修正】：计算出带小数偏移量的真实屏幕绘制坐标
// 			int draw_x = MMAP_OFFSET + (x + MMAP_VIEW_DIST) * MMAP_TILE_SIZE - (int)(fx * MMAP_TILE_SIZE);
// 			int draw_y = MMAP_OFFSET + (y + MMAP_VIEW_DIST) * MMAP_TILE_SIZE - (int)(fy * MMAP_TILE_SIZE);

// 			if (map_x >= 0 && map_y >= 0 && map_x < game->map.width && 
// 				map_y < game->map.height && game->map.grid[map_y][map_x] == '1')
// 				draw_tile(game, draw_x, draw_y, 0x666666); // 墙
// 			else if (map_x >= 0 && map_y >= 0 && map_x < game->map.width && 
// 					 map_y < game->map.height && game->map.grid[map_y][map_x] != ' ')
// 				draw_tile(game, draw_x, draw_y, 0xCCCCCC); // 路
// 			else
// 				draw_tile(game, draw_x, draw_y, 0x000000); // 虚空
// 			x++;
// 		}
// 		y++;
// 	}
// 	draw_mmap_player(game);
// }
