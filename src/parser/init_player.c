/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshi <yshi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 15:01:37 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/12 16:33:22 by yshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 辅助函数：根据字母设置方向和相机平面
static void	set_camera_vectors(t_player *player, char dir)
{
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.0;
	if (dir == 'N')
	{
		player->dir_y = -1.0;
		player->plane_x = 0.66;
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
	game->player.pos_x = x + 0.5;
	game->player.pos_y = y + 0.5;
	set_camera_vectors(&game->player, dir);
	game->map.grid[y][x] = '0';
}
