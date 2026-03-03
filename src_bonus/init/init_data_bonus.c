/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 17:54:01 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/03 18:09:36 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// 将玩家状态初始化
static void	init_player(t_player *player)
{
	player->pos_x = 0.0;
	player->pos_y = 0.0;
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.0;
	player->key_w = false;
	player->key_s = false;
	player->key_a = false;
	player->key_d = false;
	player->key_left = false;
	player->key_right = false;
}

// 将地图和纹理数据初始化
static void	init_map(t_map *map)
{
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	map->no_path = NULL;
	map->so_path = NULL;
	map->we_path = NULL;
	map->ea_path = NULL;
	// -1 代表还没读取到颜色 (因为 0x000000 是合法的黑色)
	map->floor_color = -1;
	map->ceil_color = -1;
	map->raw_lines = NULL;
}

// 暴露给 main.c 的主初始化函数
void	init_data(t_game *game)
{
	int i;

	game->mlx = NULL;
	game->win = NULL;
	
	init_map(&game->map);
	init_player(&game->player);
	
	ft_bzero(&game->ray, sizeof(t_ray));
	// 初始化纹理结构体
	i = 0;
	while (i < 4)
	{
		game->textures[i].img_ptr = NULL;
		game->textures[i].addr = NULL;
		game->textures[i].width = 0;
		game->textures[i].height = 0;
		i++;
	}
	
	// 初始化屏幕双缓冲
	game->screen.img_ptr = NULL;
	game->screen.addr = NULL;

	game->last_time = get_time_ms();
}
