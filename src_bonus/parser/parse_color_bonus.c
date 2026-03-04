/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 11:39:09 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/04 16:03:56 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	check_commas(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == ',')
			count++;
		i++;
	}
	return (count);
}

static int	parse_rgb_value(char **ptr)
{
	int	val;
	int	digits;

	val = 0;
	digits = 0;
	while (**ptr == ' ' || **ptr == '\t')
		(*ptr)++;
	if (!ft_isdigit(**ptr))
		return (-1);
	while (ft_isdigit(**ptr))
	{
		val = val * 10 + (**ptr - '0');
		digits++;
		if (val > 255 || digits > 3)
			return (-1);
		(*ptr)++;
	}
	while (**ptr == ' ' || **ptr == '\t')
		(*ptr)++;
	return (val);
}

void	parse_color(t_game *game, int *color_ptr, char *line, int i)
{
	char	*ptr;
	int		r;
	int		g;
	int		b;

	if (*color_ptr != -1)
		exit_err(game, "Duplicate color definition");
	ptr = line + i;
	if (check_commas(ptr) != 2)
		exit_err(game, "Invalid color format: wrong number of commas");
	r = parse_rgb_value(&ptr);
	if (r == -1 || *ptr != ',')
		exit_err(game, "Invalid Red value");
	ptr++;
	g = parse_rgb_value(&ptr);
	if (g == -1 || *ptr != ',')
		exit_err(game, "Invalid Green value");
	ptr++;
	b = parse_rgb_value(&ptr);
	if (b == -1)
		exit_err(game, "Invalid Blue value");
	if (*ptr != '\n' && *ptr != '\0')
		exit_err(game, "Garbage after color values");
	*color_ptr = (r << 16) | (g << 8) | b;
}
