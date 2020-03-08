# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+         #n
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/17 12:14:41 by ppepperm          #+#    #+#              #
#    Updated: 2019/11/17 12:14:43 by ppepperm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= 2D_ray
SRC := kekush.c line.c player.c
OBJ := $(patsubst %.c, %.o, $(SRC))
CFLAGS := -Wall -Wextra -Werror -I includes
LIB_FLAG :=  -L libft/ -lft `sdl2-config --libs --cflags` -O0 -framework OpenCl
LINUX_FLAG := -L libft/ -lft `sdl2-config --libs --cflags` -O0 -lSDL2_image -l OpenCL -lm
INCLUDES := .

all: $(NAME)

%.o : src/%.c $(INCLUDES)
		@gcc -c $(CFLAGS) -I $(INCLUDES) $< -o $@
		@echo $(patsubst src/%.c, %, $<)

$(NAME): $(OBJ)
		@make -C libft
		@gcc -o $(NAME) $(CFLAGS) $(OBJ) $(LIB_FLAG)
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

