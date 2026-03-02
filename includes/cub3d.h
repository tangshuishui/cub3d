/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 17:17:09 by hanwang           #+#    #+#             */
/*   Updated: 2026/03/02 17:11:34 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include <stdlib.h>
# include "../mlx/mlx.h"

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
}	t_ray;

typedef struct s_map_list {
	char				*line;
	struct s_map_list	*next;
}	t_map_list;

// 4. 地图与配置数据结构 (Map & Config)
typedef struct s_map {
	char		**grid;
	int			width;
	int			height;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	int			floor_color;
	int			ceil_color;
	t_map_list	*raw_lines;
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
void	init_mlx(t_game *game);
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


//utils
void	free_all(t_game *game);

#endif

/*// 1. 纹理与图像数据结构 (MLX Image)
typedef struct s_img {
    void    *img_ptr;     // MLX 图像指针
    char    *addr;        // 像素数据内存地址
    int     bpp;          // Bits Per Pixel
    int     line_len;     // Line length
    int     endian;       // Endianness
    int     width;        // 图像宽度
    int     height;       // 图像高度
} t_img;

// 2. 玩家数据结构 (Player & Camera)
typedef struct s_player {
    double  pos_x;        // 玩家绝对X坐标
    double  pos_y;        // 玩家绝对Y坐标
    double  dir_x;        // 方向向量X分量 (例如北是 0, -1)
    double  dir_y;        // 方向向量Y分量
    double  plane_x;      // 相机平面X分量 (决定FOV)
    double  plane_y;      // 相机平面Y分量
    bool    key_w;        // 移动按键状态
    bool    key_s;
    bool    key_a;
    bool    key_d;
    bool    key_left;     // 视角旋转按键状态
    bool    key_right;
} t_player;

// 3. 射线与 DDA 计算专用结构体 (Raycaster)
// 包含在每次投射射线时需要刷新的变量
typedef struct s_ray {
    double  camera_x;     // 当前屏幕垂直线在相机平面上的位置 (-1 到 1)
    double  dir_x;        // 射线方向X
    double  dir_y;        // 射线方向Y
    int     map_x;        // 射线当前所在的网格X
    int     map_y;        // 射线当前所在的网格Y
    double  side_dist_x;  // 射线当前位置到下一个X网格线的距离
    double  side_dist_y;  // 射线当前位置到下一个Y网格线的距离
    double  delta_dist_x; // 射线在X轴移动1个单位实际跨越的距离
    double  delta_dist_y; // 射线在Y轴移动1个单位实际跨越的距离
    double  perp_wall_dist;// 最终计算的垂直墙壁距离 (防止鱼眼)
    int     step_x;       // DDA跳跃方向 (-1 或 1)
    int     step_y;
    int     hit;          // 是否撞墙 (1/0)
    int     side;         // 撞击的是NS墙(0)还是EW墙(1)
} t_ray;

// 4. 地图与配置数据结构 (Map & Config)
typedef struct s_map {
    char    **grid;       // 二维数组存放地图 (以空格补齐的矩形)
    int     width;        // 地图最大宽度
    int     height;       // 地图高度
    char    *no_path;     // 北墙纹理路径
    char    *so_path;     // 南墙纹理路径
    char    *we_path;     // 西墙纹理路径
    char    *ea_path;     // 东墙纹理路径
    int     floor_color;  // 地板RGB转成的十六进制颜色 (例如 0xRRGGBB)
    int     ceil_color;   // 天花板颜色
} t_map;

// 5. 游戏主结构体 (The God Struct)
typedef struct s_game {
    void        *mlx;         // MLX 实例指针
    void        *win;         // 窗口指针
    t_map       map;          // 地图与配置
    t_player    player;       // 玩家状态
    t_ray       ray;          // 射线计算状态
    t_img       textures[4];  // 存放已加载的4个方向的墙壁纹理 (0:NO, 1:SO, 2:WE, 3:EA)
    t_img       screen;       // 屏幕双缓冲图像 (每帧画好后一次性推入窗口)
} t_game;*/