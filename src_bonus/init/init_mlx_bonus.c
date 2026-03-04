/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:00:24 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/04 13:54:55 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	exit_err(t_game *game, char *msg)
{
	printf("Error\n%s\n", msg);
	free_all(game);
	exit(1);
}

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit_err(game, "Failed to initialize MLX");
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->win)
		exit_err(game, "Failed to create window");
	game->screen.img_ptr = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->screen.img_ptr)
		exit_err(game, "Failed to create screen image");
	game->screen.addr = mlx_get_data_addr(game->screen.img_ptr, &game->screen.bpp, &game->screen.line_len, &game->screen.endian);
	game->screen.width = WIN_WIDTH;
	game->screen.height = WIN_HEIGHT;
}

// 辅助函数：加载单张纹理并获取其像素数据地址
static void	load_texture(t_game *game, t_img *tex, char *path)
{
	// 1. 使用 mlx_xpm_file_to_image 读取 .xpm 文件
	// 它会自动把图片的宽和高存入 tex->width 和 tex->height
	tex->img_ptr = mlx_xpm_file_to_image(game->mlx, path, &tex->width, &tex->height);
	if (!tex->img_ptr)
	{
		printf("Error\nFailed to load texture: %s\n", path);
		exit_err(game, "XPM loading failed");
	}

	// 2. 获取该图片的内存地址 (addr)
	// 只有拿到了 addr，我们才能在渲染时用快速的位运算去提取某个 (x, y) 坐标的颜色
	tex->addr = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->line_len, &tex->endian);
	if (!tex->addr)
		exit_err(game, "Failed to get texture data address");
}

// 主加载函数：按照 0=NO, 1=SO, 2=WE, 3=EA, 4=D 的顺序存入数组
void	init_textures(t_game *game)
{
	// 这里的顺序极其重要！必须和你之前 determine_texture_dir 中的设定完全一致
	load_texture(game, &game->textures[0], game->map.no_path);
	load_texture(game, &game->textures[1], game->map.so_path);
	load_texture(game, &game->textures[2], game->map.we_path);
	load_texture(game, &game->textures[3], game->map.ea_path);
	load_texture(game, &game->textures[4], game->map.d_path);
}
