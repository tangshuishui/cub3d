/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 17:17:09 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/06 17:33:59 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "libft.h"
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include <stdlib.h>
# include "../mlx/mlx.h"

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

# define TEX_NORTH 0
# define TEX_SOUTH 1
# define TEX_WEST 2
# define TEX_EAST 3
# define TEX_DOOR 4

// Linux X11 Keycodes
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_SPACE 32

# define MOVE_SPEED 3.0
# define ROT_SPEED 1.5

# define MOUSE_SENS 0.5

# define MMAP_TILE 15//小地图中每一个方格占多少像素
# define MMAP_VIEW 4//向四周看多远（例如看 4 格，小地图就是 9x9 的网格）
# define MMAP_OFFSET 20
# define MMAP_SIZE ((2 * MMAP_VIEW + 1) * MMAP_TILE)

typedef struct s_img {
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

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

// hit = 2 hit the door
typedef struct s_ray {
	double	camera_x;
	double	dir_x;
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
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_dir;
	double	wall_x;
	int		tex_x;
}	t_ray;

typedef struct s_map_list {
	char				*line;
	struct s_map_list	*next;
}	t_map_list;

typedef struct s_map {
	char		**grid;
	int			width;
	int			height;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	char		*d_path;
	int			floor_color;
	int			ceil_color;
	t_map_list	*raw_lines;
}	t_map;

typedef struct s_poster {
	t_img	anim_wall[8];// 海报有 8 帧
	int		anim_frames;
	unsigned long long	last_anim_time;
}	t_poster;

typedef struct s_game {
	void		*mlx;
	void		*win;
	t_map		map;
	t_player	player;
	t_ray		ray;
	t_img		textures[5];
	t_img		screen;
	unsigned long long	last_time;
	double		frame_time;
	t_poster	anim;
}	t_game;

int		main(int ac, char **av);

//init
void	init_data(t_game *game);
void	init_mlx(t_game *game);
void	init_textures(t_game *game);
void	exit_err(t_game *game, char *msg);


//parse
void	parsing(t_game *game, char *filename);
void	parse_color(t_game *game, int *color_ptr, char *line, int i);
void	parse_map(t_game *game, char *line);
void	convert_list_to_grid(t_game *game);
void	format_map(t_game *game);
void	validate_map(t_game *game);
void	init_player_position(t_game *game, int x, int y, char dir);

//render
int		render_frame(t_game *game);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	cast_rays(t_game *game);
void	cal_lineheight(t_game *game);
void	determine_texture(t_game *game);
void	cal_texture(t_game *game);
void	draw_vertical_stripe(t_game *game, int x);
void	draw_minimap(t_game *game);

//events
void	init_hooks(t_game *game);
int		key_press(int keycode, t_game *game);
int 	key_release(int keycode, t_game *game);
int 	close_window(t_game *game);
int		mouse_move_hook(int x, int y, t_game *game);
void	open_door(t_game *game);
void	player_move(t_game *game);
void	player_rotate(t_game *game);
void	rotate_vectors(t_player *p, double rot_speed);

//utils
void	free_all(t_game *game);
unsigned long long	get_time_ms(void);
void	set_frame(t_game *game);

#endif
