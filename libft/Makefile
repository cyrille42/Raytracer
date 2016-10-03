#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ploulidi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/03/24 16:15:15 by ploulidi          #+#    #+#              #
#    Updated: 2016/04/28 16:34:55 by ploulidi         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libft.a

COLOR = color

SRC = 	ft_strcat.c ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c \
		ft_isascii.c ft_tabcpy.c ft_isdigit.c ft_isprint.c ft_memccpy.c ft_memcmp.c ft_memcpy.c \
		ft_memset.c ft_putchar.c ft_putstr.c ft_strchr.c ft_strcmp.c \
		ft_strcpy.c ft_strdup.c ft_strlcat.c ft_strlen.c ft_strncat.c ft_strncmp.c \
		ft_strncpy.c ft_puttab.c ft_strnstr.c ft_strrchr.c ft_strstr.c ft_tolower.c ft_toupper.c \
		ft_memchr.c ft_itoa.c ft_memalloc.c ft_memdel.c ft_putchar.c ft_putchar_fd.c \
		ft_putendl.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_putstr_fd.c ft_realloc.c ft_strclr.c ft_strdel.c ft_strequ.c ft_striter.c ft_striteri.c \
		ft_strjoin.c ft_strmap.c ft_strmapi.c ft_strnew.c ft_strsplit.c ft_strsub.c \
		ft_strtrim.c ft_strnequ.c ft_putnbr.c ft_memmove.c ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c

OBJ = $(SRC:.c=.o)

cc_red= "\033[0;31m"
cc_green= "\033[0;32m"
cc_yellow= "\033[0;33m"
cc_blue= "\033[0;34m"
cc_normal= "\033[m\017"

all: $(COLOR) $(NAME)

$(COLOR):
	@echo $(cc_green) 

$(NAME):  $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo ${cc_blue} : libft ${cc_normal}

%.o: %.c
	@gcc -Wall -Wextra -Werror -g -c $< 
	@echo -n .

clean:
	@rm -f $(OBJ)
	@echo ${cc_yellow} deleted file from libft ${cc_normal}

fclean: clean
	@rm -f $(NAME)

re: fclean all
