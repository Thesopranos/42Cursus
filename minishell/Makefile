NAME	:= minishell
CC		:= gcc
INCLUDE	:= minishell.h
CFLAGS	:= -I $(INCLUDE) -I ./libft/libft.h
LIBFT	= libft
FLAGS	= -Wall -Wextra -Werror -g

SRC		:=	check_builtin.c \
			echo_and_env.c \
			export_and_unset.c \
			cd_and_pwd.c \
			utils2.c \
			check.c \
			check_utils.c \
			dup_transaction.c \
			exec_free.c \
			exec_free2.c \
			exec.c \
			execve.c \
			expander.c \
			create_files_utils.c \
			create_files.c \
			heredoc_utils.c \
			heredoc.c \
			lexer.c \
			exit.c \
			main.c \
			parser.c \
			parser_control.c \
			signal.c \
			expander_utils.c \
			utils.c \
			exec_utils.c \
			utils3.c

OBJ		:= $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Compiling..."
	@make -C $(LIBFT)
	@cp libft/libft.a .
	@printf "\e[35mLIBFT: \e[32mDONE \e[0m\n"
	@$(CC) $(FLAGS) $(CFLAGS) $(OBJ) libft.a -lreadline -o $@
	@printf "\e[35mMINISHELL: \e[32mDONE\e[0m\n"

.c.o:
	@${CC} ${FLAGS} ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
	@echo "Cleaning..."
	@make clean -C $(LIBFT)
	@rm -rf libft.a
	@rm -rf $(OBJ)

fclean: clean
	@rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re