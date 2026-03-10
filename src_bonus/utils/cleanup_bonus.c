/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:20:55 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/10 12:17:01 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	free_map_lines(t_map_list*lst)
{
	t_map_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		if (lst->line)
			free(lst->line);
		free(lst);
		lst = tmp;
	}
}

static void	free_map(t_map *map)
{
	int i;

	if (map->no_path)
		free(map->no_path);
	if (map->so_path)
		free(map->so_path);
	if (map->we_path)
		free(map->we_path);
	if (map->ea_path)
		free(map->ea_path);
	if (map->d_path)
		free(map->d_path);
	if (map->raw_lines)
		free_map_lines(map->raw_lines);
	if (map->grid)
	{
		i = 0;
		while (i < map->height && map->grid[i])
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}
}

static void	free_graph(t_game *game)
{
	int i;

	i = 0;
	while (i < 5)
	{
		if (game->textures[i].img_ptr)
			mlx_destroy_image(game->mlx, game->textures[i].img_ptr);
		i++;
	}
	i = 0;
	while (i < 8)
	{
		if (game->anim.anim_wall[i].img_ptr)
			mlx_destroy_image(game->mlx, game->anim.anim_wall[i].img_ptr);
		i++;
	}
	if (game->screen.img_ptr)
		mlx_destroy_image(game->mlx, game->screen.img_ptr);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

void	free_all(t_game *game)
{
	if (!game)
		return ;
	if (game->line)
	{
		free(game->line);
		game->line = get_next_line(-1);
	}
	if (game->fd > 0)
		close(game->fd);
	free_map(&game->map);
	free_graph(game);
}
