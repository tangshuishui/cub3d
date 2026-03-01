/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 17:17:09 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/01 18:06:30 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include <stdlib.h>
# include "../mlx_linux/mlx.h"

# define WIN_WIDTH 800
# define WIN_HEIGHT 600


// 1. 纹理与图像数据结构 (MLX Image)
typedef struct s_img {
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

// 2. 玩家数据结构 (Player & Camera)
typedef struct s_player {
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	bool	key_w;
	bool	key_s;
	bool	key_a;
	bool	key_d;
	bool	key_left;
	bool	key_right;
}	t_player;

// 3. 射线与 DDA 计算专用结构体 (Raycaster)
// 包含在每次投射射线时需要刷新的变量
typedef struct s_ray {
	double	camera_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}	t_ray;

// 4. 地图与配置数据结构 (Map & Config)
typedef struct s_map {
	char	**grid;
	int		height;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_color;
	int		ceil_color;
}	t_map;

// 5. 游戏主结构体 (The God Struct)
typedef struct s_game {
	void		*mlx;
	void		*win;
	t_map		map;
	t_player	player;
	t_ray		ray;
	t_img		textures[4];
	t_img		screen;
}	t_game;

int		main(int ac, char **av);

//init
void	init_data(t_game *game);

#endif