# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/27 22:18:20 by mertcaki          #+#    #+#              #
#    Updated: 2024/10/27 22:19:30 by mertcaki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= philo

CC = gcc

CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

SRC = main.c \
		argument_control.c \
		utils.c \
		threads_start.c \
		create.c

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) -c $(SRC)
		$(CC) $(CFLAGS) -o $(NAME) $(SRC)

all: $(NAME)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)
re: fclean all

r: re
f: fclean
c: clean

.phony: all clean fclean re
