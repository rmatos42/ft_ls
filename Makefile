NAME = ft_ls

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = gnl/get_next_line.c src/*.c


INCLUDE = -I includes

INCLUDE_LIBFT = -I libft/includes
LINK_LIBFT = -L libft/ -lft
LIBFT = $(INCLUDE_LIBFT) $(LINK_LIBFT)

GNL = -I gnl

all: $(NAME)

libft.a:
	make -C libft

$(NAME): libft.a
	$(CC) $(LIBFT) $(INCLUDE) $(GNL) $(SRC) -o $(NAME)

clean:
	make -C libft fclean

fclean: clean
	rm -rf $(NAME)

re: clean all
