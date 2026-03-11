/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:47:32 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/03 16:00:09 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int is_valid_pos(t_game *game, double target_x, double target_y)
{
	// 直接把浮点坐标强转为 int 来查网格
	// 0.1 穿模保护
	if (game->map.grid[(int)target_y][(int)(target_x + 0.1)] == '1' ||
		game->map.grid[(int)target_y][(int)(target_x - 0.1)] == '1' ||
		game->map.grid[(int)(target_y + 0.1)][(int)target_x] == '1' ||
		game->map.grid[(int)(target_y - 0.1)][(int)target_x] == '1')
		return (0);
	//防止走到虚空
	if (game->map.grid[(int)target_y][(int)target_x] == ' ')
		return (0);
	return (1);
}

static void	move_step(t_game *game, double x, double y)
{
	double	move_x;
	double	move_y;

	move_x = game->player.pos_x + x;
	move_y = game->player.pos_y + y;
	if (is_valid_pos(game, move_x, move_y))
	{
		game->player.pos_x = move_x;
		game->player.pos_y = move_y;
	}
}

void	player_move(t_game *game)
{
	t_player	*p;
	double		step;
	
	p = &game->player;
	step = MOVE_SPEED * game->frame_time;
	// 前进 (W) 和后退 (S) -> 沿着方向向量 dir 移动
	if (p->key_w)
		move_step(game, p->dir_x * step, p->dir_y * step);
	if (p->key_s)
		move_step(game, -p->dir_x * step, -p->dir_y * step);

	// 左平移 (A) 和右平移 (D) -> 沿着相机平面向量 plane 移动 (因为 plane 永远垂直于 dir)
	if (p->key_a)
		move_step(game, -p->plane_x * step, -p->plane_y * step);
	if (p->key_d)
		move_step(game, p->plane_x * step, p->plane_y * step);
}


//bonus
// 辅助函数：检查目标位置是否合法（不是墙）
// static bool	is_valid_pos_b(t_game *game, double x, double y)
// {
// 	// 加减 0.2 是为了给玩家一个“碰撞体积”，防止眼睛贴进墙面里
// 	if (game->map.grid[(int)y][(int)(x + 0.2)] == '1') return (false);
// 	if (game->map.grid[(int)y][(int)(x - 0.2)] == '1') return (false);
// 	if (game->map.grid[(int)(y + 0.2)][(int)x] == '1') return (false);
// 	if (game->map.grid[(int)(y - 0.2)][(int)x] == '1') return (false);
// 	return (true);
// }

// // 尝试在 X 和 Y 轴上独立移动，实现“贴墙滑动”
// static void	move_step(t_game *game, double move_x, double move_y)
// {
// 	t_player *p = &game->player;

// 	if (is_valid_pos_b(game, p->pos_x + move_x, p->pos_y))
// 		p->pos_x += move_x;
// 	if (is_valid_pos_b(game, p->pos_x, p->pos_y + move_y))
// 		p->pos_y += move_y;
// }


