# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/27 20:14:17 by hmensah-          #+#    #+#              #
#    Updated: 2025/03/10 18:16:02 by hmensah-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = fractol
CC          = cc
CFLAGS      = -g -Wall -Werror -Wextra
RM          = rm -f

SRCS        = fractol.c  image.c utils.c event_handlers.c
OBJS        = $(SRCS:.c=.o)

LIBFT_DIR   = ./libft
LIBFT       = $(LIBFT_DIR)/libft.a

PLATFORM    = linux
# PLATFORM    = macos

ifeq ($(PLATFORM), linux)
	MLX_DIR     = mlx_linux
	MLX_LIBS    = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
else ifeq ($(PLATFORM), macos)
	MLX_DIR     = mlx_mac
	MLX_LIBS    = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

all: $(NAME)

$(LIBFT):
		$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) $(MLX_LIBS) -L$(LIBFT_DIR) -lft -o $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

clean:
		$(MAKE) -C $(LIBFT_DIR) clean
		$(RM) $(OBJS)

fclean: clean
		$(MAKE) -C $(LIBFT_DIR) fclean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re