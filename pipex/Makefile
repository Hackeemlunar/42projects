# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/21 18:06:33 by hmensah-          #+#    #+#              #
#    Updated: 2025/02/23 16:50:27 by hmensah-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex
CC			=	cc
ARGS		=	-Wall -Werror -Wextra
RM			=	rm -f

SRCS		=	parser.c pipex.c util.c

LIBFT_DIR	=	./libft
LIBFT		=	$(LIBFT_DIR)/libft.a

all			:	$(NAME)

$(LIBFT)	:
				@$(MAKE) -C $(LIBFT_DIR)

$(NAME)		:	$(LIBFT)
				$(CC) $(ARGS) $(SRCS) -o $(NAME) $(LIBFT)

clean		:
				@$(MAKE) -C $(LIBFT_DIR) clean
fclean		:
				@$(MAKE) -C $(LIBFT_DIR) fclean
				$(RM) $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re