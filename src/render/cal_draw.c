/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cal_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 17:58:31 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/02 18:27:40 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cal_lineheight(t_game *game, int *line_height, int *start, int *end)
{
	t_ray	*r;

	r = &game->ray;
	if (r->perp_wall_dist <= 0.0001) // 防止贴墙太近导致除零或高度爆炸
		r->perp_wall_dist = 0.0001;

	// 1. 计算墙体在屏幕上的像素高度
	// WIN_HEIGHT 是屏幕高度。距离越小，高度越大。
	*line_height = (int)(WIN_HEIGHT / r->perp_wall_dist);

	// 2. 计算绘制的起点（屏幕中心对称）
	// 将墙体放在屏幕中间：屏幕高度的一半 减去 墙高的一半
	*start = -*line_height / 2 + WIN_HEIGHT / 2;
	
	// 防止墙体超出屏幕顶部（溢出保护）
	if (*start < 0)
		*start = 0;

	// 3. 计算绘制的终点
	*end = *line_height / 2 + WIN_HEIGHT / 2;
	
	// 防止墙体超出屏幕底部
	if (*end >= WIN_HEIGHT)
		*end = WIN_HEIGHT - 1;
}

int	determine_wallcolor(t_game *game)
{
	t_ray	*r;
	int		color;

	r = &game->ray;
	// side == 0: 撞到了南北走向的墙 (跨越了 X 轴的网格线)
	if (r->side == 0)
	{
		if (r->step_x > 0)
			color = COLOR_WEST;  // 射线往右，打中西墙
		else
			color = COLOR_EAST;  // 射线往左，打中东墙
	}
	// side == 1: 撞到了东西走向的墙 (跨越了 Y 轴的网格线)
	else
	{
		if (r->step_y > 0)
			color = COLOR_NORTH; // 射线往下，打中北墙
		else
			color = COLOR_SOUTH; // 射线往上，打中南墙
	}

	// 可选：给南北面加上简单的阴影效果，增加 3D 立体感
	if (r->side == 1)
		color = (color >> 1) & 8355711; 

	return (color);
}

void	draw_vertical_stripe(t_game *game, int x, int start, int end, int color)
{
	int y;

	y = 0;
	// 1. 画天花板：从屏幕顶部 (0) 画到墙壁的顶端
	while (y < start)
	{
		my_mlx_pixel_put(&game->screen, x, y, game->map.ceil_color);
		y++;
	}

	// 2. 画墙壁：从墙壁的顶端画到墙壁的底端
	while (y <= end)
	{
		// 注意：后续贴图时，这里的纯色会被替换为从贴图(Texture)中提取的像素颜色
		my_mlx_pixel_put(&game->screen, x, y, color);
		y++;
	}

	// 3. 画地板：从墙壁的底端画到屏幕底部 (WIN_HEIGHT)
	while (y < WIN_HEIGHT)
	{
		my_mlx_pixel_put(&game->screen, x, y, game->map.floor_color);
		y++;
	}
}
