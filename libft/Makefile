# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yshi <yshi@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/18 11:10:25 by yshi              #+#    #+#              #
#    Updated: 2026/01/20 17:55:40 by yshi             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

SRC_DIR		= handle_format

SRCS		= 	ft_atoi.c		ft_isdigit.c	ft_memchr.c		ft_putendl_fd.c	ft_striteri.c	\
				ft_strncmp.c	ft_toupper.c	ft_bzero.c		ft_isprint.c	ft_memcmp.c		\
				ft_putnbr_fd.c	ft_strjoin.c	ft_strnstr.c	ft_calloc.c		ft_itoa.c		\
				ft_memcpy.c		ft_putstr_fd.c	ft_strlcat.c	ft_strrchr.c 	ft_isalnum.c	\
				ft_memset.c		ft_split.c		ft_strlcpy.c	ft_strtrim.c	ft_memmove.c	\
				ft_strchr.c		ft_strlen.c		ft_substr.c		ft_isascii.c	ft_putchar_fd.c	\
				ft_strdup.c		ft_strmapi.c	ft_tolower.c	ft_isalpha.c	ft_printf.c		\
				ft_atol.c		ft_atof.c		ft_strcmp.c 	ft_printf.c		ft_printf_fd.c	\
				ft_printf_fd_util.c		ft_printf_fd_util1.c 	ft_realloc.c \
				ft_lstdelone_bonus.c	ft_lstiter_bonus.c		ft_lstlast_bonus.c	ft_lstadd_back_bonus.c	\
				ft_lstmap_bonus.c		ft_lstadd_front_bonus.c	ft_lstnew_bonus.c	ft_lstclear_bonus.c		\
				ft_lstsize_bonus.c	\
				get_next_line.c	get_next_line_utils.c
SRCS_SUB	=	handle_char.c \
				handle_dec.c \
				handle_hex.c \
				handle_pct.c \
				handle_ptr.c \
				handle_udec.c \
				hanle_str.c
SRCS_ALL	=	$(SRCS)  $(addprefix $(SRC_DIR)/, $(SRCS_SUB))

OBJS		=	$(SRCS_ALL:.c=.o)

HEADERS		=	libft.h

CFLAGS		=	-Wall -Wextra -Werror -I ./ -I ./handle_format
CC			=	cc

all: $(NAME)

$(NAME): $(OBJS)
	ar crs $(NAME) $(OBJS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

