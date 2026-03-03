/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:47:32 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/03 18:58:02 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	is_wall(t_game *game, double x, double y)
{
	char	c;

	if (x < 0 || y < 0 || x >= game->map.width || y >= game->map.height)
		return (1);
	c = game->map.grid[(int)y][(int)x];
	if (c == '1' || c == ' ' || c == 'D')
		return (1);
	return (0);
}

static int	is_valid_pos_b(t_game *game, double x, double y)
{
	if (is_wall(game, x + 0.2, y + 0.2) || is_wall(game, x - 0.2, y + 0.2) ||
		is_wall(game, x + 0.2, y - 0.2) || is_wall(game, x - 0.2, y - 0.2))
		return (0);
	return (1);
}

// 尝试在 X 和 Y 轴上独立移动，实现“贴墙滑动”
static void	move_step(t_game *game, double x, double y)
{
	t_player *p = &game->player;

	if (is_valid_pos_b(game, p->pos_x + x, p->pos_y))
		p->pos_x += x;
	if (is_valid_pos_b(game, p->pos_x, p->pos_y + y))
		p->pos_y += y;
}

void	player_move(t_game *game)
{
	t_player	*p;
	double		step;
	
	p = &game->player;
	step = MOVE_SPEED * game->frame_time;
	if (p->key_w)
		move_step(game, p->dir_x * step, p->dir_y * step);
	if (p->key_s)
		move_step(game, -p->dir_x * step, -p->dir_y * step);
	if (p->key_a)
		move_step(game, -p->plane_x * step, -p->plane_y * step);
	if (p->key_d)
		move_step(game, p->plane_x * step, p->plane_y * step);
}
