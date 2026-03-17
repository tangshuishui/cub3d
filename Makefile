COLOR_GREEN	= \033[0;32m
COLOR_BLUE	= \033[0;34m
COLOR_RESET	= \033[0m

NAME		= cub3D
BONUS		= cub3D_bonus
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -rf

SRC_DIR		= src/
SRC_FILES   = main.c \
              events/hooks.c events/movement.c events/rotation.c \
              init/init_data.c init/init_mlx.c \
              parser/format_map.c parser/init_player.c parser/parse.c \
              parser/parse_color.c parser/parse_map.c parser/validate_map.c \
              render/calculate.c render/draw.c render/raycast.c render/render.c \
              utils/cleanup.c utils/time.c
SRC_B_DIR	= src_bonus/
SRC_B_FILES = main_bonus.c \
              events/hooks_bonus.c events/interact_bonus.c \
              events/movement_bonus.c events/rotation_bonus.c \
              init/init_data_bonus.c init/init_mlx_bonus.c \
              parser/format_map_bonus.c parser/init_player_bonus.c \
              parser/parse_bonus.c parser/parse_color_bonus.c \
              parser/parse_map_bonus.c parser/validate_map_bonus.c \
              render/calculate_bonus.c render/draw_bonus.c \
              render/minimap_bonus.c render/raycast_bonus.c render/render_bonus.c \
              utils/cleanup_bonus.c utils/time_bonus.c
OBJ_DIR		= obj/
LIBFT_DIR	= libft/
LIBFT		= $(LIBFT_DIR)libft.a
MLX_DIR		= mlx/
MLX			= $(MLX_DIR)libmlx.a

INCLU_DIR	= includes/
INCLU_B_DIR	= includes_bonus/
INCLUDES	= -I$(INCLU_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
INCLUDES_B	= -I$(INCLU_B_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
HEADER		= $(INCLU_DIR)cub3d.h
HEADER_B	= $(INCLU_B_DIR)cub3d_bonus.h

LDFLAGS		= -L/usr/lib -lXext -lX11 -lm -lz

SRCS        = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS		= $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

SRCS_B      = $(addprefix $(SRC_B_DIR), $(SRC_B_FILES))
OBJS_B		= $(patsubst $(SRC_B_DIR)%.c, $(OBJ_DIR)bonus/%.o, $(SRCS_B))

all: $(NAME)

$(LIBFT):
	@echo "$(COLOR_BLUE)Building Libft...$(COLOR_RESET)"
	@make -C $(LIBFT_DIR) > /dev/null 2>&1

$(MLX):
	@echo "$(COLOR_BLUE)Building MLX...$(COLOR_RESET)"
	@make -C $(MLX_DIR) > /dev/null 2>&1

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@echo "$(COLOR_BLUE)compilation begin...$(COLOR_RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -o $(NAME) $(LDFLAGS)
	@echo "$(COLOR_GREEN)compilation completed!$(COLOR_RESET)"

bonus: $(BONUS)

$(OBJ_DIR)bonus/%.o: $(SRC_B_DIR)%.c $(HEADER_B)
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) $(INCLUDES_B) $< -o $@

$(BONUS): $(OBJS_B) $(LIBFT) $(MLX)
	@echo "$(COLOR_BLUE)compilation begin...$(COLOR_RESET)"
	@$(CC) $(CFLAGS) $(OBJS_B) $(LIBFT) $(MLX) -o $(BONUS) $(LDFLAGS)
	@echo "$(COLOR_GREEN)compilation completed!$(COLOR_RESET)"

clean:
	@$(RM) -r $(OBJ_DIR)
	@make --no-print-directory -C $(LIBFT_DIR) clean > /dev/null 2>&1
	@make --no-print-directory -C $(MLX_DIR) clean > /dev/null 2>&1
	@echo "$(COLOR_GREEN)Objects removed$(COLOR_RESET)"

fclean: clean
	@$(RM) $(NAME) $(BONUS)
	@make --no-print-directory -C $(LIBFT_DIR) fclean > /dev/null 2>&1
	@make --no-print-directory -C $(MLX_DIR) clean > /dev/null 2>&1 || true
	@echo "$(COLOR_GREEN)All clear$(COLOR_RESET)"

re: fclean all

.PHONY: all clean fclean re