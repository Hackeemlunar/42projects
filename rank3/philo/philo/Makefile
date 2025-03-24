NAME	=	philo
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

SRCS	=	philo.c ft_atoi.c sleep.c think.c eat.c ft_arena.c util.c
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