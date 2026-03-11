/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 14:24:29 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/04 14:29:57 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	mouse_move_hook(int x, int y, t_game *game)
{
	int		center_x;
	int		delta_x;
	double	rot_speed;

	(void)y; // 2.5D 游戏不需要上下抬头，忽略 Y 轴
	center_x = WIN_WIDTH / 2;
	delta_x = x - center_x; // 计算鼠标偏离中心的距离

	if (delta_x != 0)
	{
		// 1. 根据偏移量和 frame_time 计算旋转角度
		rot_speed = delta_x * MOUSE_SENS * game->frame_time;
		
		// 2. 视角旋转，二维欧几里得旋转变换
		rotate_vectors(&game->player, rot_speed);
		
		// 3. 把鼠标强行拽回窗口正中心，等待下一帧的相对位移
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
	// 玩家正前方 1 格的坐标
	// 为了防止玩家在远处隔空开门，我们可以加上一点偏移量，这里简单地取前方 1 个单位
	target_x = (int)(p->pos_x + p->dir_x);
	target_y = (int)(p->pos_y + p->dir_y);

	// 防越界保护
	if (target_x < 0 || target_x >= game->map.width 
		|| target_y < 0 || target_y >= game->map.height)
		return ;

	// 如果前方是关着的门 ('D')，打开它！('O')
	if (game->map.grid[target_y][target_x] == 'D')
	{
		game->map.grid[target_y][target_x] = 'O'; // 'O' 既不会阻挡射线，也不会阻挡玩家
	}
	// 如果前方是开着的门 ('O')，关上它！('D')
	else if (game->map.grid[target_y][target_x] == 'O')
	{
		// 【防卡死保护】：如果玩家正站在门里，绝对不能关门，否则会卡死在墙里！
		if ((int)p->pos_x == target_x && (int)p->pos_y == target_y)
			return ;
		game->map.grid[target_y][target_x] = 'D';
	}
}
