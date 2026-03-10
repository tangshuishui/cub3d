/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 12:12:59 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/10 15:14:22 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_map_chars(t_game *game, char *line)
{
	int	i;

	//检查地图里的字符是否合法 (只能是 1, 0, N, S, E, W, 空格, 和末尾的 \n)
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
		free(clean_line); // 创建节点失败时，别忘了释放刚才扒下来的字符串
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

	// 1. 一次性精确分配所有行的指针空间 (+1 为了最后的 NULL)
	game->map.grid = malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.grid)
		exit_err(game, "Malloc failed for grid array");

	// 2. 遍历链表，转移指针所有权，并摧毁节点空壳
	tmp = game->map.raw_lines;
	i = 0;
	while (tmp)
	{
		game->map.grid[i] = tmp->line;// 指针交接 (Zero-Copy!)
		next_node = tmp->next;
		free(tmp);// 注意：只释放节点，千万别释放 tmp->line
		tmp = next_node;
		i++;
	}
	game->map.grid[i] = NULL;
	
	// 3. 将临时链表头置空，防止后续 cleanup 重复 free
	game->map.raw_lines = NULL; 
}
