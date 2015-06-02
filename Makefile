CC = gcc

FLAGS = -g -Wall -Wextra -Werror

SRC =		ft_sh1.c \
		utils.c \
		cd.c \

OBJ	= $(SRC:.c=.o)

LIB 	= libft/libft.a

NAME = ft_sh1

all:		$(NAME)

$(NAME):	$(OBJ)
	$(MAKE) -C ./libft
	$(CC) -o $(NAME) $(FLAGS) $(OBJ) $(LIB)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
