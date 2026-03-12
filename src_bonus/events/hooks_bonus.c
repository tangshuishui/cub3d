/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshi <yshi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:42:32 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/12 17:31:49 by yshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		free_all(game);
		exit(0);
		return (0);
	}
	if (keycode == KEY_SPACE)
		open_door(game);
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

int	key_release(int keycode, t_game *game)
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

int	close_window(t_game *game)
{
	free_all(game);
	exit(0);
	return (0);
}

void	init_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 1L << 17, close_window, game);
	mlx_mouse_hide(game->mlx, game->win);
	mlx_mouse_move(game->mlx, game->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	mlx_hook(game->win, 6, 1L << 6, mouse_move_hook, game);
}
