CC=cc
CFLAGS=
HEADER=mini_shell.h
RM=rm -f
NAME=minishell

LIB=lib/ft_putstr_fd.c lib/ft_isalnum.c lib/ft_strjoin.c lib/ft_strlcat.c lib/ft_strlcpy.c\
	lib/ft_strlen.c lib/ft_substr.c lib/ft_strdup.c lib/ft_itoa.c
ERROR=error/err_handler.c error/syntax_error.c
CODE=code/expand_env_vars.c
UTILS=utils/find_num_char.c

SRC=main.c $(LIB) $(ERROR) $(CODE) $(UTILS)
OBJ=$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $^ -lreadline -o $@

%.o:%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re