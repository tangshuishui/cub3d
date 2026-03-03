/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:46:59 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/03 18:57:23 by hanwang          ###   ########.fr       */
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

int	render_frame(t_game *game)
{
	int	x;

	set_frame(game);
	player_move(game);
	player_rotate(game);
	
	x = 0;
	while (x < WIN_WIDTH)
	{
		cast_rays(game, x);
		cal_lineheight(game);
		determine_texture(game);
		cal_texture(game);
		draw_vertical_stripe(game, x);
		x++;
	}
	//新增小地图
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img_ptr, 0, 0);
	return (0);
}
