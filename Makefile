CC = cc
# CFLAGS = -Wall -Wextra -Werror  -c 
SRCS = main.c ./utils/helper_functions/ft_split.c ./utils/helper_functions/utils.c \
	./utils/list/list.c ./utils/helper_functions/utils2.c \
	./utils/helper_functions/ft_memset.c
OBJS = $(SRCS:.c=.o)
NAME = ms
HEADER = m1.h

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) -lreadline -fsanitize=address -g $^ -o $(NAME) 

%.o:%.c $(HEADER)
	$(CC) $(CFLAGS) -g -c $< -o $@

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all 