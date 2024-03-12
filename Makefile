CC = cc

CFLAGS =-Wall -Wextra -Werror 

ERROR=error/err_handler.c error/syntax_error.c error/valid_id.c error/failing_err.c\
	error/handle_cmd_not_found.c error/fd_failure.c error/sys_failing.c

CODE=code/expand_env_vars.c code/create_envs.c

BUILT_INS=built_ins/env_built_in.c built_ins/unset_built_in.c\
	built_ins/exit_built_in.c built_ins/pwd_built_in.c built_ins/echo_built_in.c built_ins/cd_built_in.c\
	built_ins/export_built_in.c built_ins/export/export_no_args.c\
	built_ins/export/check_args_export.c built_ins/export/export_plus.c\
	built_ins/export/export.c built_ins/export/export_utils.c

LIB=lib/ft_putstr_fd.c lib/ft_isalnum.c lib/ft_strjoin.c lib/ft_strlcat.c lib/ft_strlcpy.c\
	lib/ft_strlen.c lib/ft_substr.c lib/ft_strdup.c lib/ft_itoa.c lib/ft_lstadd_back.c\
	lib/ft_lstadd_front.c lib/ft_lstclear.c lib/ft_lstdelone.c lib/ft_lstiter.c lib/ft_lstlast.c\
	lib/ft_lstmap.c lib/ft_lstnew.c lib/ft_lstsize.c lib/ft_split.c lib/ft_strncmp.c lib/ft_isalpha.c\
	lib/ft_atoi.c lib/ft_strtrim.c lib/ft_strnstr.c

PARSING=parsing/first_list.c parsing/sec_list.c parsing/first_list_follower.c parsing/quote_handler.c\
	parsing/type_giver.c

UTILS=utils/find_num_char.c utils/free_double.c ./utils/helper_functions/utils.c\
	./utils/list/list.c ./utils/helper_functions/ft_memset.c ./utils/tree/tree.c utils/free_half_double.c\
	utils/free_tree.c

EXECUTION=execution/executing.c execution/exe_pipe.c execution/exe_cmd.c\
	execution/ft_join_all_nexts.c execution/get_path_cmd.c\
	execution/exe_and_op.c execution/exe_or_op.c execution/exe_sub_shell.c execution/exe_built_in.c\
	execution/exe_heredoc.c execution/ft_join_all_downs.c execution/expand_double_quote.c execution/expand_single_quote.c\
	execution/exe_heredoc.c execution/redirection/exe_red.c execution/redirection/open_file.c execution/redirection/create_string.c\
	execution/expandtemp.c
	

PRINT=list_print.c

WILD_CARDS=execution/wild_cards/check_wild_card.c execution/wild_cards/handle_wild.c\
	execution/wild_cards/match.c

SIGNAL=Signal/signal_handler.c

SRCS = main.c  $(LIB) $(ERROR) $(CODE) $(BUILT_INS) $(UTILS)\
	$(EXECUTION) $(GET_NEXT_LINE) $(WILD_CARDS) $(PARSING) $(PRINT) $(SIGNAL)

OBJS = $(SRCS:.c=.o)
NAME = minishell
HEADER = mini_shell.h

READLINE_L = $(shell brew --prefix readline)/lib 
READLINE_I = $(shell brew --prefix readline)/include

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -lreadline $(CFLAGS) -L ${READLINE_L} $^ -o $(NAME) 

%.o:%.c $(HEADER)
	$(CC) $(CFLAGS) -I ${READLINE_I} -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re : fclean all 

.PHONY: clean
