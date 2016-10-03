#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ploulidi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/03/24 16:15:15 by ploulidi          #+#    #+#              #
#    Updated: 2016/05/20 13:30:39 by rcargou          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = Rt

SRC = main.c graph.c graph_tool.c error.c image.c key.c object.c pars_obj.c math.c\
		ft_atof.c get_next_line.c beahivor.c bmp.c menu.c gen_scene.c texture.c video_player.c tool.c object_norme.c pars_obj2.c gen_scene_2.c color.c color_next.c graph_next.c key_next.c

HD = rt.h get_next_line.h

LIB = libft/libft.a

LIBMLX = ./minilibx_macos/libmlx.a -framework OpenGL -framework AppKit -framework opencl

INC = -I ./libft/

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra -g

cc_red= "\033[0;31m"
cc_green= "\033[0;32m"
cc_yellow= "\033[0;33m"
cc_blue= "\033[0;34m"
cc_normal= "\033[m\017"

all: $(LIB) $(NAME)

$(LIB):
	@make -C ./libft/
	@make -C ./minilibx_macos
	@echo ${cc_green}

$(NAME): $(OBJ)
	@gcc -o $(NAME) $(OBJ) -O3 $(LIB) $(LIBMLX) $(INC) -g
	@echo ${cc_blue} : $(NAME)  ${cc_normal}

%.o: %.c $(HD)
	@gcc $(FLAGS) -c $< $(INC)
	@echo -n .

clean:
	@rm -f $(OBJ)
	@echo ${cc_yellow} deleted file from $(NAME) ${cc_normal}

fclean: clean
	@make -C ./libft fclean
	@make -C ./minilibx_macos clean
	@rm -f $(NAME)

re: fclean all
