# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/27 20:32:49 by hmensah-          #+#    #+#              #
#    Updated: 2025/05/06 15:20:41 by hmensah-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo_bonus
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

SRCS	=	philo_bonus.c utils.c
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