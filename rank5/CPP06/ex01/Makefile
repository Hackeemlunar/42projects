# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/10/17 17:53:39 by hmensah-          #+#    #+#              #
#    Updated: 2026/10/17 17:53:40 by hmensah-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Serializer
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
SRCS =	main.cpp Serializer.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re