# ==========================================
# 颜色定义
# ==========================================
COLOR_GREEN	= \033[0;32m
COLOR_BLUE	= \033[0;34m
COLOR_RESET	= \033[0m

# ==========================================
# 项目基础变量
# ==========================================
NAME		= cub3D
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3
RM			= rm -f

# ==========================================
# 目录与路径
# ==========================================
SRC_DIR		= src/
OBJ_DIR		= obj/
LIBFT_DIR	= libft/

INCLUDES	= -I ./includes -I ./$(LIBFT_DIR)
HEADER		= includes/cub3d.h

# ==========================================
# 库文件与链接参数 (Linux MLX环境为例)
# ==========================================
LIBFT		= $(LIBFT_DIR)libft.a
LDFLAGS		= -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

# ==========================================
# 源码与对象文件映射
# ==========================================
# 获取所有 src 及其子目录下的 .c 文件
SRCS_LIST	= $(wildcard $(SRC_DIR)*.c) \
			  $(wildcard $(SRC_DIR)init/*.c) \
			  $(wildcard $(SRC_DIR)parse/*.c) \
			  $(wildcard $(SRC_DIR)render/*.c) \
			  $(wildcard $(SRC_DIR)events/*.c) \
			  $(wildcard $(SRC_DIR)utils/*.c)

# 将 src/xxx.c 映射为 obj/xxx.o
OBJS		= $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS_LIST))

# ==========================================
# 编译规则
# ==========================================
all: $(NAME)

# 编译 libft (静默调用其 Makefile)
$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)

# 编译 .o 文件 (全程静默，自动创建对应子目录)
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

# 链接生成最终可执行文件，并打印提示
$(NAME): $(OBJS) $(LIBFT)
	@echo "$(COLOR_BLUE)compilation begin...$(COLOR_RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS)
	@echo "$(COLOR_GREEN)compilation completed!$(COLOR_RESET)"

# ==========================================
# 清理规则
# ==========================================
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