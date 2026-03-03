/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:46:59 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/03 16:41:24 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	// 防止画出屏幕边界引起段错误
	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	render_frame(t_game *game)
{
	int					x;

	set_frame(game);
	player_move(game);
	player_rotate(game);
	
	x = 0;
	while (x < WIN_WIDTH)
	{
		// 发射射线,计算垂直墙壁距离
		cast_rays(game, x);
		// 计算墙壁在屏幕上的高度，赋予不同颜色，画墙
		cal_lineheight(game);
		determine_texture(game);
		cal_texture(game);
		draw_vertical_stripe(game, x);
		x++;
	}
	// 将画好的双缓冲图像一次性推送到窗口
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img_ptr, 0, 0);
	return (0);
}
