# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/21 18:06:33 by hmensah-          #+#    #+#              #
#    Updated: 2025/03/22 20:21:28 by hmensah-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex
CC			=	cc
ARGS		=	-Wall -Werror -Wextra
RM			=	rm -f

SRCS		=	parser.c pipex.c util.c
OBJS		=	$(SRCS:.c=.o)

BONUS_SRCS	=	pipex_bonus.c pipex_bonus_util1.c pipex_bonus_util2.c parser.c
BONUS_OBJS	=	$(BONUS_SRCS:.c=.o)

LIBFT_DIR	=	../libft

LIBFT		=	$(LIBFT_DIR)/libft.a

%.o: %.c
				$(CC) $(ARGS) -c $< -o $@

all			:	$(NAME)

bonus		:	$(LIBFT) $(BONUS_OBJS)
				$(CC) $(ARGS) $(BONUS_OBJS) -o $(NAME) $(LIBFT)

$(LIBFT)	:
				@$(MAKE) -C $(LIBFT_DIR)

$(NAME)		:	$(LIBFT) $(OBJS)
				$(CC) $(ARGS) $(OBJS) -o $(NAME) $(LIBFT)

clean		:
				@$(MAKE) -C $(LIBFT_DIR) clean
				$(RM) $(OBJS)
				$(RM) $(BONUS_OBJS)

fclean		:	clean
				@$(MAKE) -C $(LIBFT_DIR) fclean
				$(RM) $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re