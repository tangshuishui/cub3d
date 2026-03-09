/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 19:14:18 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/09 22:35:14 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

static void	parse_texture(t_game *game, char **path_ptr, char *line, int i)
{
	int	start;
	int	end;

	if (*path_ptr != NULL)
		exit_err(game, "Duplicate texture definition");
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		i++;
	end = i;
	if (start == end)
		exit_err(game, "Missing texture path");
	*path_ptr = ft_substr(line, start, end - start);
	if (!*path_ptr)
		exit_err(game, "Malloc failed for texture path");
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] != '\n' && line[i] != '\0')
		exit_err(game, "Garbage found after texture path");
}

static int	valid_elem(char *line, char *id)
{
	int	len;

	len = ft_strlen(id);
	if (ft_strncmp(line, id, len) == 0 && (line[len] == ' ' || line[len] == '\t'))
		return (1);
	return (0);
}

static void	parse_config(t_game *game, char *line, int *elements)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (valid_elem(&line[i], "NO"))
		parse_texture(game, &game->map.no_path, line, i + 2);
	else if (valid_elem(&line[i], "SO"))
		parse_texture(game, &game->map.so_path, line, i + 2);
	else if (valid_elem(&line[i], "WE"))
		parse_texture(game, &game->map.we_path, line, i + 2);
	else if (valid_elem(&line[i], "EA"))
		parse_texture(game, &game->map.ea_path, line, i + 2);
	else if (valid_elem(&line[i], "DO"))
		parse_texture(game, &game->map.d_path, line, i + 2);
	else if (valid_elem(&line[i], "F"))
		parse_color(game, &game->map.floor_color, line, i + 1);
	else if (valid_elem(&line[i], "C"))
		parse_color(game, &game->map.ceil_color, line, i + 1);
	else
		exit_err(game, "Invalid configuration element");
		
	(*elements)++;
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
			if (elements < 7)
				parse_config(game, line, &elements);
			else
				parse_map(game, line);
		}
		else if (elements == 7 && game->map.raw_lines != NULL)
		{
			free(line);
			exit_err(game, "Empty line inside or after the map");
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	convert_list_to_grid(game);
	if (game->map.grid == NULL)
		exit_err(game, "No map found in file");
	format_map(game);
	validate_map(game);
}
