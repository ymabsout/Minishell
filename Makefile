CC = cc
CFLAGS =

ERROR=error/err_handler.c error/syntax_error.c error/valid_id.c
CODE=code/expand_env_vars.c code/create_envs.c
BUILT_INS=built_ins/export_built_in.c built_ins/env_built_in.c built_ins/unset_built_in.c\
	built_ins/exit_built_in.c built_ins/pwd_built_in.c built_ins/echo_built_in.c built_ins/cd_built_in.c

LIB=lib/ft_putstr_fd.c lib/ft_isalnum.c lib/ft_strjoin.c lib/ft_strlcat.c lib/ft_strlcpy.c\
	lib/ft_strlen.c lib/ft_substr.c lib/ft_strdup.c lib/ft_itoa.c lib/ft_lstadd_back.c\
	lib/ft_lstadd_front.c lib/ft_lstclear.c lib/ft_lstdelone.c lib/ft_lstiter.c lib/ft_lstlast.c\
	lib/ft_lstmap.c lib/ft_lstnew.c lib/ft_lstsize.c lib/ft_split.c lib/ft_strncmp.c lib/ft_isalpha.c\
	lib/ft_atoi.c

UTILS=utils/find_num_char.c utils/free_double.c ./utils/helper_functions/utils.c \
	./utils/list/list.c ./utils/helper_functions/ft_memset.c ./utils/tree/tree.c

SRCS = main.c  $(LIB) $(ERROR) $(CODE) $(BUILT_INS) $(UTILS)
OBJS = $(SRCS:.c=.o)
NAME = minishell
HEADER = mini_shell.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -lreadline $^ -o $(NAME) 

%.o:%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re : fclean all 
