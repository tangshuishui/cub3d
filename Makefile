COLOR_GREEN	= \033[0;32m
COLOR_BLUE	= \033[0;34m
COLOR_RESET	= \033[0m

NAME		= cub3D
BONUS		= cub3D_bonus
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -rf

SRC_DIR		= src/
SRC_B_DIR	= src_bonus/
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

SRCS	= $(shell find $(SRC_DIR) -name "*.c")
OBJS	= $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

SRCS_B	= $(shell find $(SRC_B_DIR) -name "*.c")
OBJS_B	= $(patsubst $(SRC_B_DIR)%.c, $(OBJ_DIR)bonus/%.o, $(SRCS_B))

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