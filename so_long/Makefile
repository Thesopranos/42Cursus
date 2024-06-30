# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/30 23:27:06 by mertcaki          #+#    #+#              #
#    Updated: 2024/06/30 23:27:07 by mertcaki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	so_long

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror
AR				=	ar
ARFLAGS 		=	rcs
RM				=	rm -rf

SRC				=	map_control.c map_bug.c exit_point.c player_controls.c map_size.c graphics.c main.c library/get_next_line/get_next_line.c library/get_next_line/get_next_line_utils.c

LIBFT_PATH		=	./library/libft
LIBFT			=	$(LIBFT_PATH)/libft.a

PRINTF_PATH		=	./library/ft_printf
PRINTF			=	$(PRINTF_PATH)/libftprintf.a

MINILIBX_PATH	=	./library/minilibx

all:				$(NAME)

$(NAME):			$(LIBFT) $(PRINTF) mlx
					$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(LIBFT) $(PRINTF) -framework OpenGL -framework AppKit -L$(MINILIBX_PATH) -lmlx

$(LIBFT):
					make -C $(LIBFT_PATH) all

$(PRINTF):
					make -C $(PRINTF_PATH) all

mlx:
					make -C $(MINILIBX_PATH) all

clean:
					make -C $(LIBFT_PATH) clean
					make -C $(MINILIBX_PATH) clean
					make -C $(PRINTF_PATH) clean

fclean:				clean
					make -C $(LIBFT_PATH) fclean
					make -C $(PRINTF_PATH) fclean
					$(RM) $(NAME)

re:					fclean all

.PHONY:				all clean fclean re libft printf
