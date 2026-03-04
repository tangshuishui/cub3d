/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:57:23 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/04 15:24:11 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

static void	dda_step(t_ray *r)
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
}

static void	perform_dda(t_game *game)
{
	t_ray	*r;

	r = &game->ray;
	while (r->hit == 0)
	{
		dda_step(r);
		if (r->map_y < 0 || r->map_y >= game->map.height
			|| r->map_x < 0 || r->map_x >= game->map.width)
		{
			r->hit = 1;
			break ;
		}
		if (game->map.grid[r->map_y][r->map_x] == '1')
			r->hit = 1;
		else if (game->map.grid[r->map_y][r->map_x] == 'D')
			r->hit = 2;
	}
}

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

void	cast_rays(t_game *game)
{
	calculate_step(game);
	perform_dda(game);
	calculate_perpwalldist(game);
}
