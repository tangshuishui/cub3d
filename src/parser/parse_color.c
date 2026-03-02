/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 11:39:09 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/02 11:50:47 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

// 提取一个 RGB 数字，同时推进指针。如果格式错误，返回 -1。
static	int parse_rgb_value(char **ptr)
{
	int	val;
	int	digits;

	val = 0;
	digits = 0;
	// 1. 跳过数字前面的空白字符
	while (**ptr == ' ' || **ptr == '\t')
		(*ptr)++;
		
	// 2. 如果跳过空白后不是数字（比如遇到了逗号、负号、字母、或者直接结束了）
	if (!ft_isdigit(**ptr))
		return (-1);
		
	// 3. 提取数字，同时防越界
	while (ft_isdigit(**ptr))
	{
		val = val * 10 + (**ptr - '0');
		digits++;
		// 任何单个颜色值不能超过 255，且位数不能超过3位 (防止 0000000 这种恶搞)
		if (val > 255 || digits > 3)
			return (-1);
		(*ptr)++;
	}
	
	// 4. 跳过数字后面的空白字符，直到碰到逗号或结尾
	while (**ptr == ' ' || **ptr == '\t')
		(*ptr)++;
		
	return (val);
}

// 将传入的 i 设置为指向 'F' 或 'C' 后面的第一个字符
void	parse_color(t_game *game, int *color_ptr, char *line, int i)
{
	char	*ptr;
	int		r;
	int		g;
	int		b;

	if (*color_ptr != -1) // -1 是我们在 init_data 中设置的初始值
		exit_err(game, "Duplicate color definition");

	ptr = line + i;
	if (check_commas(ptr) != 2)
		exit_err(game, "Invalid color format: wrong number of commas");

	r = parse_rgb_value(&ptr);
	if (r == -1 || *ptr != ',')
		exit_err(game, "Invalid Red value");
	ptr++; // 跨过第一个逗号

	g = parse_rgb_value(&ptr);
	if (g == -1 || *ptr != ',')
		exit_err(game, "Invalid Green value");
	ptr++; // 跨过第二个逗号

	b = parse_rgb_value(&ptr);
	if (b == -1)
		exit_err(game, "Invalid Blue value");

	// 最后的防线：检查 B 值之后是否还有垃圾字符 (除了换行和结束符)
	if (*ptr != '\n' && *ptr != '\0')
		exit_err(game, "Garbage after color values");

	// 使用位运算将 R, G, B 合并成一个 24 位的整型颜色
	*color_ptr = (r << 16) | (g << 8) | b;
}
