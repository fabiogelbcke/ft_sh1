#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fschuber <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/23 12:50:23 by fschuber          #+#    #+#              #
#    Updated: 2018/04/23 13:07:33 by fschuber         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC = gcc

FLAGS = -Wall -Wextra -Werror

NAME = minishell

FILES =	ft_sh1.c \
		utils.c \
		utils2.c \
		cd.c \

F_DIR = srcs
SRCS = $(addprefix $(F_DIR)/, $(FILES))

O_DIR = objs
OBJS = $(addprefix $(O_DIR)/, $(FILES:.c=.o))

HEADER = ft_sh1.h
H_DIR = Includes
INC = $(addprefix $(H_DIR)/, $(HEADER))
INCLUDE = -I $(L_DIR) -I $(H_DIR)

L_DIR = libft
LIB = libft/libft.a
LIBLINK = -L ./$(L_DIR) -lft

all: libft $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(FLAGS) -o $@ $(OBJS) $(LIBLINK)

$(O_DIR)/%.o: $(F_DIR)/%.c $(INC)
	@mkdir -p $(O_DIR)
	@$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $<
	@echo "Creation de "$@" OK"

libft:
	@make -C $(L_DIR)

clean:
	rm -f $(OBJ)
	$(MAKE) -C ./libft clean

fclean:	clean
	rm -f $(NAME)
	$(MAKE) -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re libft
