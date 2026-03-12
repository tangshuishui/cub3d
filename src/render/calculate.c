/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshi <yshi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 17:58:31 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/12 17:25:50 by yshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cal_lineheight(t_game *game)
{
	t_ray	*r;

	r = &game->ray;
	r->line_height = (int)(WIN_HEIGHT / r->perp_wall_dist);
	r->draw_start = -r->line_height / 2 + WIN_HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + WIN_HEIGHT / 2;
	if (r->draw_end >= WIN_HEIGHT)
		r->draw_end = WIN_HEIGHT - 1;
}

void	determine_texture(t_game *game)
{
	t_ray	*r;

	r = &game->ray;
	if (r->side == 0)
	{
		if (r->step_x > 0)
			r->tex_dir = TEX_WEST;
		else
			r->tex_dir = TEX_EAST;
	}
	else
	{
		if (r->step_y > 0)
			r->tex_dir = TEX_NORTH;
		else
			r->tex_dir = TEX_SOUTH;
	}
}

void	cal_texture(t_game *game)
{
	t_ray	*r;
	t_img	*tex;

	r = &game->ray;
	tex = &game->textures[r->tex_dir];
	if (r->side == 0)
		r->wall_x = game->player.pos_y + r->perp_wall_dist * r->dir_y;
	else
		r->wall_x = game->player.pos_x + r->perp_wall_dist * r->dir_x;
	r->wall_x -= floor(r->wall_x);
	r->tex_x = (int)(r->wall_x * (double)tex->width);
	if ((r->side == 0 && r->dir_x > 0) || (r->side == 1 && r->dir_y < 0))
		r->tex_x = tex->width - r->tex_x - 1;
}
