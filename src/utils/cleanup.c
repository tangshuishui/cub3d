/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 18:20:55 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/02 12:25:42 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_map_lines(t_map_list*lst)
{
	t_map_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		// 如果行内容存在，释放字符串
		if (lst->line)
			free(lst->line);
		// 释放节点本身
		free(lst);
		lst = tmp;
	}
}

// 释放地图相关的内存 (比如二维数组和字符串)
static void	free_map(t_map *map)
{
	int i;

	// 释放纹理路径字符串
	if (map->no_path)
		free(map->no_path);
	if (map->so_path)
		free(map->so_path);
	if (map->we_path)
		free(map->we_path);
	if (map->ea_path)
		free(map->ea_path);

	if (map->raw_lines)
		free_map_lines(map->raw_lines);
	// 释放二维地图数组
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

// 释放图形界面的所有资源
static void	free_graph(t_game *game)
{
	int i;

	// 1. 销毁 4 个方向的纹理图像
	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img_ptr)
			mlx_destroy_image(game->mlx, game->textures[i].img_ptr);
		i++;
	}

	// 2. 销毁屏幕双缓冲图像
	if (game->screen.img_ptr)
		mlx_destroy_image(game->mlx, game->screen.img_ptr);

	// 3. 销毁窗口
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);

	// 4. 销毁 MLX 
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
	free_map(&game->map);
	free_graph(game);
}
