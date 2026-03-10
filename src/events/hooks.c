/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:42:32 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/10 16:09:07 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 1. 按下按键时，将对应的布尔值设为 true
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

// 2. 松开按键时，将对应的布尔值设为 false
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

// 3. 点击窗口的红叉时退出
int close_window(t_game *game)
{
	free_all(game);
	exit(0);
	return (0);
}

void	init_hooks(t_game *game)
{
	// 2 是 KeyPress, 1L<<0 是 KeyPressMask
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	// 3 是 KeyRelease, 1L<<1 是 KeyReleaseMask
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	// 17 是 DestroyNotify (点红叉)
	mlx_hook(game->win, 17, 0, close_window, game);
}
