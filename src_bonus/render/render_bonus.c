/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshi <yshi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:46:59 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/12 18:01:54 by yshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

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

static void	update_animation(t_game *game)
{
	unsigned long long	current_time;

	current_time = get_time_ms();
	if (current_time - game->anim.last_anim_time > 100)
	{
		game->anim.anim_frames = (game->anim.anim_frames + 1) % 8;
		game->anim.last_anim_time = current_time;
	}
}

int	render_frame(t_game *game)
{
	int	x;

	update_animation(game);
	set_frame(game);
	player_move(game);
	player_rotate(game);
	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(game, x);
		cast_rays(game);
		cal_lineheight(game);
		determine_texture(game);
		cal_texture(game);
		draw_vertical_stripe(game, x);
		x++;
	}
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img_ptr, 0, 0);
	return (0);
}
