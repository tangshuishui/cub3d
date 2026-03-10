/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 17:58:31 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/10 15:02:11 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cal_lineheight(t_game *game)
{
	t_ray	*r;

	r = &game->ray;

	// 1. 计算墙体在屏幕上的像素高度
	// WIN_HEIGHT 是屏幕高度。距离越小，高度越大。
	r->line_height = (int)(WIN_HEIGHT / r->perp_wall_dist);

	// 2. 计算绘制的起点（屏幕中心对称）
	// 将墙体放在屏幕中间：屏幕高度的一半 减去 墙高的一半
	r->draw_start = -r->line_height / 2 + WIN_HEIGHT / 2;
	
	// 防止墙体超出屏幕顶部（溢出保护）
	if (r->draw_start < 0)
		r->draw_start = 0;

	// 3. 计算绘制的终点
	r->draw_end = r->line_height / 2 + WIN_HEIGHT / 2;
	
	// 防止墙体超出屏幕底部
	if (r->draw_end >= WIN_HEIGHT)
		r->draw_end = WIN_HEIGHT - 1;
}

void	determine_texture(t_game *game)
{
	t_ray	*r;

	r = &game->ray;
	// side == 0: 撞到了南北走向的墙 (跨越了 X 轴的网格线)
	if (r->side == 0)
	{
		if (r->step_x > 0)
			r->tex_dir = TEX_WEST;// 射线往右，打中西墙
		else
			r->tex_dir = TEX_EAST;// 射线往左，打中东墙
	}
	// side == 1: 撞到了东西走向的墙 (跨越了 Y 轴的网格线)
	else
	{
		if (r->step_y > 0)
			r->tex_dir = TEX_NORTH;// 射线往下，打中北墙
		else
			r->tex_dir = TEX_SOUTH;// 射线往上，打中南墙
	}
}

void	cal_texture(t_game *game)
{
	t_ray	*r;
	t_img	*tex;

	r = &game->ray;
	tex = &game->textures[r->tex_dir];
	// 1. 计算 wall_x (0.0 ~ 1.0 之间的浮点数)
	if (r->side == 0)
		r->wall_x = game->player.pos_y + r->perp_wall_dist * r->dir_y;
	else
		r->wall_x = game->player.pos_x + r->perp_wall_dist * r->dir_x;
	r->wall_x -= floor(r->wall_x);// 抛弃整数部分，只留小数部分
	
	// 2. 将 0.0~1.0 映射到纹理图片的真实宽度上 (例如 64 像素)
	r->tex_x = (int)(r->wall_x * (double)tex->width);

	// 3. 翻转 X 坐标 (防止镜像)
	if ((r->side == 0 && r->dir_x > 0) || (r->side == 1 && r->dir_y < 0))
		r->tex_x = tex->width -r->tex_x - 1;
}
