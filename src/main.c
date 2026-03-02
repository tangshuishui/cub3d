/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 17:14:30 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/02 16:45:36 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	debug_print_parsed_data(t_game *game)
// {
// 	int i;

// 	printf("\n================ CUB3D PARSER TEST ================\n");
	
// 	printf("\n[1] TEXTURE PATHS:\n");
// 	printf("NO: [%s]\n", game->map.no_path);
// 	printf("SO: [%s]\n", game->map.so_path);
// 	printf("WE: [%s]\n", game->map.we_path);
// 	printf("EA: [%s]\n", game->map.ea_path);

// 	printf("\n[2] COLORS (Hex format):\n");
// 	// %06X 会把 int 按照 6 位大写十六进制输出，不足补 0
// 	printf("Floor   (F): 0x%06X\n", game->map.floor_color);
// 	printf("Ceiling (C): 0x%06X\n", game->map.ceil_color);

// 	printf("\n[3] PLAYER & CAMERA:\n");
// 	printf("Position (x, y)  : (%.2f, %.2f)\n", game->player.pos_x, game->player.pos_y);
// 	printf("Direction (x, y) : (%.2f, %.2f)\n", game->player.dir_x, game->player.dir_y);
// 	printf("Camera Plane     : (%.2f, %.2f)\n", game->player.plane_x, game->player.plane_y);

// 	printf("\n[4] MAP MATRIX (%d x %d):\n", game->map.width, game->map.height);
// 	i = 0;
// 	while (i < game->map.height)
// 	{
// 		// 打印每一行，并用 | 把地图包起来，这样能看清楚右边补齐的空格！
// 		printf("%02d |%s|\n", i, game->map.grid[i]);
// 		i++;
// 	}
// 	printf("===================================================\n\n");
// }

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

	// debug_print_parsed_data(&game);
	// free_all(&game);
	// printf("✅ Memory successfully freed. Test finished!\n");
	
	init_mlx(&game);
	init_loop_hooks(game.mlx, render_frame, &game);
	mlx_loop(game.mlx);
	return (0);
}
