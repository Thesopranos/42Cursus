# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mertcaki <mertcaki@student.42kocaeli.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/10 18:04:14 by mertcaki          #+#    #+#              #
#    Updated: 2024/11/11 17:31:17 by mertcaki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS =  ./src/main.c ./src/map/free.c ./src/map/map_control.c ./src/map/map_buff_read.c \
		./src/map/map_control_directions_buff.c ./src/map/map_control_utils.c ./src/map/map_control_utils2.c \
		./src/map/map_controls_directions.c ./src/map/map_controls_directions2.c ./src/map/real_map.c \
		./src/map/utils.c ./src/raycast/raycast.c ./src/raycast/raycast2.c ./src/raycast/raycast3.c \
		./src/raycast/raycast4.c ./src/libft/ft_isdigit.c ./src/libft/ft_strlen.c \
		./src/libft/get_next_line.c ./src/libft/ft_printf.c ./src/libft/ft_split.c ./src/map/map_control_utils3.c \
		./src/libft/ft_strchr.c ./src/libft/ft_strdup.c ./src/libft/ft_strjoin.c ./src/libft/ft_strlcpy.c \
		./src/libft/ft_strncmp.c ./src/libft/ft_substr.c ./src/libft/ft_atoi.c \
		./src/map/map_control_directions_buff2.c ./src/raycast/raycast5.c ./src/map/special_split.c \
		./src/map/special_split2.c
OBJS = $(SRCS:.c=.o)
RM = rm -f

MLX = ./minilibx/libmlx_libmlx.a
LIBS = -L./minilibx -lmlx -framework OpenGL -framework AppKit -lm

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C minilibx
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

$(MLX):
	@$(MAKE) -C minilibx

clean:
	@$(MAKE) -C minilibx clean
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
