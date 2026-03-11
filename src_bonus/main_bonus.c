/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshi <yshi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 17:14:30 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/11 14:53:09 by yshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	check_name(char *filename)
{
	int	len;

	len = 0;
	while (filename[len])
		len++;
	if (len < 4)
		return (0);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2 || !check_name(av[1]))
	{
		printf("Error\nInvalid arguments. Usage: ./cub3d <map.cub>\n");
		return (1);
	}
	init_data(&game);
	parsing(&game, av[1]);
	convert_list_to_grid(&game);
	if (game.map.grid == NULL)
		exit_err(&game, "No map found in file");
	format_map(&game);
	validate_map(&game);
	init_mlx(&game);
	init_textures(&game);
	init_hooks(&game);
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_loop(game.mlx);
	return (0);
}
