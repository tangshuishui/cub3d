/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:48:51 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/03 16:02:40 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 根据指定的旋转角度更新向量
static void	rotate_vectors(t_player *p, double rot_speed)
{
	double old_dir_x;
	double old_plane_x;

	// 1. 旋转方向向量 dir
	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(rot_speed) - p->dir_y * sin(rot_speed);
	p->dir_y = old_dir_x * sin(rot_speed) + p->dir_y * cos(rot_speed);

	// 2. 旋转相机平面向量 plane (极其重要，否则你的视野会崩坏)
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(rot_speed) - p->plane_y * sin(rot_speed);
	p->plane_y = old_plane_x * sin(rot_speed) + p->plane_y * cos(rot_speed);
}

// 核心视角旋转控制
void	player_rotate(t_game *game)
{
	t_player	*p;
	double		step;

	p = &game->player;
	step = ROT_SPEED * game->frame_time;
	if (p->key_left)
		rotate_vectors(p, -step);// 往左转，角度为负
	if (p->key_right)
		rotate_vectors(p, step);// 往右转，角度为正
}
