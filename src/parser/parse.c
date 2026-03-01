/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 19:14:18 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/01 19:34:52 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// 检查该行是否是空行
static int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (1);
	return (0);
}

// 提取纹理路径
static void	parse_texture(t_game *game, char **path_ptr, char *line, int i)
{
	int	start;
	int	end;

	if (*path_ptr != NULL) // 如果已经有了，说明文件里重复定义了，报错
		exit_err(game, "Duplicate texture definition");
	
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '\n')
		i++;
	end = i;
	
	*path_ptr = ft_substr(line, start, end - start);
	if (!*path_ptr)
		exit_err(game, "Malloc failed for texture path");
}

// 调度器：根据标识符分配任务
void	parse_config(t_game *game, char *line, int *elements)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	// 判断前两个字符
	if (ft_strncmp(&line[i], "NO ", 3) == 0)
		parse_texture(game, &game->map.no_path, line, i + 2);
	else if (ft_strncmp(&line[i], "SO ", 3) == 0)
		parse_texture(game, &game->map.so_path, line, i + 2);
	else if (ft_strncmp(&line[i], "WE ", 3) == 0)
		parse_texture(game, &game->map.we_path, line, i + 2);
	else if (ft_strncmp(&line[i], "EA ", 3) == 0)
		parse_texture(game, &game->map.ea_path, line, i + 2);
	else if (ft_strncmp(&line[i], "F ", 2) == 0)
		parse_color(game, &game->map.floor_color, line, i + 1);
	else if (ft_strncmp(&line[i], "C ", 2) == 0)
		parse_color(game, &game->map.ceil_color, line, i + 1);
	else
		exit_error(game, "Invalid configuration element");
		
	(*elements)++;
}

void	parse_map(t_game *game, char *line)
{
	char	*temp;
	int		i;

	// 1. 检查地图里的字符是否合法 (只能是 1, 0, N, S, E, W, 空格, 和末尾的 \n)
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!ft_strchr("01NSEW ", line[i]))
			exit_err(game, "Invalid character in map");
		i++;
	}

	// 2. 用 ft_strjoin 把新读到的一行拼接到 raw_map_str 上
	if (game->map.raw_map_str == NULL)
	{
		game->map.raw_map_str = ft_strdup(line);
	}
	else
	{
		temp = ft_strjoin(game->map.raw_map_str, line);
		free(game->map.raw_map_str);
		game->map.raw_map_str = temp;
	}
}

void	parsing(t_game *game, char *filename)
{
	int		fd;
	char	*line;
	int		elements;

	elements = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_err(game, "Cannot open .cub file");
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!is_empty_line(line))
		{
			if (elements < 6)
			{
				// 还没找齐 6 个配置，去解析路径和颜色
				parse_config(game, line, &elements);
			}
			else
			{
				// 已经找齐 6 个配置，剩下的统统当成地图来读
				// 注意：如果地图中间出现空行，要在 parse_map 里报错
				parse_map(game, line);
			}
		}
		else if (elements == 6 && game->map.grid != NULL)
		{
			// 如果已经开始读地图了，又遇到了空行 -> 报错！(地图内不允许空行)
			free(line);
			exit_err(game, "Empty line inside or after the map");
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	
	// 读完文件后，检查是否真的读到了地图
	if (game->map.grid == NULL)
		exit_err(game, "No map found in file");
		
	// 最后，把地图补齐成矩形，并检查封闭性
	format_and_validate_map(game);
}
