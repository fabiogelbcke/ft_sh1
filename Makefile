CC = gcc

FLAGS = -Wall -Wextra -Werror

SRC =	ft_ls.c \
	list_management.c \
	print_long.c \

OBJ	= $(SRC:.c=.o)

LIB 	= libft/libft.a

NAME = ft_ls

all:		$(NAME)

$(NAME):	$(OBJ)
	$(MAKE) -C ./libft
	$(CC) -o $(NAME) $(FLAGS) $(OBJ) $(LIB)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm $(NAME)

re: fclean all

.PHONY: all clean fclean re
