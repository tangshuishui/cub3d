/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 15:01:37 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/02 15:02:47 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 辅助函数：根据字母设置方向和相机平面
static void	set_camera_vectors(t_player *player, char dir)
{
	// 默认全部清零，防备脏数据
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.0;

	if (dir == 'N')
	{
		player->dir_y = -1.0;
		player->plane_x = 0.66; // 屏幕在方向向量的右侧
	}
	else if (dir == 'S')
	{
		player->dir_y = 1.0;
		player->plane_x = -0.66;
	}
	else if (dir == 'E')
	{
		player->dir_x = 1.0;
		player->plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		player->dir_x = -1.0;
		player->plane_y = -0.66;
	}
}

// 在地图验证阶段调用此函数，提取玩家信息并抹除字母
void	init_player_position(t_game *game, int x, int y, char dir)
{
	// 1. 设置绝对坐标 (加 0.5 是为了让玩家站在网格的正中心，而不是网格左上角的点)
	game->player.pos_x = x + 0.5;
	game->player.pos_y = y + 0.5;

	// 2. 设置数学向量
	set_camera_vectors(&game->player, dir);

	// 3. 抹除地图上的字母，将其变为普通的可行走空地
	game->map.grid[y][x] = '0';
}
