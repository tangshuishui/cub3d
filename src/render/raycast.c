/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshi <yshi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:57:23 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/12 17:22:54 by yshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 1. 初始化当前射线 (根据屏幕 x 坐标)
static void	init_ray(t_game *game, int x)
{
	t_player	*p;
	t_ray		*r;

	p = &game->player;
	r = &game->ray;
	r->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	r->dir_x = p->dir_x + p->plane_x * r->camera_x;
	r->dir_y = p->dir_y + p->plane_y * r->camera_x;
	r->map_x = (int)p->pos_x;
	r->map_y = (int)p->pos_y;
	if (r->dir_x == 0)
		r->delta_dist_x = 1e30;
	else
		r->delta_dist_x = fabs(1.0 / r->dir_x);
	if (r->dir_y == 0)
		r->delta_dist_y = 1e30;
	else
		r->delta_dist_y = fabs(1.0 / r->dir_y);
	r->hit = 0;
}

// 2. 计算初始步长和边距
static void	calculate_step(t_game *game)
{
	t_player	*p;
	t_ray		*r;

	p = &game->player;
	r = &game->ray;
	if (r->dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (p->pos_x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - p->pos_x) * r->delta_dist_x;
	}
	if (r->dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (p->pos_y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - p->pos_y) * r->delta_dist_y;
	}
}

// 3. 执行 DDA 算法，直到撞墙
static void	perform_dda(t_game *game)
{
	t_ray	*r;

	r = &game->ray;
	while (r->hit == 0)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (r->map_y < 0 || r->map_y >= game->map.height || r->map_x < 0
			|| r->map_x >= game->map.width)
			r->hit = 1;
		if (game->map.grid[r->map_y][r->map_x] == '1')
			r->hit = 1;
	}
}

// 4. 消除鱼眼
static void	calculate_perpwalldist(t_game *game)
{
	t_ray	*r;

	r = &game->ray;
	if (r->side == 0)
		r->perp_wall_dist = (r->side_dist_x - r->delta_dist_x);
	else
		r->perp_wall_dist = (r->side_dist_y - r->delta_dist_y);
	if (r->perp_wall_dist <= 0.0001)
		r->perp_wall_dist = 0.0001;
}

void	cast_rays(t_game *game, int x)
{
	init_ray(game, x);
	calculate_step(game);
	perform_dda(game);
	calculate_perpwalldist(game);
}
