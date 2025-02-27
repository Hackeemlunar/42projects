# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/27 20:14:17 by hmensah-          #+#    #+#              #
#    Updated: 2025/02/27 20:44:37 by hmensah-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fractol
CC			=	cc
ARGS		=	-Wall -Werror -Wextra
RM			=	rm -f

SRCS		=	fractol.c

# OBJS		=	$(SRC:.c=.o)

# BONUS_SRCS	=	

LIBFT_DIR	=	./libft

LIBFT		=	$(LIBFT_DIR)/libft.a

all			:	$(NAME)

$(LIBFT)	:
				@$(MAKE) -C $(LIBFT_DIR)

$(NAME)		:	$(LIBFT)
				$(CC) $(SRCS) -Lmlx_mac -lmlx -Llibft -lft -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c
	$(CC) $(ARGS) -Imlx_mac -c $< -o $@

clean		:
				@$(MAKE) -C $(LIBFT_DIR) clean

fclean		:
				@$(MAKE) -C $(LIBFT_DIR) fclean
				$(RM) $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re