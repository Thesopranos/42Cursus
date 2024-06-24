# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/07 15:30:15 by mertcaki          #+#    #+#              #
#    Updated: 2024/06/08 01:58:02 by mertcaki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
LIBFT = libft
LIBFTM = libft/libft.a
CC = gcc -g
CFLAGS = -Wall -Wextra -Werror

CFILES = 	ps_utils.c \
	sort_function.c \
	small_sort_func.c \
	sort.c \
	transactions_a.c \
	transactions_b.c \
	transactions_ab.c \
	quick_sort.c \
	free_error.c \
	get_next_line.c \
	push_swap.c \

OBJS = $(CFILES:.c=.o)

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFTM) -o $(NAME)
	@echo "\n\033[1;32mPush_swap is ready ✅\033[0m\n"

all: $(NAME)
	@echo "\n\033[1;32mAll files compiled successfully ✅\033[0m\n"

clean: pic
	@make clean -C $(LIBFT)
	@rm -f $(OBJS)
	@echo "\n\033[1;32mObjects files deleted ✅\033[0m\n"

fclean: clean
	@make fclean -C $(LIBFT)
	@rm -rf $(NAME)
	@echo "\n\033[1;32mArchive file deleted ✅\033[0m\n"

re: fclean all

pic:
	@echo "\n\033[1;32m<<<< -------------------------------------------------- >>>>\033[0m\n"

.PHONY: all clean fclean re pic
