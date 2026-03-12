/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshi <yshi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 14:24:29 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/12 18:00:11 by yshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	mouse_move_hook(int x, int y, t_game *game)
{
	int		center_x;
	int		delta_x;
	double	rot_speed;

	(void)y;
	center_x = WIN_WIDTH / 2;
	delta_x = x - center_x;
	if (delta_x != 0)
	{
		rot_speed = delta_x * MOUSE_SENS * game->frame_time;
		rotate_vectors(&game->player, rot_speed);
		mlx_mouse_move(game->mlx, game->win, center_x, WIN_HEIGHT / 2);
	}
	return (0);
}

void	open_door(t_game *game)
{
	t_player	*p;
	int			target_x;
	int			target_y;

	p = &game->player;
	target_x = (int)(p->pos_x + p->dir_x);
	target_y = (int)(p->pos_y + p->dir_y);
	if (target_x < 0 || target_x >= game->map.width
		|| target_y < 0 || target_y >= game->map.height)
		return ;
	if (game->map.grid[target_y][target_x] == 'D')
		game->map.grid[target_y][target_x] = 'O';
	else if (game->map.grid[target_y][target_x] == 'O')
	{
		if ((int)p->pos_x == target_x && (int)p->pos_y == target_y)
			return ;
		game->map.grid[target_y][target_x] = 'D';
	}
}
