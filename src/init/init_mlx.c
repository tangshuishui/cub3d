/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:00:24 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/01 19:20:25 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_err(t_game *game, char *msg)
{
	printf("Error\n%s\n", msg);
	free_all(game);
	exit(1);
}

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit_err(game, "Failed to initialize MLX");
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->win)
		exit_err(game, "Failed to create window");
	game->screen.img_ptr = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->screen.img_ptr)
		exit_err(game, "Failed to create screen image");
	game->screen.addr = mlx_get_data_addr(game->screen.img_ptr, &game->screen.bpp, &game->screen.line_len, &game->screen.endian);
	game->screen.width = WIN_WIDTH;
	game->screen.height = WIN_HEIGHT;
}
