CC = cc
CFLAGS = -Wall -Wextra -Werror  -c 
SRCS = main.c ft_split.c utils.c parsing.c tree.c
OBJS = $(SRCS:.c=.o)
NAME = shell
HEADER = m1.h

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) -lreadline -fsanitize=address -g $^ -o $(NAME) 

%.o:%.c $(HEADER)
	$(CC) $(CFLAGS) -g  $< -o $@

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all 