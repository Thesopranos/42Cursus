NAME		=	cub3D
BMP			=	./screenshot.bmp
MLX			=	libmlx.a

SRCS			=	cub3d.c \
					utils/*.c \
					parse/*.c \
					GNL/*.c \
					display/*.c \

SRCS_BONUS		=	bonus/cub3d.c \
					bonus/utils/*.c \
					bonus/parse/*.c \
					bonus/GNL/*.c \
					bonus/display/*.c \

CC			=	clang

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -f

RMRF		=	rm -rf

UNAME		:=	$(shell uname)

ifeq ($(UNAME), Darwin)
$(NAME):
			@echo "\033[33m[Cub3D MACOS compilation...]"
			@ $(MAKE) -C mlx all
			@ cp ./mlx/$(MLX) .
			$(CC) $(CFLAGS) -g3 -Ofast -o $(NAME) -Imlx $(SRCS) -Lmlx -lmlx -lm -framework OpenGL -framework AppKit
			@echo "\033[32m[ ./cub3D created ]"
endif

ifeq ($(UNAME), Linux)
$(NAME):
			@echo "\033[31;1mCompiling for Linux...\033[0m"
			@chmod 777 mlx_linux/configure
			@ $(MAKE) -C mlx_linux all
			$(CC) $(CFLAGS) -g3 -o $(NAME) $(SRCS) -Imlx_linux -Lmlx_linux -lmlx -lmlx_Linux -L/usr/lib -lXext -lX11 -lm
			@echo "\033[32m[ ./cub3D created ]"
endif

all:		$(NAME)

ifeq ($(UNAME), Darwin)
bonus:		$(NAME_BONUS)
				@echo "\033[33m[Cub3D MACOS compilation with bonus...]"
				@ $(MAKE) -C mlx all
				@ cp ./mlx/$(MLX) .
				$(CC) $(CFLAGS) -g3 -Ofast -o cub3D_bonus -Imlx $(SRCS_BONUS) -Lmlx -lmlx -lm -framework OpenGL -framework AppKit
				@echo "\033[32m[ ./Cub3D_bonus created ]"
endif

ifeq ($(UNAME), Linux)
bonus:		$(NAME_BONUS)
				@echo "\033[33m[Cub3D Linux compilation with bonus...]"
				@chmod 777 mlx_linux/configure
				@ $(MAKE) -C mlx_linux all
				$(CC) $(CFLAGS) -g3 -o cub3D_bonus $(SRCS_BONUS) -Imlx_linux -Lmlx_linux -lmlx -lmlx_Linux -L/usr/lib -lXext -lX11 -lm
				@echo "\033[32m[ ./cub3D_bonus created ]"
endif

ifeq ($(UNAME), Darwin)
clean:
			@ echo "\033[31m[Remove last version...]"
			@ $(MAKE) -C mlx clean
			@ $(RMRF) Cub3D.dSYM cub3D_bonus.dSYM
			@ $(RM) $(BMP)
endif

ifeq ($(UNAME), Linux)
clean:
			@ echo "\033[31m[Remove last version...]"
			@ $(MAKE) -C mlx_linux clean
			@ $(RMRF) Cub3D.dSYM cub3D_bonus.dSYM
			@ $(RM) $(BMP)
endif

fclean:		clean
			@ $(RM) $(MLX)
			$(RM) cub3D
			$(RM) cub3D_bonus


re:			fclean all

.PHONY:		$(NAME) all bonus test clean fclean re

