/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshi <yshi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 17:54:01 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/12 17:34:27 by yshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	init_player(t_player *player)
{
	player->pos_x = 0.0;
	player->pos_y = 0.0;
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.0;
	player->key_w = false;
	player->key_s = false;
	player->key_a = false;
	player->key_d = false;
	player->key_left = false;
	player->key_right = false;
}

static void	init_map(t_map *map)
{
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	map->no_path = NULL;
	map->so_path = NULL;
	map->we_path = NULL;
	map->ea_path = NULL;
	map->d_path = NULL;
	map->floor_color = -1;
	map->ceil_color = -1;
	map->raw_lines = NULL;
}

static void	init_anim(t_poster *anim)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		anim->anim_wall[i].img_ptr = NULL;
		anim->anim_wall[i].addr = NULL;
		anim->anim_wall[i].width = 0;
		anim->anim_wall[i].height = 0;
		i++;
	}
	anim->last_anim_time = get_time_ms();
	anim->anim_frames = 0;
}

void	init_data(t_game *game)
{
	int	i;

	game->mlx = NULL;
	game->win = NULL;
	init_map(&game->map);
	init_player(&game->player);
	ft_bzero(&game->ray, sizeof(t_ray));
	i = 0;
	while (i < 5)
	{
		game->textures[i].img_ptr = NULL;
		game->textures[i].addr = NULL;
		game->textures[i].width = 0;
		game->textures[i].height = 0;
		i++;
	}
	init_anim(&game->anim);
	game->screen.img_ptr = NULL;
	game->screen.addr = NULL;
	game->last_time = get_time_ms();
	game->fd = -1;
	game->line = NULL;
}
