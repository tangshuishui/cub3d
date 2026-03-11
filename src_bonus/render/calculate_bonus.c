/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 17:58:31 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/08 15:45:18 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	cal_lineheight(t_game *game)
{
	t_ray	*r;

	r = &game->ray;
	if (r->perp_wall_dist <= 0.0001)
		r->perp_wall_dist = 0.0001;
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
	if (r->hit == 2)//hit the door
	{
		r->tex_dir = 4;
		return ;
	}
	if (r->side == 0)
	{
		if (r->step_x > 0)
			r->tex_dir = 2;
		else
			r->tex_dir = 3;
	}
	else
	{
		if (r->step_y > 0)
			r->tex_dir = 0;
		else
			r->tex_dir = 1;
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
	if ((r->side == 0 && r->dir_x < 0) || (r->side == 1 && r->dir_y > 0))
		r->tex_x = tex->width -r->tex_x - 1;
}
