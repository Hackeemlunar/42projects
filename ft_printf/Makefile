NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
# CFLAGS = -Wall
AR = ar rcs
RM = rm -f

SRCS = ft_printf.c parser.c processor.c processor1.c converters.c
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_OBJS = $(LIBFT_DIR)/*.o

all: $(NAME)

bonus: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	@cp $(LIBFT_DIR)/*.o .
	$(AR) $(NAME) $(OBJS) *.o
	@$(RM) *.o

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OBJS) *.o

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
