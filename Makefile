COLOR_GREEN	= \033[0;32m
COLOR_BLUE	= \033[0;34m
COLOR_RESET	= \033[0m

NAME		= cub3D
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3
RM			= rm -f

SRC_DIR		= src/
OBJ_DIR		= obj/
LIBFT_DIR	= libft/
LIBFT		= $(LIBFT_DIR)libft.a
MLX_DIR		= mlx/

INCLU_DIR	= includes/
HEADER		= $(INCLU_DIR)cub3d.h

INCLUDES	= -I$(INCLU_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

LDFLAGS		= -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz

SRCS	= $(shell find $(SRC_DIR) -name "*.c")

OBJS		= $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

all: $(NAME)

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(COLOR_BLUE)compilation begin...$(COLOR_RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS)
	@echo "$(COLOR_GREEN)compilation completed!$(COLOR_RESET)"

clean:
	@$(RM) -r $(OBJ_DIR)
	@make --no-print-directory -C $(LIBFT_DIR) clean
	@echo "$(COLOR_GREEN)Objects removed$(COLOR_RESET)"

fclean: clean
	@$(RM) $(NAME)
	@make --no-print-directory -C $(LIBFT_DIR) fclean
	@echo "$(COLOR_GREEN)all clear$(COLOR_RESET)"

re: fclean all

.PHONY: all clean fclean re