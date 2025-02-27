# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/21 18:06:33 by hmensah-          #+#    #+#              #
#    Updated: 2025/02/27 18:36:10 by hmensah-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex
CC			=	cc
ARGS		=	-Wall -Werror -Wextra
RM			=	rm -f

SRCS		=	parser.c pipex.c util.c

BONUS_SRCS	=	pipex_bonus.c pipex_bonus_util1.c pipex_bonus_util2.c \
				parser.c

LIBFT_DIR	=	./libft

LIBFT		=	$(LIBFT_DIR)/libft.a

all			:	$(NAME)

bonus		:	$(LIBFT)
				$(CC) $(ARGS) $(BONUS_SRCS) -o $(NAME) $(LIBFT)

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