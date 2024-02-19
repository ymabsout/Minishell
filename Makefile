CC=cc
CFLAGS=
HEADER=mini_shell.h
RM=rm -f
NAME=minishell

LIB=lib/ft_putstr_fd.c lib/ft_isalnum.c lib/ft_strjoin.c lib/ft_strlcat.c lib/ft_strlcpy.c\
	lib/ft_strlen.c lib/ft_substr.c lib/ft_strdup.c lib/ft_itoa.c lib/ft_lstadd_back.c\
	lib/ft_lstadd_front.c lib/ft_lstclear.c lib/ft_lstdelone.c lib/ft_lstiter.c lib/ft_lstlast.c\
	lib/ft_lstmap.c lib/ft_lstnew.c lib/ft_lstsize.c lib/ft_split.c lib/ft_strncmp.c lib/ft_isalpha.c\
	lib/ft_atoi.c

ERROR=error/err_handler.c error/syntax_error.c error/valid_id.c
CODE=code/expand_env_vars.c code/create_envs.c
UTILS=utils/find_num_char.c utils/free_double.c
BUILT_INS=built_ins/export_built_in.c built_ins/env_built_in.c built_ins/unset_built_in.c\
	built_ins/exit_built_in.c built_ins/pwd_built_in.c built_ins/echo_built_in.c built_ins/cd_built_in.c

SRC=main.c $(LIB) $(ERROR) $(CODE) $(UTILS) $(BUILT_INS)
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