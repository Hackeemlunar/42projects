# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmensah- <hmensah-@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/27 20:32:49 by hmensah-          #+#    #+#              #
#    Updated: 2025/04/06 18:50:40 by hmensah-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo_bonus
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

SRCS	=	ft_atol.c ft_arena.c philo_bonus.c util_bonus.c util_bonus1.c \
			fork_init.c
OBJS	=	$(SRCS:.c=.o)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re