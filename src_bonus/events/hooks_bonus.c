/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:42:32 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/03 18:58:30 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		free_all(game);
		exit(0);
	}
	if (keycode == KEY_W)
		game->player.key_w = true;
	if (keycode == KEY_S)
		game->player.key_s = true;
	if (keycode == KEY_A)
		game->player.key_a = true;
	if (keycode == KEY_D)
		game->player.key_d = true;
	if (keycode == KEY_LEFT)
		game->player.key_left = true;
	if (keycode == KEY_RIGHT)
		game->player.key_right = true;
	return (0);
}

int key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->player.key_w = false;
	if (keycode == KEY_S)
		game->player.key_s = false;
	if (keycode == KEY_A)
		game->player.key_a = false;
	if (keycode == KEY_D)
		game->player.key_d = false;
	if (keycode == KEY_LEFT)
		game->player.key_left = false;
	if (keycode == KEY_RIGHT)
		game->player.key_right = false;
	return (0);
}

int close_window(t_game *game)
{
	free_all(game);
	exit(0);
	return (0);
}

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

void	init_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 1L << 17, close_window, game);
	// 隐藏系统自带的鼠标指针，沉浸感拉满！
	mlx_mouse_hide(game->mlx, game->win);
	// 将鼠标强行居中一次
	mlx_mouse_move(game->mlx, game->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	// 注册鼠标移动事件 (6 是 MotionNotify, 1L<<6 是 PointerMotionMask)
	mlx_hook(game->win, 6, 1L << 6, mouse_move_hook, game);
}
