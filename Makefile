# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/17 12:14:41 by ppepperm          #+#    #+#              #
#    Updated: 2020/05/26 19:42:03 by ppepperm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= Wolf3D
SRC :=	src/complex.c src/raycast.c src/main.c src/map.c src/doors.c\
		src/double.c src/events.c src/data.c src/textures.c src/checks.c src/errors.c\
		src/freeing.c src/put.c src/doors_horizontal.c src/doors_vertical.c
OBJ := $(SRC:%.c=%.o)
CFLAGS := -Wall -Wextra -Werror -I includes
LIB_FLAG :=  -L libft/ -lft `sdl2-config --libs --cflags` -O0
LINUX_FLAG := -L libft/ -lft `sdl2-config --libs --cflags` -O0  -lm
PATH_SDL := ./SDL2-2.0.12
INCLUDES := includes SDL2

all: $(NAME)

(SDL):
	cd $(PATH_SDL); ./configure --prefix=$(PATH_SDL)/..; make;
	make -sC $(PATH_SDL) install

%.o : src/%.c $(INCLUDES)
		gcc -c $(CFLAGS) -I $(INCLUDES) $SSRC -o
		@echo $(SSRC:src/%.c = %)

$(NAME): $(OBJ)
		@make -C libft
		@gcc -o $(NAME) $(CFLAGS) $(OBJ) $(LINUX_FLAG)
		@echo "DONE"

MAC : $(OBJ)
		@make -C libft
		@gcc -o $(NAME) $(CFLAGS) $(OBJ) $(LIB_FLAG)
		@echo "DONE"

clean:
		@rm -f $(OBJ)
		@make -C libft clean

fclean: clean
		@rm -f $(NAME)
		@make -C libft fclean

re: fclean $(NAME)

.PHONY: all clean fclean re

