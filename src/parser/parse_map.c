/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshi <yshi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 12:12:59 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/11 16:58:18 by yshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_map_chars(t_game *game, char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!ft_strchr("01NSEW ", line[i]))
			exit_err(game, "Invalid character in map");
		i++;
	}
}

static char	*dup_without_newline(char *line)
{
	int		len;
	char	*new_str;
	int		i;

	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_str[i] = line[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

// 创建新节点并挂载到链表尾部
static void	add_to_list(t_game *game, char *clean_line)
{
	t_map_list	*node;
	t_map_list	*tmp;

	node = malloc(sizeof(t_map_list));
	if (!node)
	{
		free(clean_line);
		exit_err(game, "Malloc failed for map list node");
	}
	node->line = clean_line;
	node->next = NULL;
	if (!game->map.raw_lines)
		game->map.raw_lines = node;
	else
	{
		tmp = game->map.raw_lines;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
	game->map.height++;
}

void	parse_map(t_game *game, char *line)
{
	char	*clean_line;

	check_map_chars(game, line);
	clean_line = dup_without_newline(line);
	if (!clean_line)
		exit_err(game, "Malloc failed for map line duplication");
	add_to_list(game, clean_line);
}

void	convert_list_to_grid(t_game *game)
{
	t_map_list	*tmp;
	t_map_list	*next_node;
	int			i;

	if (game->map.height == 0 || !game->map.raw_lines)
		exit_err(game, "No map content found in file");
	game->map.grid = malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.grid)
		exit_err(game, "Malloc failed for grid array");
	tmp = game->map.raw_lines;
	i = 0;
	while (tmp)
	{
		game->map.grid[i] = tmp->line;
		next_node = tmp->next;
		free(tmp);
		tmp = next_node;
		i++;
	}
	game->map.grid[i] = NULL;
	game->map.raw_lines = NULL;
}
