# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/09 20:31:29 by hmensah-          #+#    #+#              #
#    Updated: 2025/03/22 20:22:49 by hmensah-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= push_swap
NAME_BN		= checker

SRCS		= main.c push.c swap.c rotate.c reverse_rotate.c sort.c \
			  utils.c utils1.c merge_sort.c sort_util1.c sort_util2.c
OBJS		= $(SRCS:.c=.o)

SRCS_BNS	= main_bonus.c push_bonus.c swap_bonus.c rotate.c rrr_bonus.c \
			  utils.c utils1.c merge_sort.c
OBJS_BNS	= $(SRCS_BNS:.c=.o)

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

LIBFT_DIR	= ../libft
LIBFT	= $(LIBFT_DIR)/libft.a

all: $(NAME)
bonus: $(NAME_BN)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

$(NAME_BN): $(LIBFT) $(OBJS_BNS)
	$(CC) $(CFLAGS) -o $(NAME_BN) $(OBJS_BNS) $(LIBFT)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS_BNS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME_BN)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all bonus clean fclean re