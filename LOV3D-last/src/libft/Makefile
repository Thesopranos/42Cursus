NAME = libft.a
RM = rm -rf
CC = gcc
FLAG = -Wall -Wextra -Werror
CMPL = $(CC) $(FLAG) -c
MKDIR = mkdir
MV = mv
SRC = 	./ft_split.c		\
		./ft_atoi.c			\
 		./ft_strchr.c 		\
 		./ft_strdup.c		\
 		./ft_strjoin.c 		\
		./ft_strlcpy.c		\
 		./ft_strlen.c 		\
 		./ft_strncmp.c 		\
		./ft_substr.c		\
		./ft_printf.c		\
		./get_next_line.c 	\

OBJ = $(SRC:.c=.o)
OBJDIR = OBJECTS

all: $(NAME)

$(NAME) :
	@$(MKDIR) $(OBJDIR)
	@$(CMPL) $(SRC)
	@ar rc $(NAME) $(OBJ)
	@$(MV) $(OBJ) $(OBJDIR)
clean :
	@$(RM) $(OBJDIR)
fclean : clean
	@$(RM) $(NAME)
re: fclean $(NAME)

.PHONY: all bonus clean fclean re
