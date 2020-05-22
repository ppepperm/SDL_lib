# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/17 12:14:41 by ppepperm          #+#    #+#              #
#    Updated: 2019/11/17 12:14:43 by ppepperm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= Wolf3D
SRC :=	complex.c raycast.c main.c map.c doors.c\
		double.c events.c data.c textures.c checks.c errors.c\
		freeing.c put.c doors_horizontal.c doors_vertical.c
OBJ := $(SRC:%.c=%.o)
CFLAGS := -Wall -Wextra -Werror -I includes
LIB_FLAG :=  -L libft/ -lft `sdl2-config --libs --cflags` -O0
LINUX_FLAG := -L libft/ -lft `sdl2-config --libs --cflags` -O0  -lm
INCLUDES := .

all: $(NAME)

%.o : src/%.c $(INCLUDES)
		gcc -c $(CFLAGS) -I $(INCLUDES) $SSRC -o
		@echo $(SSRC:src/%.c = %)

$(NAME): $(OBJ)
		@make -C libft
		@gcc -o $(NAME) $(CFLAGS) $(OBJ) $(LINUX_FLAG)
		@echo "DONE"

LINUX : $(OBJ)
		@make -C libft
		@gcc -o $(NAME) $(CFLAGS) $(OBJ) $(LINUX_FLAG)
		@echo "DONE"

clean:
		@rm -f $(OBJ)
		@make -C libft clean

fclean: clean
		@rm -f $(NAME)
		@make -C libft fclean

re: fclean $(NAME)

.PHONY: all clean fclean re

