NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -lrt
HDRS = philo_bonus.h
SRCS = philo_bonus.c utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
    $(CC) $(CFLAGS) $(OBJS) -o $@

clean:
    rm -f $(OBJS)

fclean: clean
    rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
