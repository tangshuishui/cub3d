/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 16:11:06 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/08 15:46:55 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	prepare_tex(t_game *game, t_img *tex, double *step, double *tex_pos)
{
	t_ray	*r;

	r = &game->ray;
	*step = 1.0 * tex->height / r->line_height;
	*tex_pos = (r->draw_start - WIN_HEIGHT / 2 + r->line_height / 2) * (*step);
	if (*tex_pos < 0)
		*tex_pos = 0;
}

static int	get_tex_color(t_img *tex, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	dst = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

// static void	draw_wall(t_game *game, t_img *tex, int x)
// {
// 	int		tex_y;
// 	int		color;
// 	int		y;
// 	double	tex_pos;
// 	double	step;

// 	prepare_tex(game, tex, &step, &tex_pos);
// 	y = game->ray.draw_start;
// 	while (y <= game->ray.draw_end)
// 	{
// 		tex_y = (int)tex_pos & (tex->height - 1);
// 		tex_pos += step;
// 		color = get_tex_color(tex, game->ray.tex_x, tex_y);
// 		if (game->ray.side == 1)
// 			color = (color >> 1) & 8355711;
// 		my_mlx_pixel_put(&game->screen, x, y, color);
// 		y++;
// 	}
// }

static int	get_anim_color(t_game *game, t_img *tex, int tex_y, int color)
{
	t_img	*anim_tex;
	int		anim_x;
	int		anim_y;
	int		anim_color;

	if (game->map.grid[game->ray.map_y][game->ray.map_x] != 'A') // 'A' 代表动画墙
		return (color);
	//获取动画贴图
	anim_tex = &game->anim.anim_wall[game->anim.anim_frames];
	// 【极其重要】：根据两张贴图的真实尺寸，按比例映射坐标！
	// 防止越界，同时让小贴图也能铺满大墙壁！
	anim_x = game->ray.tex_x * anim_tex->width / tex->width;
	anim_y = tex_y * anim_tex->height / tex->height;
	anim_color = get_tex_color(anim_tex, anim_x, anim_y);

	if ((anim_color & 0x00FFFFFF) != 0x000000) // 只有非透明部分才覆盖
		color = anim_color;
	return (color);
}

static void	draw_wall(t_game *game, t_img *tex, int x)
{
	int		tex_y;
	int		color;
	int		y;
	double	tex_pos;
	double	step;

	prepare_tex(game, tex, &step, &tex_pos);
	y = game->ray.draw_start;
	while (y <= game->ray.draw_end)
	{
		tex_y = (int)tex_pos & (tex->height - 1);
		tex_pos += step;
		//提取砖墙颜色
		color = get_tex_color(tex, game->ray.tex_x, tex_y);
		//加上动画
		color = get_anim_color(game, tex, tex_y, color);

		//转角阴影
		// if (game->ray.side == 1)
		// 	color = (color >> 1) & 8355711;
		my_mlx_pixel_put(&game->screen, x, y, color);
		y++;
	}
}


void	draw_vertical_stripe(t_game *game, int x)
{
	t_img	*tex;
	int		y;

	tex = &game->textures[game->ray.tex_dir];
	y = 0;
	while (y < game->ray.draw_start)
		my_mlx_pixel_put(&game->screen, x, y++, game->map.ceil_color);
	draw_wall(game, tex, x);
	y = game->ray.draw_end + 1;
	while (y < WIN_HEIGHT)
		my_mlx_pixel_put(&game->screen, x, y++, game->map.floor_color);
}
