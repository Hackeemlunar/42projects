# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/16 17:53:25 by hmensah-          #+#    #+#              #
#    Updated: 2025/08/17 17:44:07 by hmensah-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 'Moar brainz!'

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SOURCES = main.cpp Zombie.cpp zombieHorde.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
